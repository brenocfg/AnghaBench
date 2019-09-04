#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_3__ {int rate; int _ana_snb; } ;
typedef  TYPE_1__ hdcd_state ;

/* Variables and functions */
 scalar_t__ PEAK_EXT_LEVEL ; 
 int TONEGEN16 (int,int,int,double) ; 
 scalar_t__ abs (int) ; 

__attribute__((used)) static void hdcd_analyze_prepare(hdcd_state *state, int32_t *samples, int count, int stride) {
    int n, f = 300;
    int so = state->rate / f;
    for (n = 0; n < count * stride; n += stride) {
        /* in analyze mode, the audio is replaced by a solid tone, and
         * amplitude is changed to signal when the specified feature is
         * used.
         * bit 0: HDCD signal preserved
         * bit 1: Original sample was above PE level */
        int32_t save = (abs(samples[n]) - PEAK_EXT_LEVEL >= 0) ? 2 : 0; /* above PE level */
        save |= samples[n] & 1;                      /* save LSB for HDCD packets */
        samples[n] = TONEGEN16(state->_ana_snb, f, state->rate, 0.1);
        samples[n] = (samples[n] | 3) ^ ((~save) & 3);
        if (++state->_ana_snb > so) state->_ana_snb = 0;
    }
}