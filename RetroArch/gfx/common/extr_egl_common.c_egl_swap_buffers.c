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
struct TYPE_2__ {scalar_t__ dpy; scalar_t__ surf; } ;
typedef  TYPE_1__ egl_ctx_data_t ;

/* Variables and functions */
 scalar_t__ EGL_NO_DISPLAY ; 
 scalar_t__ EGL_NO_SURFACE ; 
 int /*<<< orphan*/  eglSwapBuffers (scalar_t__,scalar_t__) ; 

void egl_swap_buffers(void *data)
{
   egl_ctx_data_t *egl = (egl_ctx_data_t*)data;
   if (  egl                         &&
         egl->dpy  != EGL_NO_DISPLAY &&
         egl->surf != EGL_NO_SURFACE
         )
      eglSwapBuffers(egl->dpy, egl->surf);
}