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
typedef  scalar_t__ EGLint ;
typedef  int EGLenum ;
typedef  int /*<<< orphan*/  EGL_SURFACE_TYPE_T ;

/* Variables and functions */
 int EGL_BACK_BUFFER ; 
 int EGL_FALSE ; 
#define  EGL_HEIGHT 136 
#define  EGL_LARGEST_PBUFFER 135 
#define  EGL_MIPMAP_TEXTURE 134 
 scalar_t__ const EGL_NONE ; 
 int EGL_NO_TEXTURE ; 
#define  EGL_RENDER_BUFFER 133 
 int EGL_SINGLE_BUFFER ; 
 int EGL_TEXTURE_2D ; 
#define  EGL_TEXTURE_FORMAT 132 
 int EGL_TEXTURE_RGB ; 
 int EGL_TEXTURE_RGBA ; 
#define  EGL_TEXTURE_TARGET 131 
 int EGL_TRUE ; 
#define  EGL_VG_ALPHA_FORMAT 130 
 int EGL_VG_ALPHA_FORMAT_NONPRE ; 
 int EGL_VG_ALPHA_FORMAT_PRE ; 
#define  EGL_VG_COLORSPACE 129 
 int EGL_VG_COLORSPACE_LINEAR ; 
 int EGL_VG_COLORSPACE_sRGB ; 
#define  EGL_WIDTH 128 
 int /*<<< orphan*/  PBUFFER ; 
 int /*<<< orphan*/  WINDOW ; 

bool egl_surface_check_attribs(
   EGL_SURFACE_TYPE_T type,
   const EGLint *attrib_list,
   bool *linear,
   bool *premult,
   bool *single,
   int *width,
   int *height,
   bool *largest_pbuffer,
   EGLenum *texture_format,
   EGLenum *texture_target,
   bool *mipmap_texture
   )
{
   if (!attrib_list)
      return true;

   while (*attrib_list != EGL_NONE) {
      int name = *attrib_list++;
      int value = *attrib_list++;

      switch (name) {
      case EGL_VG_COLORSPACE:
         if (value != EGL_VG_COLORSPACE_sRGB && value != EGL_VG_COLORSPACE_LINEAR)
            return false;
         if (value == EGL_VG_COLORSPACE_LINEAR && linear != NULL)
            *linear = true;
         break;
      case EGL_VG_ALPHA_FORMAT:
         if (value != EGL_VG_ALPHA_FORMAT_NONPRE && value != EGL_VG_ALPHA_FORMAT_PRE)
            return false;
         if (value == EGL_VG_ALPHA_FORMAT_PRE && premult != NULL)
            *premult = true;
         break;

      /* For WINDOW types only */
      case EGL_RENDER_BUFFER:
         if (type != WINDOW || (value != EGL_SINGLE_BUFFER && value != EGL_BACK_BUFFER))
            return false;
         if (value == EGL_SINGLE_BUFFER && single != NULL)
            *single = true;
         break;

      /* For PBUFFER types only */
      case EGL_WIDTH:
         if (type != PBUFFER || value < 0)
            return false;
         if (width != NULL)
            *width = value;
         break;
      case EGL_HEIGHT:
         if (type != PBUFFER || value < 0)
            return false;
         if (height != NULL)
            *height = value;
         break;
      case EGL_LARGEST_PBUFFER:
         if (type != PBUFFER || (value != EGL_FALSE && value != EGL_TRUE))
            return false;
         if (largest_pbuffer != NULL)
            *largest_pbuffer = value;
         break;
      case EGL_TEXTURE_FORMAT:
         if (type != PBUFFER || (value != EGL_NO_TEXTURE && value != EGL_TEXTURE_RGB && value != EGL_TEXTURE_RGBA))
            return false;
         if (texture_format != NULL)
            *texture_format = value;
         break;
      case EGL_TEXTURE_TARGET:
         if (type != PBUFFER || (value != EGL_NO_TEXTURE && value != EGL_TEXTURE_2D))
            return false;
         if (texture_target != NULL)
            *texture_target = value;
         break;
      case EGL_MIPMAP_TEXTURE:
         if (type != PBUFFER || (value != EGL_FALSE && value != EGL_TRUE))
            return false;
         if (mipmap_texture != NULL)
            *mipmap_texture = value;
         break;
      default:
         return false;
      }
   }

   return true;
}