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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  unsigned int uint16_t ;

/* Variables and functions */

void rgb16tobgr16(const uint8_t *src, uint8_t *dst, int src_size)
{
    int i, num_pixels = src_size >> 1;

    for (i = 0; i < num_pixels; i++) {
        unsigned rgb         = ((const uint16_t *)src)[i];
        ((uint16_t *)dst)[i] = (rgb >> 11) | (rgb & 0x7E0) | (rgb << 11);
    }
}