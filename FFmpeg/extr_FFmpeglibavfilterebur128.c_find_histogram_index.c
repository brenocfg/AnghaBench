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
 double* histogram_energy_boundaries ; 

__attribute__((used)) static size_t find_histogram_index(double energy)
{
    size_t index_min = 0;
    size_t index_max = 1000;
    size_t index_mid;

    do {
        index_mid = (index_min + index_max) / 2;
        if (energy >= histogram_energy_boundaries[index_mid]) {
            index_min = index_mid;
        } else {
            index_max = index_mid;
        }
    } while (index_max - index_min != 1);

    return index_min;
}