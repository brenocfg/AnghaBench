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
 int DEPTH_32_TLBD ; 
 int DEPTH_COL_64_TLBD ; 
#define  IMAGE_FORMAT_16 129 
#define  IMAGE_FORMAT_32 128 
 int IMAGE_FORMAT_PIXEL_SIZE_MASK ; 
 int IMAGE_FORMAT_Z ; 
 int /*<<< orphan*/  UNREACHABLE () ; 
 scalar_t__ khrn_image_is_depth (int) ; 

uint32_t khrn_image_get_z_size(KHRN_IMAGE_FORMAT_T format)
{
   if (khrn_image_is_depth(format) && (format & IMAGE_FORMAT_Z)) {
      if (format == DEPTH_32_TLBD || format == DEPTH_COL_64_TLBD)
         return 24;
      switch (format & IMAGE_FORMAT_PIXEL_SIZE_MASK) {
      case IMAGE_FORMAT_32: return 24;
      case IMAGE_FORMAT_16: return 16;
      default:              UNREACHABLE(); return 0;
      }
   } else {
      return 0;
   }
}