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
#define  IMAGE_FORMAT_1 137 
#define  IMAGE_FORMAT_16 136 
#define  IMAGE_FORMAT_24 135 
#define  IMAGE_FORMAT_32 134 
#define  IMAGE_FORMAT_4 133 
#define  IMAGE_FORMAT_64 132 
#define  IMAGE_FORMAT_8 131 
 int IMAGE_FORMAT_COMP_MASK ; 
#define  IMAGE_FORMAT_ETC1 130 
 int IMAGE_FORMAT_INVALID ; 
 int IMAGE_FORMAT_PIXEL_SIZE_MASK ; 
#define  IMAGE_FORMAT_UNCOMP 129 
#define  IMAGE_FORMAT_YUYV 128 
 int /*<<< orphan*/  UNREACHABLE () ; 
 int /*<<< orphan*/  vcos_assert (int) ; 

uint32_t khrn_image_get_bpp(KHRN_IMAGE_FORMAT_T format)
{
   vcos_assert(format != IMAGE_FORMAT_INVALID);

   switch (format & IMAGE_FORMAT_COMP_MASK) {
   case IMAGE_FORMAT_UNCOMP:
      switch (format & IMAGE_FORMAT_PIXEL_SIZE_MASK) {
         case IMAGE_FORMAT_1:  return 1;
         case IMAGE_FORMAT_4:  return 4;
         case IMAGE_FORMAT_8:  return 8;
         case IMAGE_FORMAT_16: return 16;
         case IMAGE_FORMAT_24: return 24;
         case IMAGE_FORMAT_32: return 32;
         case IMAGE_FORMAT_64: return 64;
         default:              UNREACHABLE(); return 0;
      }
   case IMAGE_FORMAT_ETC1: return 4;
   case IMAGE_FORMAT_YUYV: return 16;
   default:                UNREACHABLE(); return 0;
   }
}