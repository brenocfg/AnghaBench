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
 int khrn_image_get_bpp (int /*<<< orphan*/ ) ; 
 int khrn_image_pad_width (int /*<<< orphan*/ ,int) ; 

uint32_t khrn_image_get_stride(KHRN_IMAGE_FORMAT_T format, uint32_t width)
{
   return (khrn_image_pad_width(format, width) * khrn_image_get_bpp(format)) >> 3;
}