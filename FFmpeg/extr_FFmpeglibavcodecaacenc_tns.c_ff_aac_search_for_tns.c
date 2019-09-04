#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int present; int* n_filt; int** direction; int** order; int** length; int /*<<< orphan*/ ** coef; int /*<<< orphan*/ ** coef_idx; } ;
typedef  TYPE_4__ TemporalNoiseShaping ;
struct TYPE_12__ {TYPE_2__* ch; } ;
struct TYPE_16__ {size_t samplerate_index; scalar_t__ profile; size_t cur_channel; int /*<<< orphan*/  lpc; TYPE_3__ psy; } ;
struct TYPE_15__ {scalar_t__ energy; } ;
struct TYPE_10__ {scalar_t__* window_sequence; int num_swb; int* swb_offset; int num_windows; int /*<<< orphan*/  max_sfb; int /*<<< orphan*/  tns_max_bands; } ;
struct TYPE_14__ {TYPE_4__ tns; int /*<<< orphan*/ * coeffs; TYPE_1__ ics; } ;
struct TYPE_11__ {TYPE_6__* psy_bands; } ;
typedef  TYPE_5__ SingleChannelElement ;
typedef  TYPE_6__ FFPsyBand ;
typedef  TYPE_7__ AACEncContext ;

/* Variables and functions */
 scalar_t__ EIGHT_SHORT_SEQUENCE ; 
 int FFMIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FF_PROFILE_AAC_LOW ; 
 scalar_t__ LONG_START_SEQUENCE ; 
 scalar_t__ LONG_STOP_SEQUENCE ; 
 int MAX_LPC_ORDER ; 
 double TNS_GAIN_THRESHOLD_HIGH ; 
 double TNS_GAIN_THRESHOLD_LOW ; 
 int TNS_MAX_ORDER ; 
 int TNS_Q_BITS ; 
 int TNS_Q_BITS_IS8 ; 
 int av_clip (int,int /*<<< orphan*/ ,int const) ; 
 double ff_lpc_calc_ref_coefs_f (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int const,int const,double*) ; 
 int /*<<< orphan*/  isfinite (double) ; 
 int /*<<< orphan*/  quantize_coefs (double*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int const) ; 
 int** tns_min_sfb ; 

void ff_aac_search_for_tns(AACEncContext *s, SingleChannelElement *sce)
{
    TemporalNoiseShaping *tns = &sce->tns;
    int w, g, count = 0;
    double gain, coefs[MAX_LPC_ORDER];
    const int mmm = FFMIN(sce->ics.tns_max_bands, sce->ics.max_sfb);
    const int is8 = sce->ics.window_sequence[0] == EIGHT_SHORT_SEQUENCE;
    const int c_bits = is8 ? TNS_Q_BITS_IS8 == 4 : TNS_Q_BITS == 4;
    const int sfb_start = av_clip(tns_min_sfb[is8][s->samplerate_index], 0, mmm);
    const int sfb_end   = av_clip(sce->ics.num_swb, 0, mmm);
    const int order = is8 ? 7 : s->profile == FF_PROFILE_AAC_LOW ? 12 : TNS_MAX_ORDER;
    const int slant = sce->ics.window_sequence[0] == LONG_STOP_SEQUENCE  ? 1 :
                      sce->ics.window_sequence[0] == LONG_START_SEQUENCE ? 0 : 2;
    const int sfb_len = sfb_end - sfb_start;
    const int coef_len = sce->ics.swb_offset[sfb_end] - sce->ics.swb_offset[sfb_start];

    if (coef_len <= 0 || sfb_len <= 0) {
        sce->tns.present = 0;
        return;
    }

    for (w = 0; w < sce->ics.num_windows; w++) {
        float en[2] = {0.0f, 0.0f};
        int oc_start = 0, os_start = 0;
        int coef_start = sce->ics.swb_offset[sfb_start];

        for (g = sfb_start; g < sce->ics.num_swb && g <= sfb_end; g++) {
            FFPsyBand *band = &s->psy.ch[s->cur_channel].psy_bands[w*16+g];
            if (g > sfb_start + (sfb_len/2))
                en[1] += band->energy;
            else
                en[0] += band->energy;
        }

        /* LPC */
        gain = ff_lpc_calc_ref_coefs_f(&s->lpc, &sce->coeffs[w*128 + coef_start],
                                       coef_len, order, coefs);

        if (!order || !isfinite(gain) || gain < TNS_GAIN_THRESHOLD_LOW || gain > TNS_GAIN_THRESHOLD_HIGH)
            continue;

        tns->n_filt[w] = is8 ? 1 : order != TNS_MAX_ORDER ? 2 : 3;
        for (g = 0; g < tns->n_filt[w]; g++) {
            tns->direction[w][g] = slant != 2 ? slant : en[g] < en[!g];
            tns->order[w][g] = g < tns->n_filt[w] ? order/tns->n_filt[w] : order - oc_start;
            tns->length[w][g] = g < tns->n_filt[w] ? sfb_len/tns->n_filt[w] : sfb_len - os_start;
            quantize_coefs(&coefs[oc_start], tns->coef_idx[w][g], tns->coef[w][g],
                            tns->order[w][g], c_bits);
            oc_start += tns->order[w][g];
            os_start += tns->length[w][g];
        }
        count++;
    }
    sce->tns.present = !!count;
}