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

__attribute__((used)) static float sbr_sum_square_c(float (*x)[2], int n)
{
    float sum0 = 0.0f, sum1 = 0.0f;
    int i;

    for (i = 0; i < n; i += 2)
    {
        sum0 += x[i + 0][0] * x[i + 0][0];
        sum1 += x[i + 0][1] * x[i + 0][1];
        sum0 += x[i + 1][0] * x[i + 1][0];
        sum1 += x[i + 1][1] * x[i + 1][1];
    }

    return sum0 + sum1;
}