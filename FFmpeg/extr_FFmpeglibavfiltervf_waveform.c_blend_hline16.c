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
typedef  float uint16_t ;

/* Variables and functions */

__attribute__((used)) static void blend_hline16(uint16_t *dst, int width, float o1, float o2, int v, int step)
{
    int x;

    for (x = 0; x < width; x += step) {
        dst[x] = v * o1 + dst[x] * o2;
    }
}