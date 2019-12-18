#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int should_reset_mode; int /*<<< orphan*/  egl; } ;
typedef  TYPE_1__ xegl_ctx_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  DefaultScreen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RootWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  egl_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  g_x11_dpy ; 
 scalar_t__ g_x11_win ; 
 int /*<<< orphan*/  x11_colormap_destroy () ; 
 int /*<<< orphan*/  x11_exit_fullscreen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x11_input_ctx_destroy () ; 
 int /*<<< orphan*/  x11_window_destroy (int) ; 
 int /*<<< orphan*/  xinerama_save_last_used_monitor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gfx_ctx_xegl_destroy(void *data)
{
   xegl_ctx_data_t *xegl = (xegl_ctx_data_t*)data;

   x11_input_ctx_destroy();
#ifdef HAVE_EGL
   egl_destroy(&xegl->egl);
#endif

   if (g_x11_win)
   {
#ifdef HAVE_XINERAMA
      /* Save last used monitor for later. */
      xinerama_save_last_used_monitor(RootWindow(
               g_x11_dpy, DefaultScreen(g_x11_dpy)));
#endif
      x11_window_destroy(false);
   }

   x11_colormap_destroy();

   if (xegl->should_reset_mode)
   {
      x11_exit_fullscreen(g_x11_dpy);
      xegl->should_reset_mode = false;
   }

   free(data);

   /* Do not close g_x11_dpy. We'll keep one for the entire application
    * lifecycle to work-around nVidia EGL limitations.
    */
}