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
 float M_PI ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 float* av_calloc (int,int) ; 
 float bessel_I_0 (float) ; 
 float sinf (float) ; 
 float sqrtf (float) ; 

__attribute__((used)) static float *make_lpf(int num_taps, float Fc, float beta, float rho,
                       float scale, int dc_norm)
{
    int i, m = num_taps - 1;
    float *h = av_calloc(num_taps, sizeof(*h)), sum = 0;
    float mult = scale / bessel_I_0(beta), mult1 = 1.f / (.5f * m + rho);

    av_assert0(Fc >= 0 && Fc <= 1);

    for (i = 0; i <= m / 2; i++) {
        float z = i - .5f * m, x = z * M_PI, y = z * mult1;
        h[i] = x ? sinf(Fc * x) / x : Fc;
        sum += h[i] *= bessel_I_0(beta * sqrtf(1.f - y * y)) * mult;
        if (m - i != i) {
            h[m - i] = h[i];
            sum += h[i];
        }
    }

    for (i = 0; dc_norm && i < num_taps; i++)
        h[i] *= scale / sum;

    return h;
}