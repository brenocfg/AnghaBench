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

/* Variables and functions */

__attribute__((used)) static int color_distance(uint32_t a, uint32_t b)
{
    int r = 0, d, i;
    int alpha_a = 8, alpha_b = 8;

    for (i = 24; i >= 0; i -= 8) {
        d = alpha_a * (int)((a >> i) & 0xFF) -
            alpha_b * (int)((b >> i) & 0xFF);
        r += d * d;
        alpha_a = a >> 28;
        alpha_b = b >> 28;
    }
    return r;
}