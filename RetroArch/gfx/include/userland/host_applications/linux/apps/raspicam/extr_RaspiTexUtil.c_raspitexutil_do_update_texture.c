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
typedef  int /*<<< orphan*/  GLuint ;
typedef  int /*<<< orphan*/  EGLenum ;
typedef  scalar_t__ EGLImageKHR ;
typedef  int /*<<< orphan*/  EGLDisplay ;
typedef  scalar_t__ EGLClientBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  EGL_NO_CONTEXT ; 
 scalar_t__ EGL_NO_IMAGE_KHR ; 
 int /*<<< orphan*/  GLCHK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_TEXTURE_EXTERNAL_OES ; 
 int /*<<< orphan*/  VCOS_FUNCTION ; 
 scalar_t__ eglCreateImageKHR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eglDestroyImageKHR (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEGLImageTargetTexture2DOES (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vcos_log_trace (char*,int /*<<< orphan*/ ,unsigned int) ; 

int raspitexutil_do_update_texture(EGLDisplay display, EGLenum target,
                                   EGLClientBuffer mm_buf, GLuint *texture, EGLImageKHR *egl_image)
{
   vcos_log_trace("%s: mm_buf %u", VCOS_FUNCTION, (unsigned) mm_buf);
   GLCHK(glBindTexture(GL_TEXTURE_EXTERNAL_OES, *texture));
   if (*egl_image != EGL_NO_IMAGE_KHR)
   {
      /* Discard the EGL image for the preview frame */
      eglDestroyImageKHR(display, *egl_image);
      *egl_image = EGL_NO_IMAGE_KHR;
   }

   *egl_image = eglCreateImageKHR(display, EGL_NO_CONTEXT, target, mm_buf, NULL);
   GLCHK(glEGLImageTargetTexture2DOES(GL_TEXTURE_EXTERNAL_OES, *egl_image));

   return 0;
}