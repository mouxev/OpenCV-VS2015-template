#pragma once

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <set>

#include <cmath>


using namespace cv;
using namespace std;

/*
	Will be keeping helper functions here.
 */

/// TRACE(const char* szFormat, ...)
void TRACE(const char* szFormat, ...)
{
	char szBuff[1024];
	va_list arg;
	va_start(arg, szFormat);
	// this is better than cout because it's a wrapper on printf
	_vsnprintf_s(szBuff, sizeof(szBuff), szFormat, arg);
	/*
	std::ostringstream os_;
	os_ << "[Debug] - 1 - " << __LINE__ << " " << arg << std::endl;
	OutputDebugString(os_.str().c_str());
	*/
	va_end(arg);
	char eol1[2] = "\n";
	OutputDebugString("[debug] - ");
	OutputDebugString(szBuff);
	OutputDebugString(eol1);
}

/// long __stdcall WindowProcedure(HWND window, unsigned int msg, WPARAM wp, LPARAM lp)
/// To close the window
long __stdcall WindowProcedure(HWND window, unsigned int msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_DESTROY:
		// std::cout << "\ndestroying window\n";
		PostQuitMessage(0);
		return 0L;
	case WM_KEYDOWN:
		if (HIWORD(lp) == 1) {
			PostQuitMessage(0);
			return 0L;
		}
		// std::cout << "\nmouse left button down at (" << LOWORD(lp)
		// << ',' << HIWORD(lp) << ")\n";

	case WM_LBUTTONDOWN:
		// std::cout << "\nmouse left button down at (" << LOWORD(lp)
		// 	<< ',' << HIWORD(lp) << ")\n";
		// fall thru
	default:
		// std::cout << '.';
		return DefWindowProc(window, msg, wp, lp);
	}
}

/// void createWindow()
/// just a sample in case needed
void createWindow() {
	const char* const myclass = "myclass";
	WNDCLASSEX wndclass = { sizeof(WNDCLASSEX), CS_DBLCLKS, WindowProcedure,
		0, 0, GetModuleHandle(0), LoadIcon(0,IDI_APPLICATION),
		LoadCursor(0,IDC_ARROW), HBRUSH(COLOR_WINDOW ),
		0, myclass, LoadIcon(0,IDI_APPLICATION) };
	if (RegisterClassEx(&wndclass))
	{
		HWND window = CreateWindowEx(0, myclass, "main.h - window sample",
			WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
			CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, GetModuleHandle(0), 0);
		if (window)
		{
			ShowWindow(window, SW_SHOWDEFAULT);

			HWND hwnd_st_u = CreateWindow("static", "ST_U",
				WS_CHILD | WS_VISIBLE | WS_TABSTOP,
				10, 10, 200, 20,
				window, (HMENU)(501),
				(HINSTANCE)GetWindowLong(window, GWL_HINSTANCE), NULL);
			SetWindowText(hwnd_st_u, "hello world label");


			MSG msg;
			while (GetMessage(&msg, 0, 0, 0)) DispatchMessage(&msg);
		}
	}
}


void getImageFromCameraTemp() {

	VideoCapture cap(0); // open the default camera
	if (cap.isOpened()) {
		Mat frame;
		cap >> frame;
		imwrite("C:\\Temp\\cam_img.jpg", frame);
	}
}

Mat getImageFromCamera() {

	VideoCapture cap(0); // open the default camera
	if (cap.isOpened()) {
		Mat frame;
		cap >> frame;
		return frame;
	}
}