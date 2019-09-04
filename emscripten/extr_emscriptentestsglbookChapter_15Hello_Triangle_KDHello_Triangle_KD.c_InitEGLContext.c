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
struct TYPE_3__ {scalar_t__ eglSurface; scalar_t__ eglContext; int /*<<< orphan*/  eglDisplay; } ;
typedef  TYPE_1__ UserData ;
typedef  int /*<<< orphan*/  KDWindow ;
typedef  int EGLint ;
typedef  scalar_t__ EGLSurface ;
typedef  int /*<<< orphan*/  EGLNativeWindowType ;
typedef  scalar_t__ EGLContext ;
typedef  int /*<<< orphan*/  EGLConfig ;
typedef  int /*<<< orphan*/  EGLBoolean ;

/* Variables and functions */
 int EGL_CONTEXT_CLIENT_VERSION ; 
 int /*<<< orphan*/  EGL_FALSE ; 
 int EGL_NONE ; 
 scalar_t__ EGL_NO_CONTEXT ; 
 scalar_t__ EGL_NO_SURFACE ; 
 int /*<<< orphan*/  EGL_TRUE ; 
 scalar_t__ eglCreateContext (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int*) ; 
 scalar_t__ eglCreateWindowSurface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eglMakeCurrent (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ kdRealizeWindow (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

EGLBoolean InitEGLContext ( UserData *userData,
                            KDWindow *window,                             
                            EGLConfig config )
{
   EGLContext context;
   EGLSurface surface;   
   EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };

   // Get native window handle
   EGLNativeWindowType hWnd;
   if(kdRealizeWindow(window, &hWnd) != 0)
   {
      return EGL_FALSE;
   }
   surface = eglCreateWindowSurface(userData->eglDisplay, config, hWnd, NULL);
   if ( surface == EGL_NO_SURFACE )
   {
      return EGL_FALSE;
   }

   // Create a GL context
   context = eglCreateContext(userData->eglDisplay, config, EGL_NO_CONTEXT, contextAttribs );
   if ( context == EGL_NO_CONTEXT )
   {
      return EGL_FALSE;
   }   

   // Make the context current
   if ( !eglMakeCurrent(userData->eglDisplay, surface, surface, context) )
   {
      return EGL_FALSE;
   }

   userData->eglContext = context;
   userData->eglSurface = surface;

   return EGL_TRUE;
}