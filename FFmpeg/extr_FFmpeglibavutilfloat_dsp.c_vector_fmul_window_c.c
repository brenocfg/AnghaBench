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

/* Variables and functions */

__attribute__((used)) static void vector_fmul_window_c(float *dst, const float *src0,
                                 const float *src1, const float *win, int len)
{
    int i, j;

    dst  += len;
    win  += len;
    src0 += len;

    for (i = -len, j = len - 1; i < 0; i++, j--) {
        float s0 = src0[i];
        float s1 = src1[j];
        float wi = win[i];
        float wj = win[j];
        dst[i] = s0 * wj - s1 * wi;
        dst[j] = s0 * wi + s1 * wj;
    }
}