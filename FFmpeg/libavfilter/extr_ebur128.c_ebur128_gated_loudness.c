#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int mode; TYPE_1__* d; } ;
struct TYPE_5__ {double* block_energy_histogram; } ;
typedef  TYPE_2__ FFEBUR128State ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int FF_EBUR128_MODE_I ; 
 double HUGE_VAL ; 
 int /*<<< orphan*/  ebur128_calc_relative_threshold (TYPE_2__**,size_t,double*) ; 
 double ebur128_energy_to_loudness (double) ; 
 size_t find_histogram_index (double) ; 
 double* histogram_energies ; 
 double* histogram_energy_boundaries ; 

__attribute__((used)) static int ebur128_gated_loudness(FFEBUR128State ** sts, size_t size,
                                  double *out)
{
    double gated_loudness = 0.0;
    double relative_threshold;
    size_t above_thresh_counter;
    size_t i, j, start_index;

    for (i = 0; i < size; i++)
        if ((sts[i]->mode & FF_EBUR128_MODE_I) != FF_EBUR128_MODE_I)
            return AVERROR(EINVAL);

    if (!ebur128_calc_relative_threshold(sts, size, &relative_threshold)) {
        *out = -HUGE_VAL;
        return 0;
    }

    above_thresh_counter = 0;
    if (relative_threshold < histogram_energy_boundaries[0]) {
        start_index = 0;
    } else {
        start_index = find_histogram_index(relative_threshold);
        if (relative_threshold > histogram_energies[start_index]) {
            ++start_index;
        }
    }
    for (i = 0; i < size; i++) {
        for (j = start_index; j < 1000; ++j) {
            gated_loudness += sts[i]->d->block_energy_histogram[j] *
                histogram_energies[j];
            above_thresh_counter += sts[i]->d->block_energy_histogram[j];
        }
    }
    if (!above_thresh_counter) {
        *out = -HUGE_VAL;
        return 0;
    }
    gated_loudness /= (double) above_thresh_counter;
    *out = ebur128_energy_to_loudness(gated_loudness);
    return 0;
}