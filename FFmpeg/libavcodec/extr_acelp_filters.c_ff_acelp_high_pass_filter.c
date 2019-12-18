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
 int av_clip_int16 (int) ; 

void ff_acelp_high_pass_filter(int16_t* out, int hpf_f[2],
                               const int16_t* in, int length)
{
    int i;
    int tmp;

    for (i = 0; i < length; i++) {
        tmp  = (hpf_f[0]* 15836LL) >> 13;
        tmp += (hpf_f[1]* -7667LL) >> 13;
        tmp += 7699 * (in[i] - 2*in[i-1] + in[i-2]);

        /* With "+0x800" rounding, clipping is needed
           for ALGTHM and SPEECH tests. */
        out[i] = av_clip_int16((tmp + 0x800) >> 12);

        hpf_f[1] = hpf_f[0];
        hpf_f[0] = tmp;
    }
}