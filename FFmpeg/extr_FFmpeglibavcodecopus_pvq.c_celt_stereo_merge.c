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
 float sqrtf (float) ; 

__attribute__((used)) static inline void celt_stereo_merge(float *X, float *Y, float mid, int N)
{
    int i;
    float xp = 0, side = 0;
    float E[2];
    float mid2;
    float gain[2];

    /* Compute the norm of X+Y and X-Y as |X|^2 + |Y|^2 +/- sum(xy) */
    for (i = 0; i < N; i++) {
        xp   += X[i] * Y[i];
        side += Y[i] * Y[i];
    }

    /* Compensating for the mid normalization */
    xp *= mid;
    mid2 = mid;
    E[0] = mid2 * mid2 + side - 2 * xp;
    E[1] = mid2 * mid2 + side + 2 * xp;
    if (E[0] < 6e-4f || E[1] < 6e-4f) {
        for (i = 0; i < N; i++)
            Y[i] = X[i];
        return;
    }

    gain[0] = 1.0f / sqrtf(E[0]);
    gain[1] = 1.0f / sqrtf(E[1]);

    for (i = 0; i < N; i++) {
        float value[2];
        /* Apply mid scaling (side is already scaled) */
        value[0] = mid * X[i];
        value[1] = Y[i];
        X[i] = gain[0] * (value[0] - value[1]);
        Y[i] = gain[1] * (value[0] + value[1]);
    }
}