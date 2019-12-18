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
 scalar_t__ FFABS (int) ; 
 int G729_TILT_FACTOR_MINUS ; 
 int G729_TILT_FACTOR_PLUS ; 
 int av_clip_int16 (scalar_t__) ; 

__attribute__((used)) static int16_t apply_tilt_comp(int16_t* out, int16_t* res_pst, int refl_coeff,
                               int subframe_size, int16_t ht_prev_data)
{
    int tmp, tmp2;
    int i;
    int gt, ga;
    int fact, sh_fact;

    if (refl_coeff > 0) {
        gt = (refl_coeff * G729_TILT_FACTOR_PLUS + 0x4000) >> 15;
        fact = 0x4000; // 0.5 in (0.15)
        sh_fact = 15;
    } else {
        gt = (refl_coeff * G729_TILT_FACTOR_MINUS + 0x4000) >> 15;
        fact = 0x800; // 0.5 in (3.12)
        sh_fact = 12;
    }
    ga = (fact << 15) / av_clip_int16(32768 - FFABS(gt));
    gt >>= 1;

    /* Apply tilt compensation filter to signal. */
    tmp = res_pst[subframe_size - 1];

    for (i = subframe_size - 1; i >= 1; i--) {
        tmp2 = (gt * res_pst[i-1]) * 2 + 0x4000;
        tmp2 = res_pst[i] + (tmp2 >> 15);

        tmp2 = (tmp2 * ga * 2 + fact) >> sh_fact;
        out[i] = tmp2;
    }
    tmp2 = (gt * ht_prev_data) * 2 + 0x4000;
    tmp2 = res_pst[0] + (tmp2 >> 15);
    tmp2 = (tmp2 * ga * 2 + fact) >> sh_fact;
    out[0] = tmp2;

    return tmp;
}