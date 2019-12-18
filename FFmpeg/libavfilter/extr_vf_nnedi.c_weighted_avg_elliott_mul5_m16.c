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
 float FFABS (float const) ; 
 float min_weight_sum ; 

__attribute__((used)) static void weighted_avg_elliott_mul5_m16(const float *w, const int n, float *mstd)
{
    float vsum = 0.0f, wsum = 0.0f;
    int i;

    for (i = 0; i < n; i++) {
        vsum += w[i] * (w[n + i] / (1.0f + FFABS(w[n + i])));
        wsum += w[i];
    }
    if (wsum > min_weight_sum)
        mstd[3] += ((5.0f * vsum) / wsum) * mstd[1] + mstd[0];
    else
        mstd[3] += mstd[0];
}