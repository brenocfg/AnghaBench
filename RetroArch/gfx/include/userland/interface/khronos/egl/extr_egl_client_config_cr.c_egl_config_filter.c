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
#define  EGL_ALPHA_MASK_SIZE 162 
#define  EGL_ALPHA_SIZE 161 
#define  EGL_BIND_TO_TEXTURE_RGB 160 
#define  EGL_BIND_TO_TEXTURE_RGBA 159 
#define  EGL_BLUE_SIZE 158 
#define  EGL_BUFFER_SIZE 157 
#define  EGL_COLOR_BUFFER_TYPE 156 
#define  EGL_CONFIG_CAVEAT 155 
#define  EGL_CONFIG_ID 154 
#define  EGL_CONFORMANT 153 
#define  EGL_DEPTH_SIZE 152 
 scalar_t__ EGL_DONT_CARE ; 
 scalar_t__ EGL_FORMAT_RGBA_8888_EXACT_KHR ; 
 scalar_t__ EGL_FORMAT_RGBA_8888_KHR ; 
 scalar_t__ EGL_FORMAT_RGB_565_EXACT_KHR ; 
 scalar_t__ EGL_FORMAT_RGB_565_KHR ; 
#define  EGL_GREEN_SIZE 151 
#define  EGL_LEVEL 150 
#define  EGL_LUMINANCE_SIZE 149 
#define  EGL_MATCH_FORMAT_KHR 148 
#define  EGL_MATCH_NATIVE_PIXMAP 147 
#define  EGL_MAX_PBUFFER_HEIGHT 146 
#define  EGL_MAX_PBUFFER_PIXELS 145 
#define  EGL_MAX_PBUFFER_WIDTH 144 
#define  EGL_MAX_SWAP_INTERVAL 143 
#define  EGL_MIN_SWAP_INTERVAL 142 
#define  EGL_NATIVE_RENDERABLE 141 
#define  EGL_NATIVE_VISUAL_ID 140 
#define  EGL_NATIVE_VISUAL_TYPE 139 
 scalar_t__ const EGL_NONE ; 
