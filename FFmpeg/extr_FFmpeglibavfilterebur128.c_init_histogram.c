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
 void** histogram_energies ; 
 void** histogram_energy_boundaries ; 
 void* pow (double,double) ; 

__attribute__((used)) static inline void init_histogram(void)
{
    int i;
    /* initialize static constants */
    histogram_energy_boundaries[0] = pow(10.0, (-70.0 + 0.691) / 10.0);
    for (i = 0; i < 1000; ++i) {
        histogram_energies[i] =
            pow(10.0, ((double) i / 10.0 - 69.95 + 0.691) / 10.0);
    }
    for (i = 1; i < 1001; ++i) {
        histogram_energy_boundaries[i] =
            pow(10.0, ((double) i / 10.0 - 70.0 + 0.691) / 10.0);
    }
}