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

__attribute__((used)) static void dct4x4(int16_t *coef)
{
    int i;
    for (i = 0; i < 4; i++) {
        const int a1 = (coef[i*4 + 0] + coef[i*4 + 3]) * 8;
        const int b1 = (coef[i*4 + 1] + coef[i*4 + 2]) * 8;
        const int c1 = (coef[i*4 + 1] - coef[i*4 + 2]) * 8;
        const int d1 = (coef[i*4 + 0] - coef[i*4 + 3]) * 8;
        coef[i*4 + 0] =  a1 + b1;
        coef[i*4 + 1] = (c1 * 2217 + d1 * 5352 + 14500) >> 12;
        coef[i*4 + 2] =  a1 - b1;
        coef[i*4 + 3] = (d1 * 2217 - c1 * 5352 +  7500) >> 12;
    }
    for (i = 0; i < 4; i++) {
        const int a1 = coef[i + 0*4] + coef[i + 3*4];
        const int b1 = coef[i + 1*4] + coef[i + 2*4];
        const int c1 = coef[i + 1*4] - coef[i + 2*4];
        const int d1 = coef[i + 0*4] - coef[i + 3*4];
        coef[i + 0*4] =  (a1 + b1 + 7) >> 4;
        coef[i + 1*4] = ((c1 * 2217 + d1 * 5352 + 12000) >> 16) + !!d1;
        coef[i + 2*4] =  (a1 - b1 + 7) >> 4;
        coef[i + 3*4] =  (d1 * 2217 - c1 * 5352 + 51000) >> 16;
    }
}