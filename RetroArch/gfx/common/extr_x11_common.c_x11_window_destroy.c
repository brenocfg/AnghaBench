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

/* Variables and functions */
 scalar_t__ None ; 
 int /*<<< orphan*/  XDestroyWindow (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  XUnmapWindow (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dbus_close_connection () ; 
 int /*<<< orphan*/  dbus_screensaver_uninhibit () ; 
 int /*<<< orphan*/  g_x11_dpy ; 
 scalar_t__ g_x11_win ; 

void x11_window_destroy(bool fullscreen)
{
   if (g_x11_win)
      XUnmapWindow(g_x11_dpy, g_x11_win);
   if (!fullscreen)
      XDestroyWindow(g_x11_dpy, g_x11_win);
   g_x11_win = None;

#ifdef HAVE_DBUS
    dbus_screensaver_uninhibit();
    dbus_close_connection();
#endif
}