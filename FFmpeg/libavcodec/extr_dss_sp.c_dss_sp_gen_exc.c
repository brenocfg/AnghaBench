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
 int av_clip_int16 (int) ; 

__attribute__((used)) static void dss_sp_gen_exc(int32_t *vector, int32_t *prev_exc,
                           int pitch_lag, int gain)
{
    int i;

    /* do we actually need this check? we can use just [a3 - i % a3]
     * for both cases */
    if (pitch_lag < 72)
        for (i = 0; i < 72; i++)
            vector[i] = prev_exc[pitch_lag - i % pitch_lag];
    else
        for (i = 0; i < 72; i++)
            vector[i] = prev_exc[pitch_lag - i];

    for (i = 0; i < 72; i++) {
        int tmp = gain * vector[i] >> 11;
        vector[i] = av_clip_int16(tmp);
    }
}