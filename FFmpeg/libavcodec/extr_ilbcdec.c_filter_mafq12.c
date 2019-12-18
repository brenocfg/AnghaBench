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
 int av_clip (int,int,int) ; 

__attribute__((used)) static void filter_mafq12(int16_t *in_ptr, int16_t *out_ptr,
                          int16_t *B, int16_t B_length,
                          int16_t length)
{
    int o, i, j;

    for (i = 0; i < length; i++) {
        const int16_t *b_ptr = &B[0];
        const int16_t *x_ptr = &in_ptr[i];

        o = 0;
        for (j = 0; j < B_length; j++)
            o += b_ptr[j] * *x_ptr--;

        o = av_clip(o, -134217728, 134215679);

        out_ptr[i] = ((o + 2048) >> 12);
    }
}