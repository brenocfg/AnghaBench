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
struct TYPE_3__ {int use_hw_ctx; scalar_t__ dpy; scalar_t__ surf; int /*<<< orphan*/  ctx; int /*<<< orphan*/  hw_ctx; } ;
typedef  TYPE_1__ egl_ctx_data_t ;

/* Variables and functions */
 scalar_t__ EGL_NO_DISPLAY ; 
 scalar_t__ EGL_NO_SURFACE ; 
 int /*<<< orphan*/  eglMakeCurrent (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

void egl_bind_hw_render(egl_ctx_data_t *egl, bool enable)
{
   egl->use_hw_ctx = enable;

   if (egl->dpy  == EGL_NO_DISPLAY)
      return;
   if (egl->surf == EGL_NO_SURFACE)
      return;

   eglMakeCurrent(egl->dpy, egl->surf,
         egl->surf,
         enable ? egl->hw_ctx : egl->ctx);
}