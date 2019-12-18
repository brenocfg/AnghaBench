#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int nsubbands; float*** time_samples; unsigned int* ch_pres; } ;
typedef  TYPE_1__ DCALbrDecoder ;

/* Variables and functions */
 int DCA_LBR_TIME_SAMPLES ; 
 scalar_t__ fabs (float) ; 
 float lbr_rand (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (float*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void random_ts(DCALbrDecoder *s, int ch1, int ch2)
{
    int i, j, k, ch, sb;

    for (ch = ch1; ch <= ch2; ch++) {
        for (sb = 0; sb < s->nsubbands; sb++) {
            float *samples = s->time_samples[ch][sb];

            if (s->ch_pres[ch] & (1U << sb))
                continue;   // Skip allocated subband

            if (sb < 2) {
                // The first two subbands are always zero
                memset(samples, 0, DCA_LBR_TIME_SAMPLES * sizeof(float));
            } else if (sb < 10) {
                for (i = 0; i < DCA_LBR_TIME_SAMPLES; i++)
                    samples[i] = lbr_rand(s, sb);
            } else {
                for (i = 0; i < DCA_LBR_TIME_SAMPLES / 8; i++, samples += 8) {
                    float accum[8] = { 0 };

                    // Modulate by subbands 2-5 in blocks of 8
                    for (k = 2; k < 6; k++) {
                        float *other = &s->time_samples[ch][k][i * 8];
                        for (j = 0; j < 8; j++)
                            accum[j] += fabs(other[j]);
                    }

                    for (j = 0; j < 8; j++)
                        samples[j] = (accum[j] * 0.25f + 0.5f) * lbr_rand(s, sb);
                }
            }
        }
    }
}