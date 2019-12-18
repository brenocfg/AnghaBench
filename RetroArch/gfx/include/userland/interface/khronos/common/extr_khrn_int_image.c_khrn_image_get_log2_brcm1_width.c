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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  KHRN_IMAGE_FORMAT_T ;

/* Variables and functions */
 scalar_t__ khrn_image_get_log2_brcm2_width (int /*<<< orphan*/ ) ; 

uint32_t khrn_image_get_log2_brcm1_width(KHRN_IMAGE_FORMAT_T format)
{
   return khrn_image_get_log2_brcm2_width(format) + 3;
}