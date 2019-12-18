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
typedef  int /*<<< orphan*/  KHRN_IMAGE_FORMAT_T ;

/* Variables and functions */
 int _max (int,int) ; 
 int khrn_image_get_log2_brcm2_height (int /*<<< orphan*/ ) ; 
 int khrn_image_get_log2_brcm2_width (int /*<<< orphan*/ ) ; 
 int khrn_image_get_stride (int /*<<< orphan*/ ,int) ; 
 scalar_t__ khrn_image_is_brcm1 (int /*<<< orphan*/ ) ; 
 scalar_t__ khrn_image_is_brcm2 (int /*<<< orphan*/ ) ; 
 int khrn_image_pad_height (int /*<<< orphan*/ ,int) ; 

uint32_t khrn_image_get_size(KHRN_IMAGE_FORMAT_T format, uint32_t width, uint32_t height)
{
   uint32_t size = khrn_image_get_stride(format, width) * khrn_image_pad_height(format, height);
#ifdef WORKAROUND_HW2038
   if (khrn_image_is_brcm1(format) || khrn_image_is_brcm2(format)) {
      uint32_t log2_brcm2_width = khrn_image_get_log2_brcm2_width(format);
      uint32_t log2_brcm2_height = khrn_image_get_log2_brcm2_height(format);
      uint32_t width_in_brcm2s = (width + ((1 << log2_brcm2_width) - 1)) >> log2_brcm2_width;
      uint32_t height_in_brcm2s = (height + ((1 << log2_brcm2_height) - 1)) >> log2_brcm2_height;
      uint32_t hw2038_size =
         ((((height_in_brcm2s - 1) >> 3) << 7) +
         ((width_in_brcm2s - 1) >> 3) + 1) << 6;
      size = _max(size, hw2038_size);
   } /* else: can't bind it as a texture */
#endif
   return size;
}