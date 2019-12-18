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
typedef  int /*<<< orphan*/  Window ;

/* Variables and functions */
 scalar_t__ dbus_suspend_screensaver (int) ; 
 int /*<<< orphan*/  x11_suspend_screensaver_xdg_screensaver (int /*<<< orphan*/ ,int) ; 

void x11_suspend_screensaver(Window wnd, bool enable)
{
#ifdef HAVE_DBUS
    if (dbus_suspend_screensaver(enable))
       return;
#endif
    x11_suspend_screensaver_xdg_screensaver(wnd, enable);
}