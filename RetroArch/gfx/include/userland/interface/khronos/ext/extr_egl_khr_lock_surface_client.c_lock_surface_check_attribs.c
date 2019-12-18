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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  EGLint ;

/* Variables and functions */
 int EGL_FALSE ; 
#define  EGL_LOCK_USAGE_HINT_KHR 129 
#define  EGL_MAP_PRESERVE_PIXELS_KHR 128 
 int EGL_NONE ; 
 int EGL_READ_SURFACE_BIT_KHR ; 
 int EGL_TRUE ; 
 int EGL_WRITE_SURFACE_BIT_KHR ; 

__attribute__((used)) static bool lock_surface_check_attribs(const EGLint *attrib_list, bool *preserve_pixels, uint32_t *lock_usage_hint)
{
   if (!attrib_list)
      return EGL_TRUE;

   while (1) {
      int name = *attrib_list++;
      if (name == EGL_NONE)
         return EGL_TRUE;
      else {
         int value = *attrib_list++;
         switch (name) {
         case EGL_MAP_PRESERVE_PIXELS_KHR:
            *preserve_pixels = value ? true : false;
            break;
         case EGL_LOCK_USAGE_HINT_KHR:
            if (value & ~(EGL_READ_SURFACE_BIT_KHR | EGL_WRITE_SURFACE_BIT_KHR))
               return EGL_FALSE;

            *lock_usage_hint = value;
            break;
         default:
            return EGL_FALSE;
         }
      }
   }
}