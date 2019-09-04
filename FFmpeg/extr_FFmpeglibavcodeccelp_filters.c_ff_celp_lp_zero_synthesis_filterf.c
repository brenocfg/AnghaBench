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

void ff_celp_lp_zero_synthesis_filterf(float *out, const float *filter_coeffs,
                                       const float *in, int buffer_length,
                                       int filter_length)
{
    int i,n;

    for (n = 0; n < buffer_length; n++) {
        out[n] = in[n];
        for (i = 1; i <= filter_length; i++)
            out[n] += filter_coeffs[i-1] * in[n-i];
    }
}