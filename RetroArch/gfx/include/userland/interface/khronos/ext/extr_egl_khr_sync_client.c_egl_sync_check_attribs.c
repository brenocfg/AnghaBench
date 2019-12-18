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
typedef  int EGLenum ;
typedef  int EGLBoolean ;

/* Variables and functions */
 int EGL_FALSE ; 
 int EGL_NONE ; 
#define  EGL_SYNC_FENCE_KHR 128 
 int EGL_SYNC_PRIOR_COMMANDS_COMPLETE_KHR ; 
 int EGL_UNSIGNALED_KHR ; 

__attribute__((used)) static EGLBoolean egl_sync_check_attribs(const EGLint *attrib_list, EGLenum type,
      EGLint *condition, EGLint *threshold, EGLint *status)
{
   switch (type) {
   case EGL_SYNC_FENCE_KHR:
      *condition = EGL_SYNC_PRIOR_COMMANDS_COMPLETE_KHR;
      *threshold = 0;
      *status = EGL_UNSIGNALED_KHR;
      break;
   default :
      *condition = EGL_NONE;
      *threshold = 0;
      *status = 0;
      break;
   }

   if (attrib_list) {
      while (1) {
         int name = *attrib_list++;
         if (name == EGL_NONE)
            break;
         else {
            /* int value = * */attrib_list++; /* at present no name/value pairs are handled */
            switch (name) {
            default:
               return EGL_FALSE;
            }
         }
      }
   }

   return ((type == EGL_SYNC_FENCE_KHR) || (type == 0));
}