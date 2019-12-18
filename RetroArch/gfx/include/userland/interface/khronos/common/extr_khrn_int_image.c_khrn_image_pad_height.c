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
#define  IMAGE_FORMAT_BRCM1 131 
#define  IMAGE_FORMAT_BRCM2 130 
#define  IMAGE_FORMAT_BRCM4 129 
 int IMAGE_FORMAT_INVALID ; 
 int IMAGE_FORMAT_MEM_LAYOUT_MASK ; 
#define  IMAGE_FORMAT_RSO 128 
 int /*<<< orphan*/  UNREACHABLE () ; 
 int khrn_image_get_log2_brcm1_height (int) ; 
 int khrn_image_get_log2_brcm2_height (int) ; 
 int round_up (int,int) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 

uint32_t khrn_image_pad_height(KHRN_IMAGE_FORMAT_T format, uint32_t height)
{
   vcos_assert(format != IMAGE_FORMAT_INVALID);

   switch (format & IMAGE_FORMAT_MEM_LAYOUT_MASK) {
   case IMAGE_FORMAT_RSO: return height;
   case IMAGE_FORMAT_BRCM1:  return round_up(height, (uint32_t) (1 << khrn_image_get_log2_brcm1_height(format)));
   case IMAGE_FORMAT_BRCM2:  return round_up(height, (uint32_t) (1 << khrn_image_get_log2_brcm2_height(format)));
   case IMAGE_FORMAT_BRCM4: return round_up(height, 64);
   default:               UNREACHABLE(); return 0;
   }
}