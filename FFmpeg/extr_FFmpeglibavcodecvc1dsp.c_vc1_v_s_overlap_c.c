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
typedef  int int16_t ;

/* Variables and functions */

__attribute__((used)) static void vc1_v_s_overlap_c(int16_t *top, int16_t *bottom)
{
    int i;
    int a, b, c, d;
    int d1, d2;
    int rnd1 = 4, rnd2 = 3;
    for (i = 0; i < 8; i++) {
        a  = top[48];
        b  = top[56];
        c  = bottom[0];
        d  = bottom[8];
        d1 = a - d;
        d2 = a - d + b - c;

        top[48]   = ((a << 3) - d1 + rnd1) >> 3;
        top[56]   = ((b << 3) - d2 + rnd2) >> 3;
        bottom[0] = ((c << 3) + d2 + rnd1) >> 3;
        bottom[8] = ((d << 3) + d1 + rnd2) >> 3;

        bottom++;
        top++;
        rnd2 = 7 - rnd2;
        rnd1 = 7 - rnd1;
    }
}