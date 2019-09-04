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
struct TYPE_6__ {double sample_floor; double auto_floor; } ;
struct TYPE_5__ {double* noisy_data; double* sfm_results; double sfm_threshold; } ;
typedef  TYPE_1__ DeNoiseChannel ;
typedef  TYPE_2__ AudioFFTDeNoiseContext ;

/* Variables and functions */
 double log (double) ; 

__attribute__((used)) static void calculate_sfm(AudioFFTDeNoiseContext *s,
                          DeNoiseChannel *dnch,
                          int start, int end)
{
    double d1 = 0.0, d2 = 1.0;
    int i = 0, j = 0;

    for (int k = start; k < end; k++) {
        if (dnch->noisy_data[k] > s->sample_floor) {
            j++;
            d1 += dnch->noisy_data[k];
            d2 *= dnch->noisy_data[k];
            if (d2 > 1.0E100) {
                d2 *= 1.0E-100;
                i++;
            } else if (d2 < 1.0E-100) {
                d2 *= 1.0E100;
                i--;
            }
        }
    }
    if (j > 1) {
        d1 /= j;
        dnch->sfm_results[0] = d1;
        d2 = log(d2) + 230.2585 * i;
        d2 /= j;
        d1 = log(d1);
        dnch->sfm_results[1] = d1;
        dnch->sfm_results[2] = d1 - d2;
    } else {
        dnch->sfm_results[0] = s->auto_floor;
        dnch->sfm_results[1] = dnch->sfm_threshold;
        dnch->sfm_results[2] = dnch->sfm_threshold;
    }
}