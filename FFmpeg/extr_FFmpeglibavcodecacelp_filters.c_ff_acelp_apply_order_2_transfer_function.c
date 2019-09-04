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

void ff_acelp_apply_order_2_transfer_function(float *out, const float *in,
                                              const float zero_coeffs[2],
                                              const float pole_coeffs[2],
                                              float gain, float mem[2], int n)
{
    int i;
    float tmp;

    for (i = 0; i < n; i++) {
        tmp = gain * in[i] - pole_coeffs[0] * mem[0] - pole_coeffs[1] * mem[1];
        out[i] =       tmp + zero_coeffs[0] * mem[0] + zero_coeffs[1] * mem[1];

        mem[1] = mem[0];
        mem[0] = tmp;
    }
}