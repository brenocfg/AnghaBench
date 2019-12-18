#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  (* gl_term ) (TYPE_2__*) ;} ;
struct TYPE_6__ {scalar_t__ display; scalar_t__ context; TYPE_1__ ops; int /*<<< orphan*/  surface; int /*<<< orphan*/ * native_window; } ;
typedef  TYPE_2__ RASPITEX_STATE ;
typedef  int /*<<< orphan*/  EGLint ;
typedef  int /*<<< orphan*/  EGLConfig ;

/* Variables and functions */
 int /*<<< orphan*/  EGL_DEFAULT_DISPLAY ; 
 scalar_t__ EGL_NO_CONTEXT ; 
 scalar_t__ EGL_NO_DISPLAY ; 
 int /*<<< orphan*/  EGL_NO_SURFACE ; 
 int /*<<< orphan*/  VCOS_FUNCTION ; 
 int /*<<< orphan*/  eglChooseConfig (scalar_t__,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ eglCreateContext (scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  eglCreateWindowSurface (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ eglGetDisplay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglGetError () ; 
 int /*<<< orphan*/  eglInitialize (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglMakeCurrent (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  vcos_log_error (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  vcos_log_trace (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int raspitexutil_gl_common(RASPITEX_STATE *raspitex_state,
                                  const EGLint attribs[], const EGLint context_attribs[])
{
   EGLConfig config;
   EGLint num_configs;

   vcos_log_trace("%s", VCOS_FUNCTION);

   if (raspitex_state->native_window == NULL)
   {
      vcos_log_error("%s: No native window", VCOS_FUNCTION);
      goto error;
   }

   raspitex_state->display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
   if (raspitex_state->display == EGL_NO_DISPLAY)
   {
      vcos_log_error("%s: Failed to get EGL display", VCOS_FUNCTION);
      goto error;
   }

   if (! eglInitialize(raspitex_state->display, 0, 0))
   {
      vcos_log_error("%s: eglInitialize failed", VCOS_FUNCTION);
      goto error;
   }

   if (! eglChooseConfig(raspitex_state->display, attribs, &config,
                         1, &num_configs))
   {
      vcos_log_error("%s: eglChooseConfig failed", VCOS_FUNCTION);
      goto error;
   }

   raspitex_state->surface = eglCreateWindowSurface(raspitex_state->display,
                             config, raspitex_state->native_window, NULL);
   if (raspitex_state->surface == EGL_NO_SURFACE)
   {
      vcos_log_error("%s: eglCreateWindowSurface failed", VCOS_FUNCTION);
      goto error;
   }

   raspitex_state->context = eglCreateContext(raspitex_state->display,
                             config, EGL_NO_CONTEXT, context_attribs);
   if (raspitex_state->context == EGL_NO_CONTEXT)
   {
      vcos_log_error("%s: eglCreateContext failed", VCOS_FUNCTION);
      goto error;
   }

   if (!eglMakeCurrent(raspitex_state->display, raspitex_state->surface,
                       raspitex_state->surface, raspitex_state->context))
   {
      vcos_log_error("%s: Failed to activate EGL context", VCOS_FUNCTION);
      goto error;
   }

   return 0;

error:
   vcos_log_error("%s: EGL error 0x%08x", VCOS_FUNCTION, eglGetError());
   raspitex_state->ops.gl_term(raspitex_state);
   return -1;
}