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
 int /*<<< orphan*/  RTLD_LAZY ; 
 int /*<<< orphan*/  dlerror () ; 
 void* dlopen (char*,int /*<<< orphan*/ ) ; 
 void* dlsym (void*,char*) ; 
 int /*<<< orphan*/ * eglGetCurrentContext ; 
 int /*<<< orphan*/ * eglGetCurrentDisplay ; 
 int /*<<< orphan*/ * eglGetCurrentSurface ; 
 int /*<<< orphan*/ * eglGetError ; 
 int /*<<< orphan*/ * eglMakeCurrent ; 
 int /*<<< orphan*/ * eglQueryString ; 
 int /*<<< orphan*/ * eglQuerySurface ; 
 int /*<<< orphan*/ * eglSwapBuffers ; 
 int /*<<< orphan*/ * eglSwapInterval ; 
 int /*<<< orphan*/  yprintf (int /*<<< orphan*/ ) ; 

int initEGLFunc()
{
   void * handle;
   char *error;

   handle = dlopen("libEGL.so",RTLD_LAZY);
   if( handle == NULL )
   {
      yprintf(dlerror());
      return -1;
   }

   eglGetCurrentDisplay = dlsym(handle, "eglGetCurrentDisplay");
   if( eglGetCurrentDisplay == NULL){ yprintf(dlerror()); return -1; }

   eglGetCurrentSurface = dlsym(handle, "eglGetCurrentSurface");
   if( eglGetCurrentSurface == NULL){ yprintf(dlerror()); return -1; }

   eglGetCurrentContext = dlsym(handle, "eglGetCurrentContext");
   if( eglGetCurrentContext == NULL){ yprintf(dlerror()); return -1; }

   eglQuerySurface      = dlsym(handle, "eglQuerySurface");
   if( eglQuerySurface == NULL){ yprintf(dlerror()); return -1; }

   eglSwapInterval      = dlsym(handle, "eglSwapInterval");
   if( eglSwapInterval == NULL){ yprintf(dlerror()); return -1; }

   eglMakeCurrent       = dlsym(handle, "eglMakeCurrent");
   if( eglMakeCurrent == NULL){ yprintf(dlerror()); return -1; }

   eglSwapBuffers       = dlsym(handle, "eglSwapBuffers");
   if( eglSwapBuffers == NULL){ yprintf(dlerror()); return -1; }

   eglQueryString       = dlsym(handle, "eglQueryString");
   if( eglQueryString == NULL){ yprintf(dlerror()); return -1; }

   eglGetError          = dlsym(handle, "eglGetError");
   if( eglGetError == NULL){ yprintf(dlerror()); return -1; }

   return 0;
}