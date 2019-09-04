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

__attribute__((used)) static void predict(float *samples, const float *coeff, int nsamples)
{
    int i, j;

    for (i = 0; i < nsamples; i++) {
        float res = 0;
        for (j = 0; j < 8; j++)
            res += coeff[j] * samples[i - j - 1];
        samples[i] -= res;
    }
}