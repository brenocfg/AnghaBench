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
 float FFMIN (float,int) ; 
 int LP_ORDER ; 
 int LP_ORDER_16k ; 
 float auto_correlation (float*,float,int) ; 

__attribute__((used)) static void extrapolate_isf(float isf[LP_ORDER_16k])
{
    float diff_isf[LP_ORDER - 2], diff_mean;
    float corr_lag[3];
    float est, scale;
    int i, j, i_max_corr;

    isf[LP_ORDER_16k - 1] = isf[LP_ORDER - 1];

    /* Calculate the difference vector */
    for (i = 0; i < LP_ORDER - 2; i++)
        diff_isf[i] = isf[i + 1] - isf[i];

    diff_mean = 0.0;
    for (i = 2; i < LP_ORDER - 2; i++)
        diff_mean += diff_isf[i] * (1.0f / (LP_ORDER - 4));

    /* Find which is the maximum autocorrelation */
    i_max_corr = 0;
    for (i = 0; i < 3; i++) {
        corr_lag[i] = auto_correlation(diff_isf, diff_mean, i + 2);

        if (corr_lag[i] > corr_lag[i_max_corr])
            i_max_corr = i;
    }
    i_max_corr++;

    for (i = LP_ORDER - 1; i < LP_ORDER_16k - 1; i++)
        isf[i] = isf[i - 1] + isf[i - 1 - i_max_corr]
                            - isf[i - 2 - i_max_corr];

    /* Calculate an estimate for ISF(18) and scale ISF based on the error */
    est   = 7965 + (isf[2] - isf[3] - isf[4]) / 6.0;
    scale = 0.5 * (FFMIN(est, 7600) - isf[LP_ORDER - 2]) /
            (isf[LP_ORDER_16k - 2] - isf[LP_ORDER - 2]);

    for (i = LP_ORDER - 1, j = 0; i < LP_ORDER_16k - 1; i++, j++)
        diff_isf[j] = scale * (isf[i] - isf[i - 1]);

    /* Stability insurance */
    for (i = 1; i < LP_ORDER_16k - LP_ORDER; i++)
        if (diff_isf[i] + diff_isf[i - 1] < 5.0) {
            if (diff_isf[i] > diff_isf[i - 1]) {
                diff_isf[i - 1] = 5.0 - diff_isf[i];
            } else
                diff_isf[i] = 5.0 - diff_isf[i - 1];
        }

    for (i = LP_ORDER - 1, j = 0; i < LP_ORDER_16k - 1; i++, j++)
        isf[i] = isf[i - 1] + diff_isf[j] * (1.0f / (1 << 15));

    /* Scale the ISF vector for 16000 Hz */
    for (i = 0; i < LP_ORDER_16k - 1; i++)
        isf[i] *= 0.8;
}