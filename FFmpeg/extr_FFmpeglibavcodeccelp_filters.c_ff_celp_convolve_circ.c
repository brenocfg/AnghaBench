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
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

void ff_celp_convolve_circ(int16_t* fc_out, const int16_t* fc_in,
                           const int16_t* filter, int len)
{
    int i, k;

    memset(fc_out, 0, len * sizeof(int16_t));

    /* Since there are few pulses over an entire subframe (i.e. almost
       all fc_in[i] are zero) it is faster to loop over fc_in first. */
    for (i = 0; i < len; i++) {
        if (fc_in[i]) {
            for (k = 0; k < i; k++)
                fc_out[k] += (fc_in[i] * filter[len + k - i]) >> 15;

            for (k = i; k < len; k++)
                fc_out[k] += (fc_in[i] * filter[      k - i]) >> 15;
        }
    }
}