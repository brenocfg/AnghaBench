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
typedef  int /*<<< orphan*/  KHRN_IMAGE_WRAP_T ;
typedef  scalar_t__ EGLint ;
typedef  int /*<<< orphan*/  EGLNativePixmapType ;

/* Variables and functions */
#define  EGL_ALPHA_MASK_SIZE 170 
#define  EGL_ALPHA_SIZE 169 
#define  EGL_BIND_TO_TEXTURE_RGB 168 
#define  EGL_BIND_TO_TEXTURE_RGBA 167 
#define  EGL_BLUE_SIZE 166 
#define  EGL_BUFFER_SIZE 165 
#define  EGL_COLOR_BUFFER_TYPE 164 
#define  EGL_CONFIG_CAVEAT 163 
#define  EGL_CONFIG_ID 162 
#define  EGL_CONFORMANT 161 
#define  EGL_DEPTH_SIZE 160 
#define  EGL_DONT_CARE 159 
#define  EGL_FALSE 158 
#define  EGL_FORMAT_RGBA_8888_EXACT_KHR 157 
#define  EGL_FORMAT_RGBA_8888_KHR 156 
#define  EGL_FORMAT_RGB_565_EXACT_KHR 155 
#define  EGL_FORMAT_RGB_565_KHR 154 
#define  EGL_GREEN_SIZE 153 
#define  EGL_LEVEL 152 
 int EGL_LOCK_SURFACE_BIT_KHR ; 
 scalar_t__ EGL_LUMINANCE_BUFFER ; 
#define  EGL_LUMINANCE_SIZE 151 
#define  EGL_MATCH_FORMAT_KHR 150 
#define  EGL_MATCH_NATIVE_PIXMAP 149 
#define  EGL_MAX_PBUFFER_HEIGHT 148 
#define  EGL_MAX_PBUFFER_PIXELS 147 
#define  EGL_MAX_PBUFFER_WIDTH 146 
#define  EGL_MAX_SWAP_INTERVAL 145 
#define  EGL_MIN_SWAP_INTERVAL 144 
 int EGL_MULTISAMPLE_RESOLVE_BOX_BIT ; 
#define  EGL_NATIVE_RENDERABLE 143 
#define  EGL_NATIVE_VISUAL_ID 142 
#define  EGL_NATIVE_VISUAL_TYPE 141 
#define  EGL_NONE 140 
 scalar_t__ EGL_NON_CONFORMANT_CONFIG ; 
 scalar_t__ EGL_OPENGL_BIT ; 
 scalar_t__ EGL_OPENGL_ES2_BIT ; 
 scalar_t__ EGL_OPENGL_ES_BIT ; 
 scalar_t__ EGL_OPENVG_BIT ; 
 int EGL_OPTIMAL_FORMAT_BIT_KHR ; 
 int EGL_PBUFFER_BIT ; 
 int EGL_PIXMAP_BIT ; 
#define  EGL_RECORDABLE_ANDROID 139 
#define  EGL_RED_SIZE 138 
#define  EGL_RENDERABLE_TYPE 137 
 scalar_t__ EGL_RGB_BUFFER ; 
#define  EGL_SAMPLES 136 
#define  EGL_SAMPLE_BUFFERS 135 
 scalar_t__ EGL_SLOW_CONFIG ; 
#define  EGL_STENCIL_SIZE 134 
#define  EGL_SURFACE_TYPE 133 
 int EGL_SWAP_BEHAVIOR_PRESERVED_BIT ; 
#define  EGL_TRANSPARENT_BLUE_VALUE 132 
#define  EGL_TRANSPARENT_GREEN_VALUE 131 
#define  EGL_TRANSPARENT_RED_VALUE 130 
 scalar_t__ EGL_TRANSPARENT_RGB ; 
