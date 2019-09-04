#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  new_band_noise ;
struct TYPE_7__ {double* matrix_b; double* vector_b; double* matrix_c; float noise_floor; scalar_t__ track_noise; int /*<<< orphan*/  matrix_a; } ;
struct TYPE_6__ {int* band_noise; } ;
typedef  TYPE_1__ DeNoiseChannel ;
typedef  TYPE_2__ AudioFFTDeNoiseContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int av_clip (int,int,int) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,...) ; 
 int lrint (double) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  solve (int /*<<< orphan*/ ,double*,int) ; 

__attribute__((used)) static void set_noise_profile(AudioFFTDeNoiseContext *s,
                              DeNoiseChannel *dnch,
                              double *sample_noise,
                              int new_profile)
{
    int new_band_noise[15];
    double temp[15];
    double sum = 0.0, d1;
    float new_noise_floor;
    int i, n;

    for (int m = 0; m < 15; m++)
        temp[m] = sample_noise[m];

    if (new_profile) {
        i = 0;
        for (int m = 0; m < 5; m++) {
            sum = 0.0;
            for (n = 0; n < 15; n++)
                sum += s->matrix_b[i++] * temp[n];
            s->vector_b[m] = sum;
        }
        solve(s->matrix_a, s->vector_b, 5);
        i = 0;
        for (int m = 0; m < 15; m++) {
            sum = 0.0;
            for (n = 0; n < 5; n++)
                sum += s->matrix_c[i++] * s->vector_b[n];
            temp[m] = sum;
        }
    }

    sum = 0.0;
    for (int m = 0; m < 15; m++)
        sum += temp[m];

    d1 = (int)(sum / 15.0 - 0.5);
    if (!new_profile)
        i = lrint(temp[7] - d1);

    for (d1 -= dnch->band_noise[7] - i; d1 > -20.0; d1 -= 1.0)
        ;

    for (int m = 0; m < 15; m++)
        temp[m] -= d1;

    new_noise_floor = d1 + 2.5;

    if (new_profile) {
        av_log(s, AV_LOG_INFO, "bn=");
        for (int m = 0; m < 15; m++) {
            new_band_noise[m] = lrint(temp[m]);
            new_band_noise[m] = av_clip(new_band_noise[m], -24, 24);
            av_log(s, AV_LOG_INFO, "%d ", new_band_noise[m]);
        }
        av_log(s, AV_LOG_INFO, "\n");
        memcpy(dnch->band_noise, new_band_noise, sizeof(new_band_noise));
    }

    if (s->track_noise)
        s->noise_floor = new_noise_floor;
}