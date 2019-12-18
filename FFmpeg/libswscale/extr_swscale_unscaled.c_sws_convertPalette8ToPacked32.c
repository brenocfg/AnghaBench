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
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */

void sws_convertPalette8ToPacked32(const uint8_t *src, uint8_t *dst,
                                   int num_pixels, const uint8_t *palette)
{
    int i;

    for (i = 0; i < num_pixels; i++)
        ((uint32_t *) dst)[i] = ((const uint32_t *) palette)[src[i]];
}