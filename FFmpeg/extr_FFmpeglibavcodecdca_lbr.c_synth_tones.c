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
struct TYPE_5__ {int*** tonal_bounds; TYPE_1__* tones; } ;
struct TYPE_4__ {int* amp; int* phs; size_t f_delt; int x_freq; scalar_t__ ph_rot; } ;
typedef  TYPE_1__ DCALbrTone ;
typedef  TYPE_2__ DCALbrDecoder ;

/* Variables and functions */
 int DCA_LBR_TONES ; 
 float* cos_tab ; 
 float** ff_dca_corr_cf ; 
 float* ff_dca_quant_amp ; 
 float* ff_dca_synth_env ; 

__attribute__((used)) static void synth_tones(DCALbrDecoder *s, int ch, float *values,
                        int group, int group_sf, int synth_idx)
{
    int i, start, count;

    if (synth_idx < 0)
        return;

    start =  s->tonal_bounds[group][group_sf][0];
    count = (s->tonal_bounds[group][group_sf][1] - start) & (DCA_LBR_TONES - 1);

    for (i = 0; i < count; i++) {
        DCALbrTone *t = &s->tones[(start + i) & (DCA_LBR_TONES - 1)];

        if (t->amp[ch]) {
            float amp = ff_dca_synth_env[synth_idx] * ff_dca_quant_amp[t->amp[ch]];
            float c = amp * cos_tab[(t->phs[ch]     ) & 255];
            float s = amp * cos_tab[(t->phs[ch] + 64) & 255];
            const float *cf = ff_dca_corr_cf[t->f_delt];
            int x_freq = t->x_freq;

            switch (x_freq) {
            case 0:
                goto p0;
            case 1:
                values[3] += cf[0] * -s;
                values[2] += cf[1] *  c;
                values[1] += cf[2] *  s;
                values[0] += cf[3] * -c;
                goto p1;
            case 2:
                values[2] += cf[0] * -s;
                values[1] += cf[1] *  c;
                values[0] += cf[2] *  s;
                goto p2;
            case 3:
                values[1] += cf[0] * -s;
                values[0] += cf[1] *  c;
                goto p3;
            case 4:
                values[0] += cf[0] * -s;
                goto p4;
            }

            values[x_freq - 5] += cf[ 0] * -s;
        p4: values[x_freq - 4] += cf[ 1] *  c;
        p3: values[x_freq - 3] += cf[ 2] *  s;
        p2: values[x_freq - 2] += cf[ 3] * -c;
        p1: values[x_freq - 1] += cf[ 4] * -s;
        p0: values[x_freq    ] += cf[ 5] *  c;
            values[x_freq + 1] += cf[ 6] *  s;
            values[x_freq + 2] += cf[ 7] * -c;
            values[x_freq + 3] += cf[ 8] * -s;
            values[x_freq + 4] += cf[ 9] *  c;
            values[x_freq + 5] += cf[10] *  s;
        }

        t->phs[ch] += t->ph_rot;
    }
}