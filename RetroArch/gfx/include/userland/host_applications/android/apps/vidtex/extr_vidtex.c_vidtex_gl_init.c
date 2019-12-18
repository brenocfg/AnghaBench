#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  texture; int /*<<< orphan*/  context; int /*<<< orphan*/  surface; int /*<<< orphan*/  display; } ;
typedef  TYPE_1__ VIDTEX_T ;
typedef  int EGLint ;
typedef  int /*<<< orphan*/  EGLNativeWindowType ;
typedef  int /*<<< orphan*/  EGLConfig ;

/* Variables and functions */
 int EGL_BLUE_SIZE ; 
 int /*<<< orphan*/  EGL_DEFAULT_DISPLAY ; 
 int EGL_DEPTH_SIZE ; 
 int EGL_GREEN_SIZE ; 
 int EGL_NONE ; 
 int EGL_RED_SIZE ; 
 int /*<<< orphan*/  GL_DITHER ; 
 int /*<<< orphan*/  GL_FLAT ; 
 int /*<<< orphan*/  GL_SCISSOR_TEST ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TEXTURE_EXTERNAL_OES ; 
 int /*<<< orphan*/  eglChooseConfig (int /*<<< orphan*/ ,int const*,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  eglCreateContext (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eglCreateWindowSurface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eglGetDisplay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglInitialize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglMakeCurrent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGenTextures (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glShadeModel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vidtex_gl_term (TYPE_1__*) ; 

__attribute__((used)) static int vidtex_gl_init(VIDTEX_T *vt, EGLNativeWindowType win)
{
   const EGLint attribs[] =
   {
      EGL_RED_SIZE,   8,
      EGL_GREEN_SIZE, 8,
      EGL_BLUE_SIZE,  8,
      EGL_DEPTH_SIZE, 0,
      EGL_NONE
   };
   EGLConfig config;
   EGLint num_configs;

   vt->display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
   eglInitialize(vt->display, 0, 0);

   eglChooseConfig(vt->display, attribs, &config, 1, &num_configs);

   vt->surface = eglCreateWindowSurface(vt->display, config, win, NULL);
   vt->context = eglCreateContext(vt->display, config, NULL, NULL);

   if (!eglMakeCurrent(vt->display, vt->surface, vt->surface, vt->context))
   {
      vidtex_gl_term(vt);
      return -1;
   }

   glGenTextures(1, &vt->texture);

   glShadeModel(GL_FLAT);
   glDisable(GL_DITHER);
   glDisable(GL_SCISSOR_TEST);
   glEnable(GL_TEXTURE_EXTERNAL_OES);
   glDisable(GL_TEXTURE_2D);

   return 0;
}