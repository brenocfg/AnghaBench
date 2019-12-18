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
struct TYPE_3__ {int /*<<< orphan*/  config; int /*<<< orphan*/  dpy; } ;
typedef  TYPE_1__ egl_ctx_data_t ;
typedef  int /*<<< orphan*/  EGLint ;

/* Variables and functions */
 int /*<<< orphan*/  EGL_NATIVE_VISUAL_ID ; 
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int /*<<< orphan*/  eglGetConfigAttrib (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool egl_get_native_visual_id(egl_ctx_data_t *egl, EGLint *value)
{
   if (!eglGetConfigAttrib(egl->dpy, egl->config,
         EGL_NATIVE_VISUAL_ID, value))
   {
      RARCH_ERR("[EGL]: egl_get_native_visual_id failed.\n");
      return false;
   }

   return true;
}