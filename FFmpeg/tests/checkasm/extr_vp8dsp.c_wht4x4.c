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

__attribute__((used)) static void wht4x4(int16_t *coef)
{
    int i;
    for (i = 0; i < 4; i++) {
        int a1 = coef[0 * 4 + i];
        int b1 = coef[1 * 4 + i];
        int c1 = coef[2 * 4 + i];
        int d1 = coef[3 * 4 + i];
        int e1;
        a1 += b1;
        d1 -= c1;
        e1 = (a1 - d1) >> 1;
        b1 = e1 - b1;
        c1 = e1 - c1;
        a1 -= c1;
        d1 += b1;
        coef[0 * 4 + i] = a1;
        coef[1 * 4 + i] = c1;
        coef[2 * 4 + i] = d1;
        coef[3 * 4 + i] = b1;
    }
    for (i = 0; i < 4; i++) {
        int a1 = coef[i * 4 + 0];
        int b1 = coef[i * 4 + 1];
        int c1 = coef[i * 4 + 2];
        int d1 = coef[i * 4 + 3];
        int e1;
        a1 += b1;
        d1 -= c1;
        e1 = (a1 - d1) >> 1;
        b1 = e1 - b1;
        c1 = e1 - c1;
        a1 -= c1;
        d1 += b1;
        coef[i * 4 + 0] = a1 * 2;
        coef[i * 4 + 1] = c1 * 2;
        coef[i * 4 + 2] = d1 * 2;
        coef[i * 4 + 3] = b1 * 2;
    }
}