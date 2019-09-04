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
union av_intfloat32 {unsigned int i; } ;

/* Variables and functions */

__attribute__((used)) static void sbr_qmf_deint_neg_c(float *v, const float *src)
{
    const union av_intfloat32 *si = (const union av_intfloat32*)src;
    union av_intfloat32 *vi = (union av_intfloat32*)v;
    int i;
    for (i = 0; i < 32; i++) {
        vi[     i].i = si[63 - 2 * i    ].i;
        vi[63 - i].i = si[63 - 2 * i - 1].i ^ (1U << 31);
    }
}