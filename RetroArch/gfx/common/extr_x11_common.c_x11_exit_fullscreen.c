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
typedef  int /*<<< orphan*/  Display ;

/* Variables and functions */
 int /*<<< orphan*/  DefaultScreen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XF86VidModeSetViewPort (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XF86VidModeSwitchToMode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  desktop_mode ; 

void x11_exit_fullscreen(Display *dpy)
{
   XF86VidModeSwitchToMode(dpy, DefaultScreen(dpy), &desktop_mode);
   XF86VidModeSetViewPort(dpy, DefaultScreen(dpy), 0, 0);
}