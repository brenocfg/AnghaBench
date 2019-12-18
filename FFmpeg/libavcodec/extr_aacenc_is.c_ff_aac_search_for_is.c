#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct AACISError {scalar_t__ error; float ener01; scalar_t__ phase; scalar_t__ pass; } ;
struct TYPE_17__ {float lambda; } ;
struct TYPE_16__ {float sample_rate; } ;
struct TYPE_15__ {int* is_mask; int* ms_mask; int is_mode; TYPE_2__* ch; int /*<<< orphan*/  common_window; } ;
struct TYPE_13__ {float num_windows; int* group_len; int num_swb; int* swb_sizes; } ;
struct TYPE_14__ {scalar_t__* band_type; float* coeffs; float* is_ener; int* sf_idx; TYPE_1__ ics; int /*<<< orphan*/ * zeroes; } ;
typedef  TYPE_2__ SingleChannelElement ;
typedef  TYPE_3__ ChannelElement ;
typedef  TYPE_4__ AVCodecContext ;
typedef  TYPE_5__ AACEncContext ;

/* Variables and functions */
 void* INTENSITY_BT ; 
 void* INTENSITY_BT2 ; 
 float INT_STEREO_LOW_LIMIT ; 
 scalar_t__ NOISE_BT ; 
 scalar_t__ RESERVED_BT ; 
 struct AACISError ff_aac_is_encoding_err (TYPE_5__*,TYPE_3__*,int,int,int,float,float,float,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ff_init_nextband_map (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ ff_sfdelta_can_remove_band (TYPE_2__*,int /*<<< orphan*/ *,int,int) ; 
 float sqrt (float) ; 

void ff_aac_search_for_is(AACEncContext *s, AVCodecContext *avctx, ChannelElement *cpe)
{
    SingleChannelElement *sce0 = &cpe->ch[0];
    SingleChannelElement *sce1 = &cpe->ch[1];
    int start = 0, count = 0, w, w2, g, i, prev_sf1 = -1, prev_bt = -1, prev_is = 0;
    const float freq_mult = avctx->sample_rate/(1024.0f/sce0->ics.num_windows)/2.0f;
    uint8_t nextband1[128];

    if (!cpe->common_window)
        return;

    /** Scout out next nonzero bands */
    ff_init_nextband_map(sce1, nextband1);

    for (w = 0; w < sce0->ics.num_windows; w += sce0->ics.group_len[w]) {
        start = 0;
        for (g = 0;  g < sce0->ics.num_swb; g++) {
            if (start*freq_mult > INT_STEREO_LOW_LIMIT*(s->lambda/170.0f) &&
                cpe->ch[0].band_type[w*16+g] != NOISE_BT && !cpe->ch[0].zeroes[w*16+g] &&
                cpe->ch[1].band_type[w*16+g] != NOISE_BT && !cpe->ch[1].zeroes[w*16+g] &&
                ff_sfdelta_can_remove_band(sce1, nextband1, prev_sf1, w*16+g)) {
                float ener0 = 0.0f, ener1 = 0.0f, ener01 = 0.0f, ener01p = 0.0f;
                struct AACISError ph_err1, ph_err2, *best;
                for (w2 = 0; w2 < sce0->ics.group_len[w]; w2++) {
                    for (i = 0; i < sce0->ics.swb_sizes[g]; i++) {
                        float coef0 = sce0->coeffs[start+(w+w2)*128+i];
                        float coef1 = sce1->coeffs[start+(w+w2)*128+i];
                        ener0  += coef0*coef0;
                        ener1  += coef1*coef1;
                        ener01 += (coef0 + coef1)*(coef0 + coef1);
                        ener01p += (coef0 - coef1)*(coef0 - coef1);
                    }
                }
                ph_err1 = ff_aac_is_encoding_err(s, cpe, start, w, g,
                                                 ener0, ener1, ener01p, 0, -1);
                ph_err2 = ff_aac_is_encoding_err(s, cpe, start, w, g,
                                                 ener0, ener1, ener01, 0, +1);
                best = (ph_err1.pass && ph_err1.error < ph_err2.error) ? &ph_err1 : &ph_err2;
                if (best->pass) {
                    cpe->is_mask[w*16+g] = 1;
                    cpe->ms_mask[w*16+g] = 0;
                    cpe->ch[0].is_ener[w*16+g] = sqrt(ener0 / best->ener01);
                    cpe->ch[1].is_ener[w*16+g] = ener0/ener1;
                    cpe->ch[1].band_type[w*16+g] = (best->phase > 0) ? INTENSITY_BT : INTENSITY_BT2;
                    if (prev_is && prev_bt != cpe->ch[1].band_type[w*16+g]) {
                        /** Flip M/S mask and pick the other CB, since it encodes more efficiently */
                        cpe->ms_mask[w*16+g] = 1;
                        cpe->ch[1].band_type[w*16+g] = (best->phase > 0) ? INTENSITY_BT2 : INTENSITY_BT;
                    }
                    prev_bt = cpe->ch[1].band_type[w*16+g];
                    count++;
                }
            }
            if (!sce1->zeroes[w*16+g] && sce1->band_type[w*16+g] < RESERVED_BT)
                prev_sf1 = sce1->sf_idx[w*16+g];
            prev_is = cpe->is_mask[w*16+g];
            start += sce0->ics.swb_sizes[g];
        }
    }
    cpe->is_mode = !!count;
}