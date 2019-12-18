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

__attribute__((used)) static void sbr_qmf_post_shuffle_c(float W[32][2], const float *z)
{
    const union av_intfloat32 *zi = (const union av_intfloat32*) z;
    union av_intfloat32 *Wi       = (union av_intfloat32*) W;
    int k;
    for (k = 0; k < 32; k += 2) {
        Wi[2 * k + 0].i = zi[63 - k].i ^ (1U << 31);
        Wi[2 * k + 1].i = zi[ k + 0].i;
        Wi[2 * k + 2].i = zi[62 - k].i ^ (1U << 31);
        Wi[2 * k + 3].i = zi[ k + 1].i;
    }
}