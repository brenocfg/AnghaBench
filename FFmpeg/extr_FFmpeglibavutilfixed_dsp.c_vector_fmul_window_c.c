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
typedef  size_t int64_t ;
typedef  size_t int32_t ;

/* Variables and functions */

__attribute__((used)) static void vector_fmul_window_c(int32_t *dst, const int32_t *src0,
                                       const int32_t *src1, const int32_t *win,
                                       int len)
{
    int32_t s0, s1, wi, wj, i, j;

    dst += len;
    win += len;
    src0+= len;

    for (i=-len, j=len-1; i<0; i++, j--) {
        s0 = src0[i];
        s1 = src1[j];
        wi = win[i];
        wj = win[j];
        dst[i] = ((int64_t)s0*wj - (int64_t)s1*wi + 0x40000000) >> 31;
        dst[j] = ((int64_t)s0*wi + (int64_t)s1*wj + 0x40000000) >> 31;
    }
}