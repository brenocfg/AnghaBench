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

void ff_acelp_interpolatef(float *out, const float *in,
                           const float *filter_coeffs, int precision,
                           int frac_pos, int filter_length, int length)
{
    int n, i;

    for (n = 0; n < length; n++) {
        int idx = 0;
        float v = 0;

        for (i = 0; i < filter_length;) {
            v += in[n + i] * filter_coeffs[idx + frac_pos];
            idx += precision;
            i++;
            v += in[n - i] * filter_coeffs[idx - frac_pos];
        }
        out[n] = v;
    }
}