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

__attribute__((used)) static void interpolate_delay(float *dst, float current, float prev, int index)
{
    static const float d_interpolation_factors[] = { 0, 0.3313, 0.6625, 1, 1 };
    dst[0] = (1.0 - d_interpolation_factors[index    ]) * prev
                  + d_interpolation_factors[index    ]  * current;
    dst[1] = (1.0 - d_interpolation_factors[index + 1]) * prev
                  + d_interpolation_factors[index + 1]  * current;
    dst[2] = (1.0 - d_interpolation_factors[index + 2]) * prev
                  + d_interpolation_factors[index + 2]  * current;
}