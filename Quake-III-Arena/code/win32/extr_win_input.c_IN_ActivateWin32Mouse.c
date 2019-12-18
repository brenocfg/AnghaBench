#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  hWnd; } ;
struct TYPE_5__ {int left; int top; int right; int bottom; } ;
typedef  TYPE_1__ RECT ;

/* Variables and functions */
 int /*<<< orphan*/  ClipCursor (TYPE_1__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  SM_CXSCREEN ; 
 int /*<<< orphan*/  SM_CYSCREEN ; 
 int /*<<< orphan*/  SetCapture (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetCursorPos (int,int) ; 
 scalar_t__ ShowCursor (int /*<<< orphan*/ ) ; 
 TYPE_2__ g_wv ; 
 int window_center_x ; 
 int window_center_y ; 

void IN_ActivateWin32Mouse( void ) {
	int			width, height;
	RECT		window_rect;

	width = GetSystemMetrics (SM_CXSCREEN);
	height = GetSystemMetrics (SM_CYSCREEN);

	GetWindowRect ( g_wv.hWnd, &window_rect);
	if (window_rect.left < 0)
		window_rect.left = 0;
	if (window_rect.top < 0)
		window_rect.top = 0;
	if (window_rect.right >= width)
		window_rect.right = width-1;
	if (window_rect.bottom >= height-1)
		window_rect.bottom = height-1;
	window_center_x = (window_rect.right + window_rect.left)/2;
	window_center_y = (window_rect.top + window_rect.bottom)/2;

	SetCursorPos (window_center_x, window_center_y);

	SetCapture ( g_wv.hWnd );
	ClipCursor (&window_rect);
	while (ShowCursor (FALSE) >= 0)
		;
}