#define  EGL_RECORDABLE_ANDROID 138 
#define  EGL_RED_SIZE 137 
#define  EGL_RENDERABLE_TYPE 136 
#define  EGL_SAMPLES 135 
#define  EGL_SAMPLE_BUFFERS 134 
#define  EGL_STENCIL_SIZE 133 
#define  EGL_SURFACE_TYPE 132 
#define  EGL_TRANSPARENT_BLUE_VALUE 131 
#define  EGL_TRANSPARENT_GREEN_VALUE 130 
#define  EGL_TRANSPARENT_RED_VALUE 129 
#define  EGL_TRANSPARENT_TYPE 128 
 int /*<<< orphan*/  UNREACHABLE () ; 
 int /*<<< orphan*/  egl_config_get_api_support (int) ; 
 int /*<<< orphan*/  egl_config_get_attrib (int,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  egl_config_match_pixmap_info (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  khrn_platform_release_pixmap_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_get_pixmap_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_match_pixmap_api_support (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool egl_config_filter(int id, const EGLint *attrib_list)
{
   if (!attrib_list)
      return true;

   while (*attrib_list != EGL_NONE) {
      EGLint name = *attrib_list++;
      EGLint value = *attrib_list++;
      EGLint actual_value;

      if (!egl_config_get_attrib(id, name, &actual_value) )
      {
         UNREACHABLE();
         return false;
      }

      switch (name) {
         /* Selection Criteria: AtLeast */
      case EGL_BUFFER_SIZE:
      case EGL_RED_SIZE:
      case EGL_GREEN_SIZE:
      case EGL_BLUE_SIZE:
      case EGL_LUMINANCE_SIZE:
      case EGL_ALPHA_SIZE:
      case EGL_ALPHA_MASK_SIZE:
      case EGL_DEPTH_SIZE:
      case EGL_SAMPLE_BUFFERS:
      case EGL_SAMPLES:
      case EGL_STENCIL_SIZE:
         if (value != EGL_DONT_CARE && value > actual_value)
            return false;
         break;

         /* Selection Criteria: Exact */
         /*
            Excluding EGL_TRANSPARENT_x_VALUE and EGL_MATCH_FORMAT_KHR which are listed in
            the table as Exact, but seem to have special rules attached to them.

            Excluding EGL_NATIVE_VISUAL_TYPE which is in the ignore list
            Excluding EGL_LEVEL because EGL_DONT_CARE is not allowed
         */
      case EGL_BIND_TO_TEXTURE_RGB:
      case EGL_BIND_TO_TEXTURE_RGBA:
      case EGL_COLOR_BUFFER_TYPE:
      case EGL_CONFIG_CAVEAT:
      case EGL_CONFIG_ID:
      case EGL_MAX_SWAP_INTERVAL:
      case EGL_MIN_SWAP_INTERVAL:
      case EGL_NATIVE_RENDERABLE:
      case EGL_TRANSPARENT_TYPE:
#if EGL_ANDROID_recordable
      case EGL_RECORDABLE_ANDROID:
#endif
         if (value != EGL_DONT_CARE && value != actual_value)
            return false;
         break;

      case EGL_LEVEL:
         if (value != actual_value)
            return false;
         break;

         /* Selection Criteria: Mask */
      case EGL_CONFORMANT:
      case EGL_RENDERABLE_TYPE:
      case EGL_SURFACE_TYPE:
         if (value != EGL_DONT_CARE && (value & ~actual_value))
            return false;
         break;

         /* Selection Criteria: Special */
      case EGL_MATCH_NATIVE_PIXMAP:
         if (value != EGL_DONT_CARE) { /* see comments in egl_config_check_attribs */
            EGLNativePixmapType pixmap = (EGLNativePixmapType)(intptr_t)value;
            KHRN_IMAGE_WRAP_T image;
            if (!platform_get_pixmap_info(pixmap, &image)) {
               /*
                  Not actually unreachable in theory!
                  We should have detected this in egl_config_check_attribs
                  It's possible that the validity of pixmap has changed since then however...
               */
               UNREACHABLE();
               return false;
            }
            if (!egl_config_match_pixmap_info(id, &image) ||
               !platform_match_pixmap_api_support(pixmap, egl_config_get_api_support(id)))
            {
               khrn_platform_release_pixmap_info(pixmap, &image);
               return false;
            }

            khrn_platform_release_pixmap_info(pixmap, &image);
         }
         break;
#if EGL_KHR_lock_surface
      case EGL_MATCH_FORMAT_KHR:
         if (!(value == EGL_DONT_CARE || value == actual_value
            || (value == EGL_FORMAT_RGB_565_KHR && actual_value == EGL_FORMAT_RGB_565_EXACT_KHR)
            || (value == EGL_FORMAT_RGBA_8888_KHR && actual_value == EGL_FORMAT_RGBA_8888_EXACT_KHR)))
         {
            return false;
         }
         break;
#endif

         /* Attributes we can completely ignore */
      case EGL_MAX_PBUFFER_WIDTH:
      case EGL_MAX_PBUFFER_HEIGHT:
      case EGL_MAX_PBUFFER_PIXELS:
      case EGL_NATIVE_VISUAL_ID:
         /*
         "If EGL_MAX_PBUFFER_WIDTH, EGL_MAX_PBUFFER_HEIGHT,
         EGL_MAX_PBUFFER_PIXELS, or EGL_NATIVE_VISUAL_ID are specified in
         attrib_list, then they are ignored"
         */

      case EGL_NATIVE_VISUAL_TYPE:
         /*
         "if there are no native visual types, then the EGL NATIVE VISUAL TYPE attribute is
         ignored."
         */

      case EGL_TRANSPARENT_BLUE_VALUE:
      case EGL_TRANSPARENT_GREEN_VALUE:
      case EGL_TRANSPARENT_RED_VALUE:
         /*
          "If EGL_TRANSPARENT_TYPE is set to EGL_NONE in attrib_list, then
         the EGL_TRANSPARENT_RED_VALUE, EGL_TRANSPARENT_GREEN_VALUE, and
         EGL_TRANSPARENT_BLUE_VALUE attributes are ignored."

         Possible spec deviation if EGL_TRANSPARENT_TYPE is specified as EGL_DONT_CARE
         and EGL_TRANSPARENT_*_VALUE is also specified?
         */

         break;

      default:
         UNREACHABLE();
         break;
      }
   }

   return true;
}