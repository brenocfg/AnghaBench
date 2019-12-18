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
typedef  int int32_t ;

/* Variables and functions */
 int FFMIN (int,int) ; 
 int HDCD_ANA_CDT ; 
 int HDCD_ANA_LLE ; 
 int HDCD_ANA_PE ; 
 int HDCD_ANA_TGM ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int hdcd_analyze_gen (int,int,int const) ; 

__attribute__((used)) static int hdcd_analyze(int32_t *samples, int count, int stride, int gain, int target_gain, int extend, int mode, int cdt_active, int tg_mismatch)
{
    static const int maxg = 0xf << 7;
    int i;
    int32_t *samples_end = samples + stride * count;

    for (i = 0; i < count; i++) {
        samples[i * stride] <<= 15;
        if (mode == HDCD_ANA_PE) {
            int pel = (samples[i * stride] >> 16) & 1;
            int32_t sample = samples[i * stride];
            samples[i * stride] = hdcd_analyze_gen(sample, !!(pel && extend), 1);
        } else if (mode == HDCD_ANA_TGM && tg_mismatch > 0)
            samples[i * stride] = hdcd_analyze_gen(samples[i * stride], 1, 1);
          else if (mode == HDCD_ANA_CDT && cdt_active)
            samples[i * stride] = hdcd_analyze_gen(samples[i * stride], 1, 1);
    }

    if (gain <= target_gain) {
        int len = FFMIN(count, target_gain - gain);
        /* attenuate slowly */
        for (i = 0; i < len; i++) {
            ++gain;
            if (mode == HDCD_ANA_LLE)
                *samples = hdcd_analyze_gen(*samples, gain, maxg);
            samples += stride;
        }
        count -= len;
    } else {
        int len = FFMIN(count, (gain - target_gain) >> 3);
        /* amplify quickly */
        for (i = 0; i < len; i++) {
            gain -= 8;
            if (mode == HDCD_ANA_LLE)
                *samples = hdcd_analyze_gen(*samples, gain, maxg);
            samples += stride;
        }
        if (gain - 8 < target_gain)
            gain = target_gain;
        count -= len;
    }

    /* hold a steady level */
    if (gain == 0) {
        if (count > 0)
            samples += count * stride;
    } else {
        while (--count >= 0) {
            if (mode == HDCD_ANA_LLE)
                *samples = hdcd_analyze_gen(*samples, gain, maxg);
            samples += stride;
        }
    }

    av_assert0(samples == samples_end);

    return gain;
}