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
typedef  int KHRN_IMAGE_FORMAT_T ;

/* Variables and functions */
 int ABGR_8888 ; 
 int A_8 ; 
#define  EGL_PIXEL_FORMAT_ARGB_8888_BRCM 132 
#define  EGL_PIXEL_FORMAT_ARGB_8888_PRE_BRCM 131 
#define  EGL_PIXEL_FORMAT_A_8_BRCM 130 
#define  EGL_PIXEL_FORMAT_RGB_565_BRCM 129 
 int EGL_PIXEL_FORMAT_USAGE_MASK_BRCM ; 
#define  EGL_PIXEL_FORMAT_XRGB_8888_BRCM 128 
 int IMAGE_FORMAT_PRE ; 
 int RGB_565 ; 
 int XBGR_8888 ; 
 int /*<<< orphan*/  vcos_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static KHRN_IMAGE_FORMAT_T convert_format(uint32_t format)
{
   switch (format & ~EGL_PIXEL_FORMAT_USAGE_MASK_BRCM) {
      case EGL_PIXEL_FORMAT_ARGB_8888_PRE_BRCM: return (KHRN_IMAGE_FORMAT_T)(ABGR_8888 | IMAGE_FORMAT_PRE);
      case EGL_PIXEL_FORMAT_ARGB_8888_BRCM:     return ABGR_8888;
      case EGL_PIXEL_FORMAT_XRGB_8888_BRCM:     return XBGR_8888;
      case EGL_PIXEL_FORMAT_RGB_565_BRCM:       return RGB_565;
      case EGL_PIXEL_FORMAT_A_8_BRCM:           return A_8;
      default:
         vcos_assert(0);
         return (KHRN_IMAGE_FORMAT_T)0;
   }
}