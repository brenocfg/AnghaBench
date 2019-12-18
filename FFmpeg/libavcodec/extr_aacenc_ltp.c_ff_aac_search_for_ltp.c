#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int* used; int present; scalar_t__ lag; } ;
struct TYPE_12__ {TYPE_1__* ch; } ;
struct TYPE_16__ {float* scoefs; float lambda; size_t cur_channel; int /*<<< orphan*/  (* abs_pow34 ) (float*,float*,int) ;TYPE_2__ psy; } ;
struct TYPE_15__ {int threshold; } ;
struct TYPE_13__ {scalar_t__* window_sequence; int num_windows; int* group_len; int num_swb; int* swb_sizes; int predictor_present; TYPE_8__ ltp; int /*<<< orphan*/  max_sfb; } ;
struct TYPE_14__ {float* coeffs; float* lcoeffs; TYPE_3__ ics; int /*<<< orphan*/ * band_type; int /*<<< orphan*/ * sf_idx; TYPE_8__* ltp_state; } ;
struct TYPE_11__ {TYPE_5__* psy_bands; } ;
typedef  TYPE_4__ SingleChannelElement ;
typedef  int /*<<< orphan*/  LongTermPrediction ;
typedef  TYPE_5__ FFPsyBand ;
typedef  TYPE_6__ AACEncContext ;

/* Variables and functions */
 scalar_t__ EIGHT_SHORT_SEQUENCE ; 
 int FFMIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INFINITY ; 
 int /*<<< orphan*/  MAX_LTP_LONG_SFB ; 
 int /*<<< orphan*/  memset (TYPE_8__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ quantize_band_cost (TYPE_6__*,float*,float*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (float*,float*,int) ; 
 int /*<<< orphan*/  stub2 (float*,float*,int) ; 

void ff_aac_search_for_ltp(AACEncContext *s, SingleChannelElement *sce,
                           int common_window)
{
    int w, g, w2, i, start = 0, count = 0;
    int saved_bits = -(15 + FFMIN(sce->ics.max_sfb, MAX_LTP_LONG_SFB));
    float *C34 = &s->scoefs[128*0], *PCD = &s->scoefs[128*1];
    float *PCD34 = &s->scoefs[128*2];
    const int max_ltp = FFMIN(sce->ics.max_sfb, MAX_LTP_LONG_SFB);

    if (sce->ics.window_sequence[0] == EIGHT_SHORT_SEQUENCE) {
        if (sce->ics.ltp.lag) {
            memset(&sce->ltp_state[0], 0, 3072*sizeof(sce->ltp_state[0]));
            memset(&sce->ics.ltp, 0, sizeof(LongTermPrediction));
        }
        return;
    }

    if (!sce->ics.ltp.lag || s->lambda > 120.0f)
        return;

    for (w = 0; w < sce->ics.num_windows; w += sce->ics.group_len[w]) {
        start = 0;
        for (g = 0;  g < sce->ics.num_swb; g++) {
            int bits1 = 0, bits2 = 0;
            float dist1 = 0.0f, dist2 = 0.0f;
            if (w*16+g > max_ltp) {
                start += sce->ics.swb_sizes[g];
                continue;
            }
            for (w2 = 0; w2 < sce->ics.group_len[w]; w2++) {
                int bits_tmp1, bits_tmp2;
                FFPsyBand *band = &s->psy.ch[s->cur_channel].psy_bands[(w+w2)*16+g];
                for (i = 0; i < sce->ics.swb_sizes[g]; i++)
                    PCD[i] = sce->coeffs[start+(w+w2)*128+i] - sce->lcoeffs[start+(w+w2)*128+i];
                s->abs_pow34(C34,  &sce->coeffs[start+(w+w2)*128],  sce->ics.swb_sizes[g]);
                s->abs_pow34(PCD34, PCD, sce->ics.swb_sizes[g]);
                dist1 += quantize_band_cost(s, &sce->coeffs[start+(w+w2)*128], C34, sce->ics.swb_sizes[g],
                                            sce->sf_idx[(w+w2)*16+g], sce->band_type[(w+w2)*16+g],
                                            s->lambda/band->threshold, INFINITY, &bits_tmp1, NULL, 0);
                dist2 += quantize_band_cost(s, PCD, PCD34, sce->ics.swb_sizes[g],
                                            sce->sf_idx[(w+w2)*16+g],
                                            sce->band_type[(w+w2)*16+g],
                                            s->lambda/band->threshold, INFINITY, &bits_tmp2, NULL, 0);
                bits1 += bits_tmp1;
                bits2 += bits_tmp2;
            }
            if (dist2 < dist1 && bits2 < bits1) {
                for (w2 = 0; w2 < sce->ics.group_len[w]; w2++)
                    for (i = 0; i < sce->ics.swb_sizes[g]; i++)
                        sce->coeffs[start+(w+w2)*128+i] -= sce->lcoeffs[start+(w+w2)*128+i];
                sce->ics.ltp.used[w*16+g] = 1;
                saved_bits += bits1 - bits2;
                count++;
            }
            start += sce->ics.swb_sizes[g];
        }
    }

    sce->ics.ltp.present = !!count && (saved_bits >= 0);
    sce->ics.predictor_present = !!sce->ics.ltp.present;

    /* Reset any marked sfbs */
    if (!sce->ics.ltp.present && !!count) {
        for (w = 0; w < sce->ics.num_windows; w += sce->ics.group_len[w]) {
            start = 0;
            for (g = 0;  g < sce->ics.num_swb; g++) {
                if (sce->ics.ltp.used[w*16+g]) {
                    for (w2 = 0; w2 < sce->ics.group_len[w]; w2++) {
                        for (i = 0; i < sce->ics.swb_sizes[g]; i++) {
                            sce->coeffs[start+(w+w2)*128+i] += sce->lcoeffs[start+(w+w2)*128+i];
                        }
                    }
                }
                start += sce->ics.swb_sizes[g];
            }
        }
    }
}