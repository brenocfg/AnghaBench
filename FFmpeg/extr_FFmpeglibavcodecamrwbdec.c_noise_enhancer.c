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
 float FFMAX (float,float) ; 
 float FFMIN (float,float) ; 

__attribute__((used)) static float noise_enhancer(float fixed_gain, float *prev_tr_gain,
                            float voice_fac,  float stab_fac)
{
    float sm_fac = 0.5 * (1 - voice_fac) * stab_fac;
    float g0;

    // XXX: the following fixed-point constants used to in(de)crement
    // gain by 1.5dB were taken from the reference code, maybe it could
    // be simpler
    if (fixed_gain < *prev_tr_gain) {
        g0 = FFMIN(*prev_tr_gain, fixed_gain + fixed_gain *
                     (6226 * (1.0f / (1 << 15)))); // +1.5 dB
    } else
        g0 = FFMAX(*prev_tr_gain, fixed_gain *
                    (27536 * (1.0f / (1 << 15)))); // -1.5 dB

    *prev_tr_gain = g0; // update next frame threshold

    return sm_fac * g0 + (1 - sm_fac) * fixed_gain;
}