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

__attribute__((used)) static float map(int x, int in_min, int in_max, float out_min, float out_max)
{
    double slope, output;

    slope = 1.0 * (out_max - out_min) / (in_max - in_min);
    output = out_min + slope * (x - in_min);

    return (float)output;
}