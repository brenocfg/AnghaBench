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
 int /*<<< orphan*/  RARCH_DISPLAY_X11 ; 
 scalar_t__ g_x11_dpy ; 
 int g_x11_true_full ; 
 scalar_t__ g_x11_win ; 
 int /*<<< orphan*/  g_x11_xic ; 
 int /*<<< orphan*/  g_x11_xim ; 
 int /*<<< orphan*/  video_driver_display_set (uintptr_t) ; 
 int /*<<< orphan*/  video_driver_display_type_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_driver_window_set (uintptr_t) ; 
 int /*<<< orphan*/  x11_create_input_context (scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool x11_input_ctx_new(bool true_full)
{
   if (!x11_create_input_context(g_x11_dpy, g_x11_win,
            &g_x11_xim, &g_x11_xic))
      return false;

   video_driver_display_type_set(RARCH_DISPLAY_X11);
   video_driver_display_set((uintptr_t)g_x11_dpy);
   video_driver_window_set((uintptr_t)g_x11_win);
   g_x11_true_full       = true_full;
   return true;
}