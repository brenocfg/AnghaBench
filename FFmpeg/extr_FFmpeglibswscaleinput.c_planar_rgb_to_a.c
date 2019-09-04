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
typedef  int uint8_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */

__attribute__((used)) static void planar_rgb_to_a(uint8_t *_dst, const uint8_t *src[4], int width, int32_t *unused)
{
    uint16_t *dst = (uint16_t *)_dst;
    int i;
    for (i = 0; i < width; i++)
        dst[i] = src[3][i] << 6;
}