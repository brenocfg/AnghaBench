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
 scalar_t__ XOpenDisplay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_ensure_connection () ; 
 int /*<<< orphan*/  frontend_driver_destroy_signal_handler_state () ; 
 scalar_t__ g_x11_dpy ; 

bool x11_connect(void)
{
   frontend_driver_destroy_signal_handler_state();

   /* Keep one g_x11_dpy alive the entire process lifetime.
    * This is necessary for nVidia's EGL implementation for now. */
   if (!g_x11_dpy)
   {
      g_x11_dpy = XOpenDisplay(NULL);
      if (!g_x11_dpy)
         return false;
   }

#ifdef HAVE_DBUS
   dbus_ensure_connection();
#endif

   return true;
}