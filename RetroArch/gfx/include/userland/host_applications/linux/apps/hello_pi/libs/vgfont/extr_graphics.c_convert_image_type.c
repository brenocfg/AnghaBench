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
typedef  int /*<<< orphan*/  VGImageFormat ;
typedef  int /*<<< orphan*/  VCOS_STATUS_T ;
typedef  int GRAPHICS_RESOURCE_TYPE_T ;

/* Variables and functions */
#define  GRAPHICS_RESOURCE_RGB565 130 
#define  GRAPHICS_RESOURCE_RGB888 129 
#define  GRAPHICS_RESOURCE_RGBA32 128 
 int /*<<< orphan*/  VCOS_EINVAL ; 
 int /*<<< orphan*/  VCOS_SUCCESS ; 
 int /*<<< orphan*/  VG_sARGB_8888 ; 
 int /*<<< orphan*/  VG_sRGBX_8888 ; 
 int /*<<< orphan*/  VG_sRGB_565 ; 
 int /*<<< orphan*/  vcos_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static VCOS_STATUS_T convert_image_type(GRAPHICS_RESOURCE_TYPE_T image_type,
                                        VGImageFormat *vg_image_type,
                                        int *pbytes_per_pixel)
{
   int bytes_per_pixel;

   switch (image_type)
   {
   case GRAPHICS_RESOURCE_RGB565:
      *vg_image_type = VG_sRGB_565;
      bytes_per_pixel = 2;
      break;
   case GRAPHICS_RESOURCE_RGB888:
      *vg_image_type = VG_sRGBX_8888;
      bytes_per_pixel = 3; // 24 bpp
      break;
   case GRAPHICS_RESOURCE_RGBA32:
      *vg_image_type = VG_sARGB_8888;
      bytes_per_pixel = 4;
      break;
   default:
      vcos_assert(0);
      *vg_image_type = 0;
      return VCOS_EINVAL;
   }
   if (pbytes_per_pixel)
      *pbytes_per_pixel = bytes_per_pixel;

   return VCOS_SUCCESS;
}