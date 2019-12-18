#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct AACISError {int pass; int phase; float error; float dist1; float dist2; float ener01; int /*<<< orphan*/  member_0; } ;
struct TYPE_12__ {TYPE_1__* ch; } ;
struct TYPE_17__ {float* scoefs; int cur_channel; float lambda; int /*<<< orphan*/  (* abs_pow34 ) (float*,float*,int) ;TYPE_2__ psy; } ;
struct TYPE_16__ {TYPE_4__* ch; } ;
struct TYPE_15__ {float threshold; } ;
struct TYPE_13__ {int* group_len; int* swb_sizes; } ;
struct TYPE_14__ {float* pcoeffs; float* coeffs; int* sf_idx; int* band_type; TYPE_3__ ics; } ;
struct TYPE_11__ {TYPE_5__* psy_bands; } ;
typedef  TYPE_4__ SingleChannelElement ;
typedef  TYPE_5__ FFPsyBand ;
typedef  TYPE_6__ ChannelElement ;
typedef  TYPE_7__ AACEncContext ;

/* Variables and functions */
 int FFMAX (int,int) ; 
 float FFMIN (float,float) ; 
 int /*<<< orphan*/  INFINITY ; 
 float find_max_val (int,int,float*) ; 
 int find_min_book (float,int) ; 
 int pos_pow34 (float) ; 
 scalar_t__ quantize_band_cost (TYPE_7__*,float*,float*,int,int,int,float,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 float sqrt (float) ; 
 int /*<<< orphan*/  stub1 (float*,float*,int) ; 
 int /*<<< orphan*/  stub2 (float*,float*,int) ; 
 int /*<<< orphan*/  stub3 (float*,float*,int) ; 

struct AACISError ff_aac_is_encoding_err(AACEncContext *s, ChannelElement *cpe,
                                         int start, int w, int g, float ener0,
                                         float ener1, float ener01,
                                         int use_pcoeffs, int phase)
{
    int i, w2;
    SingleChannelElement *sce0 = &cpe->ch[0];
    SingleChannelElement *sce1 = &cpe->ch[1];
    float *L = use_pcoeffs ? sce0->pcoeffs : sce0->coeffs;
    float *R = use_pcoeffs ? sce1->pcoeffs : sce1->coeffs;
    float *L34 = &s->scoefs[256*0], *R34 = &s->scoefs[256*1];
    float *IS  = &s->scoefs[256*2], *I34 = &s->scoefs[256*3];
    float dist1 = 0.0f, dist2 = 0.0f;
    struct AACISError is_error = {0};

    if (ener01 <= 0 || ener0 <= 0) {
        is_error.pass = 0;
        return is_error;
    }

    for (w2 = 0; w2 < sce0->ics.group_len[w]; w2++) {
        FFPsyBand *band0 = &s->psy.ch[s->cur_channel+0].psy_bands[(w+w2)*16+g];
        FFPsyBand *band1 = &s->psy.ch[s->cur_channel+1].psy_bands[(w+w2)*16+g];
        int is_band_type, is_sf_idx = FFMAX(1, sce0->sf_idx[w*16+g]-4);
        float e01_34 = phase*pos_pow34(ener1/ener0);
        float maxval, dist_spec_err = 0.0f;
        float minthr = FFMIN(band0->threshold, band1->threshold);
        for (i = 0; i < sce0->ics.swb_sizes[g]; i++)
            IS[i] = (L[start+(w+w2)*128+i] + phase*R[start+(w+w2)*128+i])*sqrt(ener0/ener01);
        s->abs_pow34(L34, &L[start+(w+w2)*128], sce0->ics.swb_sizes[g]);
        s->abs_pow34(R34, &R[start+(w+w2)*128], sce0->ics.swb_sizes[g]);
        s->abs_pow34(I34, IS,                   sce0->ics.swb_sizes[g]);
        maxval = find_max_val(1, sce0->ics.swb_sizes[g], I34);
        is_band_type = find_min_book(maxval, is_sf_idx);
        dist1 += quantize_band_cost(s, &L[start + (w+w2)*128], L34,
                                    sce0->ics.swb_sizes[g],
                                    sce0->sf_idx[w*16+g],
                                    sce0->band_type[w*16+g],
                                    s->lambda / band0->threshold, INFINITY, NULL, NULL, 0);
        dist1 += quantize_band_cost(s, &R[start + (w+w2)*128], R34,
                                    sce1->ics.swb_sizes[g],
                                    sce1->sf_idx[w*16+g],
                                    sce1->band_type[w*16+g],
                                    s->lambda / band1->threshold, INFINITY, NULL, NULL, 0);
        dist2 += quantize_band_cost(s, IS, I34, sce0->ics.swb_sizes[g],
                                    is_sf_idx, is_band_type,
                                    s->lambda / minthr, INFINITY, NULL, NULL, 0);
        for (i = 0; i < sce0->ics.swb_sizes[g]; i++) {
            dist_spec_err += (L34[i] - I34[i])*(L34[i] - I34[i]);
            dist_spec_err += (R34[i] - I34[i]*e01_34)*(R34[i] - I34[i]*e01_34);
        }
        dist_spec_err *= s->lambda / minthr;
        dist2 += dist_spec_err;
    }

    is_error.pass = dist2 <= dist1;
    is_error.phase = phase;
    is_error.error = dist2 - dist1;
    is_error.dist1 = dist1;
    is_error.dist2 = dist2;
    is_error.ener01 = ener01;

    return is_error;
}