#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* egl_config_attribs; } ;
typedef  TYPE_1__ RASPITEX_STATE ;
typedef  int EGLint ;

/* Variables and functions */
 int EGL_ALPHA_SIZE ; 
 int EGL_BLUE_SIZE ; 
 int EGL_CONTEXT_CLIENT_VERSION ; 
 int EGL_DEPTH_SIZE ; 
 int EGL_GREEN_SIZE ; 
 int EGL_NONE ; 
 int EGL_OPENGL_ES_BIT ; 
 int EGL_RED_SIZE ; 
 int EGL_RENDERABLE_TYPE ; 
 int /*<<< orphan*/  GLCHK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_TEXTURE_EXTERNAL_OES ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 
 int raspitexutil_create_textures (TYPE_1__*) ; 
 int raspitexutil_gl_common (TYPE_1__*,int const*,int const*) ; 

int raspitexutil_gl_init_1_0(RASPITEX_STATE *raspitex_state)
{
   int rc;
   const EGLint* attribs = raspitex_state->egl_config_attribs;

   const EGLint default_attribs[] =
   {
      EGL_RED_SIZE,   8,
      EGL_GREEN_SIZE, 8,
      EGL_BLUE_SIZE,  8,
      EGL_ALPHA_SIZE, 8,
      EGL_DEPTH_SIZE, 16,
      EGL_RENDERABLE_TYPE, EGL_OPENGL_ES_BIT,
      EGL_NONE
   };

   const EGLint context_attribs[] =
   {
      EGL_CONTEXT_CLIENT_VERSION, 1,
      EGL_NONE
   };

   if (! attribs)
      attribs = default_attribs;

   rc = raspitexutil_gl_common(raspitex_state, attribs, context_attribs);
   if (rc != 0)
      goto end;

   GLCHK(glEnable(GL_TEXTURE_EXTERNAL_OES));
   rc = raspitexutil_create_textures(raspitex_state);

end:
   return rc;
}