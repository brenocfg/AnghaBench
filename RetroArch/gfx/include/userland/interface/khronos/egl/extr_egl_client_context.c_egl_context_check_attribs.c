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
typedef  int /*<<< orphan*/  EGLBoolean ;

/* Variables and functions */
#define  EGL_CONTEXT_CLIENT_VERSION 129 
 int /*<<< orphan*/  EGL_FALSE ; 
#define  EGL_NONE 128 
 int /*<<< orphan*/  EGL_TRUE ; 

EGLBoolean egl_context_check_attribs(const EGLint *attrib_list, EGLint max_version, EGLint *version)
{
   if (!attrib_list)
      return EGL_TRUE;

   while (1) {
      switch (*attrib_list++) {
      case EGL_CONTEXT_CLIENT_VERSION:
      {
         EGLint value = *attrib_list++;

         if (value < 1 || value > max_version)
            return EGL_FALSE;
         else
            *version = value;

         break;
      }
      case EGL_NONE:
         return EGL_TRUE;
      default:
         return EGL_FALSE;
      }
   }
}