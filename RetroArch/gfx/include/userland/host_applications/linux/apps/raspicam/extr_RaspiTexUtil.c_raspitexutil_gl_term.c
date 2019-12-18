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
struct TYPE_3__ {int /*<<< orphan*/  display; int /*<<< orphan*/  surface; int /*<<< orphan*/  context; void* v_egl_image; int /*<<< orphan*/  v_texture; void* u_egl_image; int /*<<< orphan*/  u_texture; void* y_egl_image; int /*<<< orphan*/  y_texture; void* egl_image; int /*<<< orphan*/  texture; } ;
typedef  TYPE_1__ RASPITEX_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  EGL_NO_CONTEXT ; 
 void* EGL_NO_IMAGE_KHR ; 
 int /*<<< orphan*/  EGL_NO_SURFACE ; 
 int /*<<< orphan*/  VCOS_FUNCTION ; 
 int /*<<< orphan*/  eglDestroyContext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglDestroyImageKHR (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  eglDestroySurface (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglMakeCurrent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglTerminate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDeleteTextures (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_log_trace (char*,int /*<<< orphan*/ ) ; 

void raspitexutil_gl_term(RASPITEX_STATE *raspitex_state)
{
   vcos_log_trace("%s", VCOS_FUNCTION);

   /* Delete OES textures */
   glDeleteTextures(1, &raspitex_state->texture);
   eglDestroyImageKHR(raspitex_state->display, raspitex_state->egl_image);
   raspitex_state->egl_image = EGL_NO_IMAGE_KHR;

   glDeleteTextures(1, &raspitex_state->y_texture);
   eglDestroyImageKHR(raspitex_state->display, raspitex_state->y_egl_image);
   raspitex_state->y_egl_image = EGL_NO_IMAGE_KHR;

   glDeleteTextures(1, &raspitex_state->u_texture);
   eglDestroyImageKHR(raspitex_state->display, raspitex_state->u_egl_image);
   raspitex_state->u_egl_image = EGL_NO_IMAGE_KHR;

   glDeleteTextures(1, &raspitex_state->v_texture);
   eglDestroyImageKHR(raspitex_state->display, raspitex_state->v_egl_image);
   raspitex_state->v_egl_image = EGL_NO_IMAGE_KHR;

   /* Terminate EGL */
   eglMakeCurrent(raspitex_state->display, EGL_NO_SURFACE,
                  EGL_NO_SURFACE, EGL_NO_CONTEXT);
   eglDestroyContext(raspitex_state->display, raspitex_state->context);
   eglDestroySurface(raspitex_state->display, raspitex_state->surface);
   eglTerminate(raspitex_state->display);
}