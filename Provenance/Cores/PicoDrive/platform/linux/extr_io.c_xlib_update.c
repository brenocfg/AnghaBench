#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ Status ;

/* Variables and functions */
 int /*<<< orphan*/  DefaultGC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLockDisplay (int /*<<< orphan*/ ) ; 
 scalar_t__ XPutImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XUnlockDisplay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  g_screen_height ; 
 int /*<<< orphan*/  g_screen_width ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  ximage ; 
 int /*<<< orphan*/  xlib_display ; 
 int /*<<< orphan*/  xlib_window ; 

__attribute__((used)) static void xlib_update(void)
{
	Status xstatus;

	XLockDisplay(xlib_display);

	xstatus = XPutImage(xlib_display, xlib_window, DefaultGC(xlib_display, 0), ximage,
		0, 0, 0, 0, g_screen_width, g_screen_height);
	if (xstatus != 0)
		fprintf(stderr, "XPutImage %d\n", xstatus);

	XUnlockDisplay(xlib_display);
}