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

__attribute__((used)) static void postfilter_c(float *data, int period, float *gains, int len)
{
    const float g0 = gains[0];
    const float g1 = gains[1];
    const float g2 = gains[2];

    float x4 = data[-period - 2];
    float x3 = data[-period - 1];
    float x2 = data[-period + 0];
    float x1 = data[-period + 1];

    for (int i = 0; i < len; i++) {
        float x0 = data[i - period + 2];
        data[i] += g0 * x2        +
                   g1 * (x1 + x3) +
                   g2 * (x0 + x4);
        x4 = x3;
        x3 = x2;
        x2 = x1;
        x1 = x0;
    }
}