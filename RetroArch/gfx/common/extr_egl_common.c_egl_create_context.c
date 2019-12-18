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
struct TYPE_3__ {int /*<<< orphan*/ * hw_ctx; int /*<<< orphan*/ * ctx; int /*<<< orphan*/  config; int /*<<< orphan*/  dpy; scalar_t__ use_hw_ctx; } ;
typedef  TYPE_1__ egl_ctx_data_t ;
typedef  int /*<<< orphan*/  EGLint ;
typedef  int /*<<< orphan*/ * EGLContext ;

/* Variables and functions */
 int /*<<< orphan*/ * EGL_NO_CONTEXT ; 
 int /*<<< orphan*/  RARCH_LOG (char*,void*) ; 
 void* eglCreateContext (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

bool egl_create_context(egl_ctx_data_t *egl, const EGLint *egl_attribs)
{
   EGLContext ctx = eglCreateContext(egl->dpy, egl->config, EGL_NO_CONTEXT,
         egl_attribs);

   if (ctx == EGL_NO_CONTEXT)
      return false;

   egl->ctx    = ctx;
   egl->hw_ctx = NULL;

   if (egl->use_hw_ctx)
   {
      egl->hw_ctx = eglCreateContext(egl->dpy, egl->config, egl->ctx,
            egl_attribs);
      RARCH_LOG("[EGL]: Created shared context: %p.\n", (void*)egl->hw_ctx);

      if (egl->hw_ctx == EGL_NO_CONTEXT)
         return false;
   }

   return true;
}