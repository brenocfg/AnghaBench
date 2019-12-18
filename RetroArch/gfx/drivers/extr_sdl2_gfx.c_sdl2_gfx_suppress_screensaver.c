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
 scalar_t__ RARCH_DISPLAY_X11 ; 
 scalar_t__ video_driver_display_type_get () ; 
 int /*<<< orphan*/  video_driver_window_get () ; 
 int /*<<< orphan*/  x11_suspend_screensaver (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool sdl2_gfx_suppress_screensaver(void *data, bool enable)
{
   (void)data;
   (void)enable;

   if (video_driver_display_type_get() == RARCH_DISPLAY_X11)
   {
#ifdef HAVE_X11
      x11_suspend_screensaver(video_driver_window_get(), enable);
#endif
      return true;
   }

   return false;
}