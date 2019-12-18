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

/* Variables and functions */
 int /*<<< orphan*/  EGL_EXTENSIONS ; 
 int /*<<< orphan*/  EGL_NO_CONTEXT ; 
 int /*<<< orphan*/  EGL_NO_SURFACE ; 
 int /*<<< orphan*/  EGL_READ ; 
 int /*<<< orphan*/  GL_BLEND ; 
 int /*<<< orphan*/  GL_EXTENSIONS ; 
 int /*<<< orphan*/  GL_MODELVIEW ; 
 int /*<<< orphan*/  GL_ONE_MINUS_SRC_ALPHA ; 
 int /*<<< orphan*/  GL_PROJECTION ; 
 int /*<<< orphan*/  GL_RENDERER ; 
 int /*<<< orphan*/  GL_SRC_ALPHA ; 
 int /*<<< orphan*/  GL_TEXTURE ; 
 int /*<<< orphan*/  GL_VENDOR ; 
 int /*<<< orphan*/  GL_VERSION ; 
 int /*<<< orphan*/  eglGetCurrentContext () ; 
 int /*<<< orphan*/  eglGetCurrentDisplay () ; 
 int /*<<< orphan*/  eglGetCurrentSurface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglMakeCurrent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglQueryString (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglSwapInterval (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_Context ; 
 int /*<<< orphan*/  g_Display ; 
 int /*<<< orphan*/  g_Surface ; 
 int /*<<< orphan*/  glBlendFunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGetString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glLoadIdentity () ; 
 int /*<<< orphan*/  glMatrixMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glOrthof (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yprintf (int /*<<< orphan*/ ) ; 

int Java_org_yabause_android_YabauseRunnable_initViewport()
{
   int error;
   char * buf;

   g_Display = eglGetCurrentDisplay();
   g_Surface = eglGetCurrentSurface(EGL_READ);
   g_Context = eglGetCurrentContext();

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrthof(0, 320, 224, 0, 1, 0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   glMatrixMode(GL_TEXTURE);
   glLoadIdentity();

   glDisable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   yprintf(glGetString(GL_VENDOR));
   yprintf(glGetString(GL_RENDERER));
   yprintf(glGetString(GL_VERSION));
   yprintf(glGetString(GL_EXTENSIONS));
   yprintf(eglQueryString(g_Display,EGL_EXTENSIONS));
   eglSwapInterval(g_Display,0);
   eglMakeCurrent(g_Display,EGL_NO_SURFACE,EGL_NO_SURFACE,EGL_NO_CONTEXT);
   return 0;
}