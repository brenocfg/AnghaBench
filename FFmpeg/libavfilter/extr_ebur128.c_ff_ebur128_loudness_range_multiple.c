#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int mode; TYPE_1__* d; } ;
struct TYPE_4__ {unsigned long* short_term_block_energy_histogram; } ;
typedef  TYPE_2__ FFEBUR128State ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int FF_EBUR128_MODE_LRA ; 
 double MINUS_20DB ; 
 double ebur128_energy_to_loudness (double) ; 
 size_t find_histogram_index (double) ; 
 double* histogram_energies ; 
 double* histogram_energy_boundaries ; 

int ff_ebur128_loudness_range_multiple(FFEBUR128State ** sts, size_t size,
                                       double *out)
{
    size_t i, j;
    size_t stl_size;
    double stl_power, stl_integrated;
    /* High and low percentile energy */
    double h_en, l_en;
    unsigned long hist[1000] = { 0 };
    size_t percentile_low, percentile_high;
    size_t index;

    for (i = 0; i < size; ++i) {
        if (sts[i]) {
            if ((sts[i]->mode & FF_EBUR128_MODE_LRA) !=
                FF_EBUR128_MODE_LRA) {
                return AVERROR(EINVAL);
            }
        }
    }

    stl_size = 0;
    stl_power = 0.0;
    for (i = 0; i < size; ++i) {
        if (!sts[i])
            continue;
        for (j = 0; j < 1000; ++j) {
            hist[j] += sts[i]->d->short_term_block_energy_histogram[j];
            stl_size += sts[i]->d->short_term_block_energy_histogram[j];
            stl_power += sts[i]->d->short_term_block_energy_histogram[j]
                * histogram_energies[j];
        }
    }
    if (!stl_size) {
        *out = 0.0;
        return 0;
    }

    stl_power /= stl_size;
    stl_integrated = MINUS_20DB * stl_power;

    if (stl_integrated < histogram_energy_boundaries[0]) {
        index = 0;
    } else {
        index = find_histogram_index(stl_integrated);
        if (stl_integrated > histogram_energies[index]) {
            ++index;
        }
    }
    stl_size = 0;
    for (j = index; j < 1000; ++j) {
        stl_size += hist[j];
    }
    if (!stl_size) {
        *out = 0.0;
        return 0;
    }

    percentile_low = (size_t) ((stl_size - 1) * 0.1 + 0.5);
    percentile_high = (size_t) ((stl_size - 1) * 0.95 + 0.5);

    stl_size = 0;
    j = index;
    while (stl_size <= percentile_low) {
        stl_size += hist[j++];
    }
    l_en = histogram_energies[j - 1];
    while (stl_size <= percentile_high) {
        stl_size += hist[j++];
    }
    h_en = histogram_energies[j - 1];
    *out =
        ebur128_energy_to_loudness(h_en) -
        ebur128_energy_to_loudness(l_en);
    return 0;
}