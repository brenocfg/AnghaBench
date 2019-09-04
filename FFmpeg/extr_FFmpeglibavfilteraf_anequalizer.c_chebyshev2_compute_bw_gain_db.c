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

__attribute__((used)) static double chebyshev2_compute_bw_gain_db(double gain)
{
    double bw_gain = 0;

    if (gain <= -6)
        bw_gain = -3;
    else if(gain > -6 && gain < 6)
        bw_gain = gain * 0.3;
    else if(gain >= 6)
        bw_gain = 3;

    return bw_gain;
}