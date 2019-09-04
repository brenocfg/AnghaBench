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
typedef  unsigned int uint8_t ;
struct TYPE_4__ {int nsubbands; float*** time_samples; unsigned int*** high_res_scf; unsigned int*** grid_2_scf; unsigned int* ch_pres; int** sec_ch_sbms; int** sec_ch_lrms; int min_mono_subband; int part_stereo_pres; } ;
typedef  TYPE_1__ DCALbrDecoder ;

/* Variables and functions */
 unsigned int AMP_MAX ; 
 int DCA_LBR_TIME_SAMPLES ; 
 float* ff_dca_quant_amp ; 
 size_t* ff_dca_scf_to_grid_2 ; 
 int /*<<< orphan*/  synth_lpc (TYPE_1__*,int,int,int) ; 

__attribute__((used)) static void filter_ts(DCALbrDecoder *s, int ch1, int ch2)
{
    int i, j, sb, ch;

    for (sb = 0; sb < s->nsubbands; sb++) {
        // Scale factors
        for (ch = ch1; ch <= ch2; ch++) {
            float *samples = s->time_samples[ch][sb];
            uint8_t *hr_scf = s->high_res_scf[ch][sb];
            if (sb < 4) {
                for (i = 0; i < DCA_LBR_TIME_SAMPLES / 16; i++, samples += 16) {
                    unsigned int scf = hr_scf[i];
                    if (scf > AMP_MAX)
                        scf = AMP_MAX;
                    for (j = 0; j < 16; j++)
                        samples[j] *= ff_dca_quant_amp[scf];
                }
            } else {
                uint8_t *g2_scf = s->grid_2_scf[ch][ff_dca_scf_to_grid_2[sb]];
                for (i = 0; i < DCA_LBR_TIME_SAMPLES / 2; i++, samples += 2) {
                    unsigned int scf = hr_scf[i / 8] - g2_scf[i];
                    if (scf > AMP_MAX)
                        scf = AMP_MAX;
                    samples[0] *= ff_dca_quant_amp[scf];
                    samples[1] *= ff_dca_quant_amp[scf];
                }
            }
        }

        // Mid-side stereo
        if (ch1 != ch2) {
            float *samples_l = s->time_samples[ch1][sb];
            float *samples_r = s->time_samples[ch2][sb];
            int ch2_pres = s->ch_pres[ch2] & (1U << sb);

            for (i = 0; i < DCA_LBR_TIME_SAMPLES / 16; i++) {
                int sbms = (s->sec_ch_sbms[ch1 / 2][sb] >> i) & 1;
                int lrms = (s->sec_ch_lrms[ch1 / 2][sb] >> i) & 1;

                if (sb >= s->min_mono_subband) {
                    if (lrms && ch2_pres) {
                        if (sbms) {
                            for (j = 0; j < 16; j++) {
                                float tmp = samples_l[j];
                                samples_l[j] =  samples_r[j];
                                samples_r[j] = -tmp;
                            }
                        } else {
                            for (j = 0; j < 16; j++) {
                                float tmp = samples_l[j];
                                samples_l[j] =  samples_r[j];
                                samples_r[j] =  tmp;
                            }
                        }
                    } else if (!ch2_pres) {
                        if (sbms && (s->part_stereo_pres & (1 << ch1))) {
                            for (j = 0; j < 16; j++)
                                samples_r[j] = -samples_l[j];
                        } else {
                            for (j = 0; j < 16; j++)
                                samples_r[j] =  samples_l[j];
                        }
                    }
                } else if (sbms && ch2_pres) {
                    for (j = 0; j < 16; j++) {
                        float tmp = samples_l[j];
                        samples_l[j] = (tmp + samples_r[j]) * 0.5f;
                        samples_r[j] = (tmp - samples_r[j]) * 0.5f;
                    }
                }

                samples_l += 16;
                samples_r += 16;
            }
        }

        // Inverse prediction
        if (sb < 3)
            synth_lpc(s, ch1, ch2, sb);
    }
}