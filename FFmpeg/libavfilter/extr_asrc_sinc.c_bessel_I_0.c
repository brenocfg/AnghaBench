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

__attribute__((used)) static float bessel_I_0(float x)
{
    float term = 1, sum = 1, last_sum, x2 = x / 2;
    int i = 1;

    do {
        float y = x2 / i++;

        last_sum = sum;
        sum += term *= y * y;
    } while (sum != last_sum);

    return sum;
}