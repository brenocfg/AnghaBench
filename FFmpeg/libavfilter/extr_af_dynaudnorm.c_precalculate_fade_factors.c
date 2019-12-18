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

__attribute__((used)) static void precalculate_fade_factors(double *fade_factors[2], int frame_len)
{
    const double step_size = 1.0 / frame_len;
    int pos;

    for (pos = 0; pos < frame_len; pos++) {
        fade_factors[0][pos] = 1.0 - (step_size * (pos + 1.0));
        fade_factors[1][pos] = 1.0 - fade_factors[0][pos];
    }
}