#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  eglContext; int /*<<< orphan*/  eglDisplay; int /*<<< orphan*/  eglSurface; } ;
typedef  TYPE_1__ UserData ;
struct TYPE_8__ {scalar_t__ type; } ;
typedef  int /*<<< orphan*/  KDint ;
typedef  int /*<<< orphan*/  KDchar ;
typedef  int /*<<< orphan*/  KDWindow ;
typedef  TYPE_2__ KDEvent ;
typedef  int EGLint ;
typedef  int /*<<< orphan*/  EGLConfig ;

/* Variables and functions */
 int /*<<< orphan*/  Draw (TYPE_1__*) ; 
 int EGL_ALPHA_SIZE ; 
 int EGL_BLUE_SIZE ; 
 int /*<<< orphan*/  EGL_DEFAULT_DISPLAY ; 
 int EGL_DEPTH_SIZE ; 
 int EGL_DONT_CARE ; 
 int /*<<< orphan*/  EGL_FALSE ; 
 int EGL_GREEN_SIZE ; 
 int EGL_NONE ; 
 int EGL_RED_SIZE ; 
 int EGL_STENCIL_SIZE ; 
 int /*<<< orphan*/  Init (TYPE_1__*) ; 
 int /*<<< orphan*/  InitEGLContext (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ KD_EVENT_WINDOW_CLOSE ; 
 int /*<<< orphan*/ * KD_NULL ; 
 int /*<<< orphan*/  eglChooseConfig (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  eglDestroyContext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglDestroySurface (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglGetConfigs (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  eglGetDisplay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglInitialize (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  eglMakeCurrent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kdCreateWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kdDestroyWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kdExit (int /*<<< orphan*/ ) ; 
 TYPE_2__* kdWaitEvent (int /*<<< orphan*/ ) ; 

KDint kdMain ( KDint argc, const KDchar *const *argv )
{
   EGLint attribList[] =
   {
       EGL_RED_SIZE,       8,
       EGL_GREEN_SIZE,     8,
       EGL_BLUE_SIZE,      8,
       EGL_ALPHA_SIZE,     EGL_DONT_CARE,
       EGL_DEPTH_SIZE,     EGL_DONT_CARE,
       EGL_STENCIL_SIZE,   EGL_DONT_CARE,
       EGL_NONE
   };
   EGLint majorVersion, 
         minorVersion;
   UserData userData;
   EGLint numConfigs;
   EGLConfig config;
   KDWindow *window = KD_NULL;

   userData.eglDisplay = eglGetDisplay( EGL_DEFAULT_DISPLAY );

   // Initialize EGL
   if ( !eglInitialize(userData.eglDisplay, &majorVersion, &minorVersion) )
   {
      return EGL_FALSE;
   }

   // Get configs
   if ( !eglGetConfigs(userData.eglDisplay, NULL, 0, &numConfigs) )
   {
      return EGL_FALSE;
   }

   // Choose config
   if ( !eglChooseConfig(userData.eglDisplay, attribList, &config, 1, &numConfigs) )
   {
      return EGL_FALSE;
   }


   // Use OpenKODE to create a Window
   window = kdCreateWindow ( userData.eglDisplay, config, KD_NULL );
   if( !window )
      kdExit ( 0 );

   if ( !InitEGLContext ( &userData, window, config ) )
      kdExit ( 0 );

   if ( !Init ( &userData ) )
      kdExit ( 0 );

   // Main Loop
   while ( 1 )
   {
      // Wait for an event
      const KDEvent *evt = kdWaitEvent ( 0 );
      if ( evt )
      {
         // Exit app
         if ( evt->type == KD_EVENT_WINDOW_CLOSE)
            break;
      }

      // Draw frame
      Draw ( &userData );
   }

   // EGL clean up 
   eglMakeCurrent ( 0, 0, 0, 0 );
   eglDestroySurface ( userData.eglDisplay, userData.eglSurface );
   eglDestroyContext ( userData.eglDisplay, userData.eglContext );

   // Destroy the window
   kdDestroyWindow(window);

   return 0;
}