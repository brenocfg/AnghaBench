#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_3__ {int min_mono_subband; int nsubbands; size_t*** part_stereo; float*** time_samples; unsigned int* ch_pres; } ;
typedef  TYPE_1__ DCALbrDecoder ;

/* Variables and functions */
 float* ff_dca_st_coeff ; 

__attribute__((used)) static void decode_part_stereo(DCALbrDecoder *s, int ch1, int ch2)
{
    int i, ch, sb, sf;

    for (ch = ch1; ch <= ch2; ch++) {
        for (sb = s->min_mono_subband; sb < s->nsubbands; sb++) {
            uint8_t *pt_st = s->part_stereo[ch][(sb - s->min_mono_subband) / 4];
            float *samples = s->time_samples[ch][sb];

            if (s->ch_pres[ch2] & (1U << sb))
                continue;

            for (sf = 1; sf <= 4; sf++, samples += 32) {
                float prev = ff_dca_st_coeff[pt_st[sf - 1]];
                float next = ff_dca_st_coeff[pt_st[sf    ]];

                for (i = 0; i < 32; i++)
                    samples[i] *= (32 - i) * prev + i * next;
            }
        }
    }
}