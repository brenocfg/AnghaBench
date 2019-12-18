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

/* Variables and functions */
#define  EGL_BAD_ACCESS 140 
#define  EGL_BAD_ALLOC 139 
#define  EGL_BAD_ATTRIBUTE 138 
#define  EGL_BAD_CONFIG 137 
#define  EGL_BAD_CONTEXT 136 
#define  EGL_BAD_CURRENT_SURFACE 135 
#define  EGL_BAD_DISPLAY 134 
#define  EGL_BAD_MATCH 133 
#define  EGL_BAD_NATIVE_PIXMAP 132 
#define  EGL_BAD_NATIVE_WINDOW 131 
#define  EGL_BAD_PARAMETER 130 
#define  EGL_BAD_SURFACE 129 
#define  EGL_SUCCESS 128 
 int /*<<< orphan*/  RARCH_ERR (char*,unsigned int,char const*) ; 
 int eglGetError () ; 

void egl_report_error(void)
{
   EGLint    error = eglGetError();
   const char *str = NULL;
   switch (error)
   {
      case EGL_SUCCESS:
         str = "EGL_SUCCESS";
         break;

      case EGL_BAD_ACCESS:
         str = "EGL_BAD_ACCESS";
         break;

      case EGL_BAD_ALLOC:
         str = "EGL_BAD_ALLOC";
         break;

      case EGL_BAD_ATTRIBUTE:
         str = "EGL_BAD_ATTRIBUTE";
         break;

      case EGL_BAD_CONFIG:
         str = "EGL_BAD_CONFIG";
         break;

      case EGL_BAD_CONTEXT:
         str = "EGL_BAD_CONTEXT";
         break;

      case EGL_BAD_CURRENT_SURFACE:
         str = "EGL_BAD_CURRENT_SURFACE";
         break;

      case EGL_BAD_DISPLAY:
         str = "EGL_BAD_DISPLAY";
         break;

      case EGL_BAD_MATCH:
         str = "EGL_BAD_MATCH";
         break;

      case EGL_BAD_NATIVE_PIXMAP:
         str = "EGL_BAD_NATIVE_PIXMAP";
         break;

      case EGL_BAD_NATIVE_WINDOW:
         str = "EGL_BAD_NATIVE_WINDOW";
         break;

      case EGL_BAD_PARAMETER:
         str = "EGL_BAD_PARAMETER";
         break;

      case EGL_BAD_SURFACE:
         str = "EGL_BAD_SURFACE";
         break;

      default:
         str = "Unknown";
         break;
   }

   RARCH_ERR("[EGL]: #0x%x, %s\n", (unsigned)error, str);
}