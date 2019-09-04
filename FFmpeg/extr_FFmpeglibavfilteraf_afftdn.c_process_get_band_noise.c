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
struct TYPE_6__ {double* matrix_b; double* vector_b; double sample_rate; double* band_centre; int /*<<< orphan*/  matrix_a; } ;
struct TYPE_5__ {int* band_noise; } ;
typedef  TYPE_1__ DeNoiseChannel ;
typedef  TYPE_2__ AudioFFTDeNoiseContext ;

/* Variables and functions */
 double log (double) ; 
 int lrint (double) ; 
 int /*<<< orphan*/  solve (int /*<<< orphan*/ ,double*,int) ; 

__attribute__((used)) static int process_get_band_noise(AudioFFTDeNoiseContext *s,
                                  DeNoiseChannel *dnch,
                                  int band)
{
    double product, sum, f;
    int i = 0;

    if (band < 15)
        return dnch->band_noise[band];

    for (int j = 0; j < 5; j++) {
        sum = 0.0;
        for (int k = 0; k < 15; k++)
            sum += s->matrix_b[i++] * dnch->band_noise[k];
        s->vector_b[j] = sum;
    }

    solve(s->matrix_a, s->vector_b, 5);
    f = (0.5 * s->sample_rate) / s->band_centre[14];
    f = 15.0 + log(f / 1.5) / log(1.5);
    sum = 0.0;
    product = 1.0;
    for (int j = 0; j < 5; j++) {
        sum += product * s->vector_b[j];
        product *= f;
    }

    return lrint(sum);
}