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
typedef  int /*<<< orphan*/  FFEBUR128State ;

/* Variables and functions */
 double HUGE_VAL ; 
 int ebur128_energy_shortterm (int /*<<< orphan*/ *,double*) ; 
 double ebur128_energy_to_loudness (double) ; 

int ff_ebur128_loudness_shortterm(FFEBUR128State * st, double *out)
{
    double energy;
    int error = ebur128_energy_shortterm(st, &energy);
    if (error) {
        return error;
    } else if (energy <= 0.0) {
        *out = -HUGE_VAL;
        return 0;
    }
    *out = ebur128_energy_to_loudness(energy);
    return 0;
}