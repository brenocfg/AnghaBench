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

__attribute__((used)) static void biquad(float *y, float mem[2], const float *x,
                   const float *b, const float *a, int N)
{
    for (int i = 0; i < N; i++) {
        float xi, yi;

        xi = x[i];
        yi = x[i] + mem[0];
        mem[0] = mem[1] + (b[0]*xi - a[0]*yi);
        mem[1] = (b[1]*xi - a[1]*yi);
        y[i] = yi;
    }
}