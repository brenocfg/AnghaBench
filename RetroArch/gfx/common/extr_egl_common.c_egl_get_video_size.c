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
struct TYPE_3__ {scalar_t__ dpy; scalar_t__ surf; } ;
typedef  TYPE_1__ egl_ctx_data_t ;
typedef  unsigned int EGLint ;

/* Variables and functions */
 int /*<<< orphan*/  EGL_HEIGHT ; 
 scalar_t__ EGL_NO_DISPLAY ; 
 scalar_t__ EGL_NO_SURFACE ; 
 int /*<<< orphan*/  EGL_WIDTH ; 
 int /*<<< orphan*/  eglQuerySurface (scalar_t__,scalar_t__,int /*<<< orphan*/ ,unsigned int*) ; 

void egl_get_video_size(egl_ctx_data_t *egl, unsigned *width, unsigned *height)
{
   *width  = 0;
   *height = 0;

   if (egl->dpy != EGL_NO_DISPLAY && egl->surf != EGL_NO_SURFACE)
   {
      EGLint gl_width, gl_height;

      eglQuerySurface(egl->dpy, egl->surf, EGL_WIDTH, &gl_width);
      eglQuerySurface(egl->dpy, egl->surf, EGL_HEIGHT, &gl_height);
      *width  = gl_width;
      *height = gl_height;
   }
}