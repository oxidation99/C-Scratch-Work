// CIS023_S2015_Lab20 Zachary Muerle.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "CIS023_S2015_Lab20 Zachary Muerle.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

quadrupedClass *Dog = new quadrupedClass;
int iTimer = 0;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
//INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_CIS023_S2015_LAB20ZACHARYMUERLE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CIS023_S2015_LAB20ZACHARYMUERLE));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CIS023_S2015_LAB20ZACHARYMUERLE));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_CIS023_S2015_LAB20ZACHARYMUERLE);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	int direct = Dog->GetMoveDirection();//hopefully this isn't too much, being called every message...


	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_GO:
			if (iTimer != 0)
				KillTimer(hWnd, iTimer);
			iTimer = SetTimer(hWnd, WM_TIMER, 50, NULL);//set a timer for every 50ms, and don't end the first time
			Dog->reset();
			Dog->MoveDirection(DOWN | RIGHT, hWnd);
			InvalidateRect(hWnd, NULL, true);//re-draw hWnd: the rectangle of EVERYTHING, and confirm
			break;
		case ID_DIRECTION_UP:
			if (direct & UP){//if it's already going up, stop going up
				direct ^= UP;
			}
			else{//otherwise, start going up
				direct |= UP;
			}
			Dog->MoveDirection(direct, hWnd);
			break;
		case ID_DIRECTION_DOWN:
			if (direct & DOWN){//if it's already going down, stop going down
				direct ^= DOWN;
			}
			else{//otherwise, start going down
				direct |= DOWN;
			}
			Dog->MoveDirection(direct, hWnd);
			break;
		case ID_DIRECTION_RIGHT:
			if (direct & RIGHT){//if it's already going RIGHT, stop going RIGHT
				direct ^= RIGHT;
			}
			else{//otherwise, start going RIGHT
				direct |= RIGHT;
			}
			Dog->MoveDirection(direct, hWnd);
			break;
		case ID_DIRECTION_LEFT:
			if (direct & LEFT){//if it's already going LEFT, stop going LEFT
				direct ^= LEFT;
			}
			else{//otherwise, start going LEFT
				direct |= LEFT;
			}
			Dog->MoveDirection(direct, hWnd);
			break;
		case ID_SPEED_UP:
			Dog->changeSpeed(1);
			break;
		case ID_SPEED_DOWN:
			Dog->changeSpeed(-1);
			break;
			/*case IDM_ABOUT:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				break;
				case IDM_EXIT:
				DestroyWindow(hWnd);
				break;*///I removed these, but I may want to steal their code later
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_TIMER:
		Dog->Move(hWnd);
		InvalidateRect(hWnd, &Dog->RedrawArea(false), true);//re-draw hWnd: the rectangle dog gives us
		//InvalidateRect(hWnd, NULL, true);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		Dog->Draw(hdc);

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

/*// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
UNREFERENCED_PARAMETER(lParam);
switch (message)
{
case WM_INITDIALOG:
return (INT_PTR)TRUE;

case WM_COMMAND:
if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
{
EndDialog(hDlg, LOWORD(wParam));
return (INT_PTR)TRUE;
}
break;
}
return (INT_PTR)FALSE;
}*/
