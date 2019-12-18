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

__attribute__((used)) static void autocorrelation(const double *input, int order, int size,
                            double *output, double scale)
{
    int i, j;

    for (i = 0; i <= order; i++) {
        double value = 0.;

        for (j = i; j < size; j++)
            value += input[j] * input[j - i];

        output[i] = value * scale;
    }
}