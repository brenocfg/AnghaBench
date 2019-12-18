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
 int log10 (double) ; 

__attribute__((used)) static double calc_stereo_rms(const float *samples, int nb_samples)
{
    int count = nb_samples;
    double sum = 1e-16;

    while (count--) {
        sum += samples[0] * samples[0] + samples[1] * samples[1];
        samples += 2;
    }

    return 10 * log10 (sum / nb_samples) + 90.0 - 3.0;
}