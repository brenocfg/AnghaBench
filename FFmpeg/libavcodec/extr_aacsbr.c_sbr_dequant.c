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
struct TYPE_5__ {int* n; int n_q; TYPE_1__* data; scalar_t__ bs_coupling; } ;
struct TYPE_4__ {int bs_num_env; size_t* bs_freq_res; int** env_facs_q; float** env_facs; int bs_num_noise; int** noise_facs_q; float** noise_facs; scalar_t__ bs_amp_res; } ;
typedef  TYPE_2__ SpectralBandReplication ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
#define  M_SQRT2 128 
 int NOISE_FLOOR_OFFSET ; 
 int TYPE_CPE ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 double const ff_exp2fi (int) ; 

__attribute__((used)) static void sbr_dequant(SpectralBandReplication *sbr, int id_aac)
{
    int k, e;
    int ch;
    static const double exp2_tab[2] = {1, M_SQRT2};
    if (id_aac == TYPE_CPE && sbr->bs_coupling) {
        int pan_offset = sbr->data[0].bs_amp_res ? 12 : 24;
        for (e = 1; e <= sbr->data[0].bs_num_env; e++) {
            for (k = 0; k < sbr->n[sbr->data[0].bs_freq_res[e]]; k++) {
                float temp1, temp2, fac;
                if (sbr->data[0].bs_amp_res) {
                    temp1 = ff_exp2fi(sbr->data[0].env_facs_q[e][k] + 7);
                    temp2 = ff_exp2fi(pan_offset - sbr->data[1].env_facs_q[e][k]);
                }
                else {
                    temp1 = ff_exp2fi((sbr->data[0].env_facs_q[e][k]>>1) + 7) *
                            exp2_tab[sbr->data[0].env_facs_q[e][k] & 1];
                    temp2 = ff_exp2fi((pan_offset - sbr->data[1].env_facs_q[e][k])>>1) *
                            exp2_tab[(pan_offset - sbr->data[1].env_facs_q[e][k]) & 1];
                }
                if (temp1 > 1E20) {
                    av_log(NULL, AV_LOG_ERROR, "envelope scalefactor overflow in dequant\n");
                    temp1 = 1;
                }
                fac   = temp1 / (1.0f + temp2);
                sbr->data[0].env_facs[e][k] = fac;
                sbr->data[1].env_facs[e][k] = fac * temp2;
            }
        }
        for (e = 1; e <= sbr->data[0].bs_num_noise; e++) {
            for (k = 0; k < sbr->n_q; k++) {
                float temp1 = ff_exp2fi(NOISE_FLOOR_OFFSET - sbr->data[0].noise_facs_q[e][k] + 1);
                float temp2 = ff_exp2fi(12 - sbr->data[1].noise_facs_q[e][k]);
                float fac;
                av_assert0(temp1 <= 1E20);
                fac = temp1 / (1.0f + temp2);
                sbr->data[0].noise_facs[e][k] = fac;
                sbr->data[1].noise_facs[e][k] = fac * temp2;
            }
        }
    } else { // SCE or one non-coupled CPE
        for (ch = 0; ch < (id_aac == TYPE_CPE) + 1; ch++) {
            for (e = 1; e <= sbr->data[ch].bs_num_env; e++)
                for (k = 0; k < sbr->n[sbr->data[ch].bs_freq_res[e]]; k++){
                    if (sbr->data[ch].bs_amp_res)
                        sbr->data[ch].env_facs[e][k] = ff_exp2fi(sbr->data[ch].env_facs_q[e][k] + 6);
                    else
                        sbr->data[ch].env_facs[e][k] = ff_exp2fi((sbr->data[ch].env_facs_q[e][k]>>1) + 6)
                                                       * exp2_tab[sbr->data[ch].env_facs_q[e][k] & 1];
                    if (sbr->data[ch].env_facs[e][k] > 1E20) {
                        av_log(NULL, AV_LOG_ERROR, "envelope scalefactor overflow in dequant\n");
                        sbr->data[ch].env_facs[e][k] = 1;
                    }
                }

            for (e = 1; e <= sbr->data[ch].bs_num_noise; e++)
                for (k = 0; k < sbr->n_q; k++)
                    sbr->data[ch].noise_facs[e][k] =
                        ff_exp2fi(NOISE_FLOOR_OFFSET - sbr->data[ch].noise_facs_q[e][k]);
        }
    }
}