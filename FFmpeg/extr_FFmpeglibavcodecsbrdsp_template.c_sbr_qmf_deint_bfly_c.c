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
typedef  scalar_t__ INTFLOAT ;

/* Variables and functions */

__attribute__((used)) static void sbr_qmf_deint_bfly_c(INTFLOAT *v, const INTFLOAT *src0, const INTFLOAT *src1)
{
    int i;
    for (i = 0; i < 64; i++) {
#if USE_FIXED
        v[      i] = (int)(0x10U + src0[i] - src1[63 - i]) >> 5;
        v[127 - i] = (int)(0x10U + src0[i] + src1[63 - i]) >> 5;
#else
        v[      i] = src0[i] - src1[63 - i];
        v[127 - i] = src0[i] + src1[63 - i];
#endif
    }
}