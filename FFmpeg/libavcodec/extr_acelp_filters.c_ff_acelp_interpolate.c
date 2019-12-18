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
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  av_assert1 (int) ; 
 int av_clip_int16 (int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

void ff_acelp_interpolate(int16_t* out, const int16_t* in,
                          const int16_t* filter_coeffs, int precision,
                          int frac_pos, int filter_length, int length)
{
    int n, i;

    av_assert1(frac_pos >= 0 && frac_pos < precision);

    for (n = 0; n < length; n++) {
        int idx = 0;
        int v = 0x4000;

        for (i = 0; i < filter_length;) {

            /* The reference G.729 and AMR fixed point code performs clipping after
               each of the two following accumulations.
               Since clipping affects only the synthetic OVERFLOW test without
               causing an int type overflow, it was moved outside the loop. */

            /*  R(x):=ac_v[-k+x]
                v += R(n-i)*ff_acelp_interp_filter(t+6i)
                v += R(n+i+1)*ff_acelp_interp_filter(6-t+6i) */

            v += in[n + i] * filter_coeffs[idx + frac_pos];
            idx += precision;
            i++;
            v += in[n - i] * filter_coeffs[idx - frac_pos];
        }
        if (av_clip_int16(v >> 15) != (v >> 15))
            av_log(NULL, AV_LOG_WARNING, "overflow that would need clipping in ff_acelp_interpolate()\n");
        out[n] = v >> 15;
    }
}