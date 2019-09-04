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

__attribute__((used)) static void sbr_autocorrelate_c(const float x[40][2], float phi[3][2][2])
{
    float real_sum2 = x[0][0] * x[2][0] + x[0][1] * x[2][1];
    float imag_sum2 = x[0][0] * x[2][1] - x[0][1] * x[2][0];
    float real_sum1 = 0.0f, imag_sum1 = 0.0f, real_sum0 = 0.0f;
    int   i;
    for (i = 1; i < 38; i++) {
        real_sum0 += x[i][0] * x[i    ][0] + x[i][1] * x[i    ][1];
        real_sum1 += x[i][0] * x[i + 1][0] + x[i][1] * x[i + 1][1];
        imag_sum1 += x[i][0] * x[i + 1][1] - x[i][1] * x[i + 1][0];
        real_sum2 += x[i][0] * x[i + 2][0] + x[i][1] * x[i + 2][1];
        imag_sum2 += x[i][0] * x[i + 2][1] - x[i][1] * x[i + 2][0];
    }
    phi[2 - 2][1][0] = real_sum2;
    phi[2 - 2][1][1] = imag_sum2;
    phi[2    ][1][0] = real_sum0 + x[ 0][0] * x[ 0][0] + x[ 0][1] * x[ 0][1];
    phi[1    ][0][0] = real_sum0 + x[38][0] * x[38][0] + x[38][1] * x[38][1];
    phi[2 - 1][1][0] = real_sum1 + x[ 0][0] * x[ 1][0] + x[ 0][1] * x[ 1][1];
    phi[2 - 1][1][1] = imag_sum1 + x[ 0][0] * x[ 1][1] - x[ 0][1] * x[ 1][0];
    phi[0    ][0][0] = real_sum1 + x[38][0] * x[39][0] + x[38][1] * x[39][1];
    phi[0    ][0][1] = imag_sum1 + x[38][0] * x[39][1] - x[38][1] * x[39][0];
}