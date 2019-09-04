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
 int FFABS (int const) ; 
 int FFMAX (int,int /*<<< orphan*/ ) ; 
 int av_log2_16bit (int) ; 

int ff_g723_1_scale_vector(int16_t *dst, const int16_t *vector, int length)
{
    int bits, max = 0;
    int i;

    for (i = 0; i < length; i++)
        max |= FFABS(vector[i]);

    bits= 14 - av_log2_16bit(max);
    bits= FFMAX(bits, 0);

    for (i = 0; i < length; i++)
        dst[i] = (vector[i] * (1 << bits)) >> 3;

    return bits - 3;
}