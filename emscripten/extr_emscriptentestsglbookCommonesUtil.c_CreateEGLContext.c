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
typedef  int EGLint ;
typedef  scalar_t__ EGLSurface ;
typedef  scalar_t__ EGLNativeWindowType ;
typedef  int /*<<< orphan*/  EGLNativeDisplayType ;
typedef  scalar_t__ EGLDisplay ;
typedef  scalar_t__ EGLContext ;
typedef  int /*<<< orphan*/  EGLConfig ;
typedef  int /*<<< orphan*/  EGLBoolean ;

/* Variables and functions */
 int EGL_CONTEXT_CLIENT_VERSION ; 
 int /*<<< orphan*/  EGL_FALSE ; 
 int EGL_NONE ; 
 scalar_t__ EGL_NO_CONTEXT ; 
 scalar_t__ EGL_NO_DISPLAY ; 
 scalar_t__ EGL_NO_SURFACE ; 
 int /*<<< orphan*/  EGL_TRUE ; 
 int /*<<< orphan*/  eglChooseConfig (scalar_t__,int*,int /*<<< orphan*/ *,int,int*) ; 
 scalar_t__ eglCreateContext (scalar_t__,int /*<<< orphan*/ ,scalar_t__,int*) ; 
 scalar_t__ eglCreateWindowSurface (scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eglGetConfigs (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ eglGetDisplay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglInitialize (scalar_t__,int*,int*) ; 
 int /*<<< orphan*/  eglMakeCurrent (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ x_display ; 

EGLBoolean CreateEGLContext ( EGLNativeWindowType hWnd, EGLDisplay* eglDisplay,
                              EGLContext* eglContext, EGLSurface* eglSurface,
                              EGLint attribList[])
{
   EGLint numConfigs;
   EGLint majorVersion;
   EGLint minorVersion;
   EGLDisplay display;
   EGLContext context;
   EGLSurface surface;
   EGLConfig config;
   EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };

   // Get Display
   display = eglGetDisplay((EGLNativeDisplayType)x_display);
   if ( display == EGL_NO_DISPLAY )
   {
      return EGL_FALSE;
   }

   // Initialize EGL
   if ( !eglInitialize(display, &majorVersion, &minorVersion) )
   {
      return EGL_FALSE;
   }

   // Get configs
   if ( !eglGetConfigs(display, NULL, 0, &numConfigs) )
   {
      return EGL_FALSE;
   }

   // Choose config
   if ( !eglChooseConfig(display, attribList, &config, 1, &numConfigs) )
   {
      return EGL_FALSE;
   }

   // Create a surface
   surface = eglCreateWindowSurface(display, config, (EGLNativeWindowType)hWnd, NULL);
   if ( surface == EGL_NO_SURFACE )
   {
      return EGL_FALSE;
   }

   // Create a GL context
   context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs );
   if ( context == EGL_NO_CONTEXT )
   {
      return EGL_FALSE;
   }   
   
   // Make the context current
   if ( !eglMakeCurrent(display, surface, surface, context) )
   {
      return EGL_FALSE;
   }
   
   *eglDisplay = display;
   *eglSurface = surface;
   *eglContext = context;
   return EGL_TRUE;
}