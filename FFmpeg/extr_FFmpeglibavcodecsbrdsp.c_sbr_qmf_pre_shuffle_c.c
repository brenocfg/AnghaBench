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

__attribute__((used)) static void sbr_qmf_pre_shuffle_c(float *z)
{
    union av_intfloat32 *zi = (union av_intfloat32*) z;
    int k;
    zi[64].i = zi[0].i;
    zi[65].i = zi[1].i;
    for (k = 1; k < 31; k += 2) {
        zi[64 + 2 * k + 0].i = zi[64 - k].i ^ (1U << 31);
        zi[64 + 2 * k + 1].i = zi[ k + 1].i;
        zi[64 + 2 * k + 2].i = zi[63 - k].i ^ (1U << 31);
        zi[64 + 2 * k + 3].i = zi[ k + 2].i;
    }

    zi[64 + 2 * 31 + 0].i = zi[64 - 31].i ^ (1U << 31);
    zi[64 + 2 * 31 + 1].i = zi[31 +  1].i;
}