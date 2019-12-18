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

__attribute__((used)) static void sbr_hf_gen_c(float (*X_high)[2], const float (*X_low)[2],
                         const float alpha0[2], const float alpha1[2],
                         float bw, int start, int end)
{
    float alpha[4];
    int i;

    alpha[0] = alpha1[0] * bw * bw;
    alpha[1] = alpha1[1] * bw * bw;
    alpha[2] = alpha0[0] * bw;
    alpha[3] = alpha0[1] * bw;

    for (i = start; i < end; i++) {
        X_high[i][0] =
            X_low[i - 2][0] * alpha[0] -
            X_low[i - 2][1] * alpha[1] +
            X_low[i - 1][0] * alpha[2] -
            X_low[i - 1][1] * alpha[3] +
            X_low[i][0];
        X_high[i][1] =
            X_low[i - 2][1] * alpha[0] +
            X_low[i - 2][0] * alpha[1] +
            X_low[i - 1][1] * alpha[2] +
            X_low[i - 1][0] * alpha[3] +
            X_low[i][1];
    }
}