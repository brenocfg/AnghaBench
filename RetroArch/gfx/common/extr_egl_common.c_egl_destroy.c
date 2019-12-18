#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ ctx; scalar_t__ hw_ctx; scalar_t__ surf; scalar_t__ config; scalar_t__ dpy; } ;
typedef  TYPE_1__ egl_ctx_data_t ;

/* Variables and functions */
 scalar_t__ EGL_NO_CONTEXT ; 
 scalar_t__ EGL_NO_DISPLAY ; 
 scalar_t__ EGL_NO_SURFACE ; 
 int /*<<< orphan*/  eglDestroyContext (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  eglDestroySurface (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  eglMakeCurrent (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  eglTerminate (scalar_t__) ; 
 int /*<<< orphan*/  frontend_driver_destroy_signal_handler_state () ; 
 int g_egl_inited ; 
 int /*<<< orphan*/  glFinish () ; 
 int /*<<< orphan*/  glFlush () ; 

void egl_destroy(egl_ctx_data_t *egl)
{
   if (egl->dpy)
   {
#if defined HAVE_OPENGL
#if !defined(RARCH_MOBILE)
      if (egl->ctx != EGL_NO_CONTEXT)
      {
         glFlush();
         glFinish();
      }
#endif
#endif

      eglMakeCurrent(egl->dpy,
            EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
      if (egl->ctx != EGL_NO_CONTEXT)
         eglDestroyContext(egl->dpy, egl->ctx);

      if (egl->hw_ctx != EGL_NO_CONTEXT)
         eglDestroyContext(egl->dpy, egl->hw_ctx);

      if (egl->surf != EGL_NO_SURFACE)
         eglDestroySurface(egl->dpy, egl->surf);
      eglTerminate(egl->dpy);
   }

   /* Be as careful as possible in deinit.
    * If we screw up, any TTY will not restore.
    */

   egl->ctx     = EGL_NO_CONTEXT;
   egl->hw_ctx  = EGL_NO_CONTEXT;
   egl->surf    = EGL_NO_SURFACE;
   egl->dpy     = EGL_NO_DISPLAY;
   egl->config  = 0;
   g_egl_inited  = false;

   frontend_driver_destroy_signal_handler_state();
}