#define  EGL_TRANSPARENT_TYPE 129 
#define  EGL_TRUE 128 
 int EGL_VG_ALPHA_FORMAT_PRE_BIT ; 
 int EGL_VG_COLORSPACE_LINEAR_BIT ; 
 int EGL_WINDOW_BIT ; 
 int /*<<< orphan*/  khrn_platform_release_pixmap_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_get_pixmap_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool egl_config_check_attribs(const EGLint *attrib_list, bool *use_red, bool *use_green, bool *use_blue, bool *use_alpha)
{
   if (!attrib_list)
      return true;

   while (*attrib_list != EGL_NONE) {
      EGLint name = *attrib_list++;
      EGLint value = *attrib_list++;

      if (name == EGL_RED_SIZE && value != 0 && value != EGL_DONT_CARE)
         *use_red = true;

      if (name == EGL_GREEN_SIZE && value != 0 && value != EGL_DONT_CARE)
         *use_green = true;

      if (name == EGL_BLUE_SIZE && value != 0 && value != EGL_DONT_CARE)
         *use_blue = true;

      if (name == EGL_ALPHA_SIZE && value != 0 && value != EGL_DONT_CARE)
         *use_alpha = true;

      switch (name) {
      case EGL_BUFFER_SIZE:
      case EGL_RED_SIZE:
      case EGL_GREEN_SIZE:
      case EGL_BLUE_SIZE:
      case EGL_LUMINANCE_SIZE:
      case EGL_ALPHA_SIZE:
      case EGL_ALPHA_MASK_SIZE:
         if (value != EGL_DONT_CARE && value < 0) return false;
         break;
      case EGL_BIND_TO_TEXTURE_RGB:
      case EGL_BIND_TO_TEXTURE_RGBA:
         if (value != EGL_DONT_CARE && value != EGL_FALSE && value != EGL_TRUE)
            return false;
         break;
      case EGL_COLOR_BUFFER_TYPE:
         if (value != EGL_DONT_CARE && value != EGL_RGB_BUFFER && value != EGL_LUMINANCE_BUFFER)
            return false;
         break;
      case EGL_CONFIG_CAVEAT:
         if (value != EGL_DONT_CARE && value != EGL_NONE && value != EGL_SLOW_CONFIG && value != EGL_NON_CONFORMANT_CONFIG)
            return false;
         break;
      case EGL_CONFIG_ID:
         if (value != EGL_DONT_CARE && value < 1)
            return false;
         break;
      case EGL_CONFORMANT:
         if (value != EGL_DONT_CARE && (value & ~(EGL_OPENGL_BIT|EGL_OPENGL_ES_BIT|EGL_OPENGL_ES2_BIT|EGL_OPENVG_BIT)))
            return false;
         break;
      case EGL_DEPTH_SIZE:
         if (value != EGL_DONT_CARE && value < 0) return false;
         break;
      case EGL_LEVEL:
         break;
      case EGL_MATCH_NATIVE_PIXMAP:
         /* 1.4 Spec is poor here - says that value has to be a valid handle, but also says that any attribute
          * value (other than EGL_LEVEL) can be EGL_DONT_CARE. It also says that the default value is EGL_NONE,
          * but that doesn't really make sense - sensible to assume that the default is EGL_DONT_CARE, and don't
          * support EGL_NONE as an explicit parameter. (Could theoretically collide with a real handle...)
          */
         if (value != EGL_DONT_CARE) {
            KHRN_IMAGE_WRAP_T image;
            if (!platform_get_pixmap_info((EGLNativePixmapType)(intptr_t)value, &image))
               return false;
            khrn_platform_release_pixmap_info((EGLNativePixmapType)(intptr_t)value, &image);
         }
         break;
      case EGL_MAX_PBUFFER_WIDTH:
      case EGL_MAX_PBUFFER_HEIGHT:
      case EGL_MAX_PBUFFER_PIXELS:
         break;
      case EGL_MAX_SWAP_INTERVAL:
      case EGL_MIN_SWAP_INTERVAL:
         if (value != EGL_DONT_CARE && value < 0) return false;
         break;
      case EGL_NATIVE_RENDERABLE:
         if (value != EGL_DONT_CARE && value != EGL_FALSE && value != EGL_TRUE)
            return false;
         break;
      case EGL_NATIVE_VISUAL_ID:
      case EGL_NATIVE_VISUAL_TYPE:
         break;
      case EGL_RENDERABLE_TYPE:
         if (value != EGL_DONT_CARE && (value & ~(EGL_OPENGL_BIT|EGL_OPENGL_ES_BIT|EGL_OPENGL_ES2_BIT|EGL_OPENVG_BIT)))
            return false;
         break;
      case EGL_SAMPLE_BUFFERS:
      case EGL_SAMPLES:
      case EGL_STENCIL_SIZE:
         if (value != EGL_DONT_CARE && value < 0) return false;
         break;
      case EGL_SURFACE_TYPE:
      {
         int valid_bits = EGL_WINDOW_BIT|EGL_PIXMAP_BIT|EGL_PBUFFER_BIT|
            EGL_MULTISAMPLE_RESOLVE_BOX_BIT|EGL_SWAP_BEHAVIOR_PRESERVED_BIT|
            EGL_VG_COLORSPACE_LINEAR_BIT|EGL_VG_ALPHA_FORMAT_PRE_BIT;
#if EGL_KHR_lock_surface
         valid_bits |= EGL_LOCK_SURFACE_BIT_KHR|EGL_OPTIMAL_FORMAT_BIT_KHR;
#endif
         if (value != EGL_DONT_CARE && (value & ~valid_bits))
            return false;
         break;
      }
      case EGL_TRANSPARENT_TYPE:
         if (value != EGL_DONT_CARE && value != EGL_NONE && value != EGL_TRANSPARENT_RGB)
            return false;
         break;
      case EGL_TRANSPARENT_RED_VALUE:
      case EGL_TRANSPARENT_GREEN_VALUE:
      case EGL_TRANSPARENT_BLUE_VALUE:
         if (value != EGL_DONT_CARE && value < 0) return false;
         break;
#if EGL_KHR_lock_surface
      case EGL_MATCH_FORMAT_KHR:
         switch (value) {
         case EGL_DONT_CARE:
         case EGL_NONE:
         case EGL_FORMAT_RGB_565_EXACT_KHR:
         case EGL_FORMAT_RGB_565_KHR:
         case EGL_FORMAT_RGBA_8888_EXACT_KHR:
         case EGL_FORMAT_RGBA_8888_KHR:
            break;
         default:
            return false;
         }
         break;
#endif
#if EGL_ANDROID_recordable
      case EGL_RECORDABLE_ANDROID:
         switch (value) {
         case EGL_DONT_CARE:
         case EGL_TRUE:
         case EGL_FALSE:
            break;
         default:
            return false;
         }
         break;
#endif
      default:
         return false;
      }
   }

   return true;
}