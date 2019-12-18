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
typedef  size_t uint16_t ;

/* Variables and functions */

__attribute__((used)) static void apply_lut(const uint16_t *lut, uint16_t *dst, int dsize)
{
    int i;

    for (i = 0; i < dsize; ++i)
        dst[i] = lut[dst[i]];
}