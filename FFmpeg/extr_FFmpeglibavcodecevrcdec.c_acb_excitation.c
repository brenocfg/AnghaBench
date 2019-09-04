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
typedef  int /*<<< orphan*/  EVRCContext ;

/* Variables and functions */
 int /*<<< orphan*/  bl_intrp (int /*<<< orphan*/ *,float*,float) ; 

__attribute__((used)) static void acb_excitation(EVRCContext *e, float *excitation, float gain,
                           const float delay[3], int length)
{
    float denom, locdelay, dpr, invl;
    int i;

    invl = 1.0 / ((float) length);
    dpr = length;

    /* first at-most extra samples */
    denom = (delay[1] - delay[0]) * invl;
    for (i = 0; i < dpr; i++) {
        locdelay = delay[0] + i * denom;
        bl_intrp(e, excitation + i, locdelay);
    }

    denom = (delay[2] - delay[1]) * invl;
    /* interpolation */
    for (i = dpr; i < dpr + 10; i++) {
        locdelay = delay[1] + (i - dpr) * denom;
        bl_intrp(e, excitation + i, locdelay);
    }

    for (i = 0; i < length; i++)
        excitation[i] *= gain;
}