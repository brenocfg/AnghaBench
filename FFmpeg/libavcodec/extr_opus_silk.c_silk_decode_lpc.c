#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  nlsf ;
typedef  int /*<<< orphan*/  lpc ;
typedef  size_t int8_t ;
typedef  int int16_t ;
struct TYPE_6__ {size_t wb; int subframes; int nlsf_interp_factor; } ;
struct TYPE_5__ {int* nlsf; float* lpc; scalar_t__ coded; } ;
typedef  TYPE_1__ SilkFrame ;
typedef  TYPE_2__ SilkContext ;
typedef  int /*<<< orphan*/  OpusRangeCoder ;

/* Variables and functions */
 int av_clip_uintp2 (int,int) ; 
 size_t ff_opus_rc_dec_cdf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int** ff_silk_lsf_codebook_nbmb ; 
 int** ff_silk_lsf_codebook_wb ; 
 int /*<<< orphan*/  ff_silk_lsf_min_spacing_nbmb ; 
 int /*<<< orphan*/  ff_silk_lsf_min_spacing_wb ; 
 int** ff_silk_lsf_pred_weights_nbmb ; 
 int** ff_silk_lsf_pred_weights_wb ; 
 int** ff_silk_lsf_s2_model_sel_nbmb ; 
 int** ff_silk_lsf_s2_model_sel_wb ; 
 size_t** ff_silk_lsf_weight_sel_nbmb ; 
 size_t** ff_silk_lsf_weight_sel_wb ; 
 int /*<<< orphan*/  ff_silk_model_lsf_interpolation_offset ; 
 int /*<<< orphan*/ ** ff_silk_model_lsf_s1 ; 
 int /*<<< orphan*/ * ff_silk_model_lsf_s2 ; 
 int /*<<< orphan*/  ff_silk_model_lsf_s2_ext ; 
 int /*<<< orphan*/  memcpy (float*,...) ; 
 int opus_ilog (int) ; 
 int /*<<< orphan*/  silk_lsf2lpc (int*,float*,int) ; 
 int /*<<< orphan*/  silk_stabilize_lsf (int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void silk_decode_lpc(SilkContext *s, SilkFrame *frame,
                                   OpusRangeCoder *rc,
                                   float lpc_leadin[16], float lpc[16],
                                   int *lpc_order, int *has_lpc_leadin, int voiced)
{
    int i;
    int order;                   // order of the LP polynomial; 10 for NB/MB and 16 for WB
    int8_t  lsf_i1, lsf_i2[16];  // stage-1 and stage-2 codebook indices
    int16_t lsf_res[16];         // residual as a Q10 value
    int16_t nlsf[16];            // Q15

    *lpc_order = order = s->wb ? 16 : 10;

    /* obtain LSF stage-1 and stage-2 indices */
    lsf_i1 = ff_opus_rc_dec_cdf(rc, ff_silk_model_lsf_s1[s->wb][voiced]);
    for (i = 0; i < order; i++) {
        int index = s->wb ? ff_silk_lsf_s2_model_sel_wb  [lsf_i1][i] :
                            ff_silk_lsf_s2_model_sel_nbmb[lsf_i1][i];
        lsf_i2[i] = ff_opus_rc_dec_cdf(rc, ff_silk_model_lsf_s2[index]) - 4;
        if (lsf_i2[i] == -4)
            lsf_i2[i] -= ff_opus_rc_dec_cdf(rc, ff_silk_model_lsf_s2_ext);
        else if (lsf_i2[i] == 4)
            lsf_i2[i] += ff_opus_rc_dec_cdf(rc, ff_silk_model_lsf_s2_ext);
    }

    /* reverse the backwards-prediction step */
    for (i = order - 1; i >= 0; i--) {
        int qstep = s->wb ? 9830 : 11796;

        lsf_res[i] = lsf_i2[i] * 1024;
        if (lsf_i2[i] < 0)      lsf_res[i] += 102;
        else if (lsf_i2[i] > 0) lsf_res[i] -= 102;
        lsf_res[i] = (lsf_res[i] * qstep) >> 16;

        if (i + 1 < order) {
            int weight = s->wb ? ff_silk_lsf_pred_weights_wb  [ff_silk_lsf_weight_sel_wb  [lsf_i1][i]][i] :
                                 ff_silk_lsf_pred_weights_nbmb[ff_silk_lsf_weight_sel_nbmb[lsf_i1][i]][i];
            lsf_res[i] += (lsf_res[i+1] * weight) >> 8;
        }
    }

    /* reconstruct the NLSF coefficients from the supplied indices */
    for (i = 0; i < order; i++) {
        const uint8_t * codebook = s->wb ? ff_silk_lsf_codebook_wb  [lsf_i1] :
                                           ff_silk_lsf_codebook_nbmb[lsf_i1];
        int cur, prev, next, weight_sq, weight, ipart, fpart, y, value;

        /* find the weight of the residual */
        /* TODO: precompute */
        cur = codebook[i];
        prev = i ? codebook[i - 1] : 0;
        next = i + 1 < order ? codebook[i + 1] : 256;
        weight_sq = (1024 / (cur - prev) + 1024 / (next - cur)) << 16;

        /* approximate square-root with mandated fixed-point arithmetic */
        ipart = opus_ilog(weight_sq);
        fpart = (weight_sq >> (ipart-8)) & 127;
        y = ((ipart & 1) ? 32768 : 46214) >> ((32 - ipart)>>1);
        weight = y + ((213 * fpart * y) >> 16);

        value = cur * 128 + (lsf_res[i] * 16384) / weight;
        nlsf[i] = av_clip_uintp2(value, 15);
    }

    /* stabilize the NLSF coefficients */
    silk_stabilize_lsf(nlsf, order, s->wb ? ff_silk_lsf_min_spacing_wb :
                                            ff_silk_lsf_min_spacing_nbmb);

    /* produce an interpolation for the first 2 subframes, */
    /* and then convert both sets of NLSFs to LPC coefficients */
    *has_lpc_leadin = 0;
    if (s->subframes == 4) {
        int offset = ff_opus_rc_dec_cdf(rc, ff_silk_model_lsf_interpolation_offset);
        if (offset != 4 && frame->coded) {
            *has_lpc_leadin = 1;
            if (offset != 0) {
                int16_t nlsf_leadin[16];
                for (i = 0; i < order; i++)
                    nlsf_leadin[i] = frame->nlsf[i] +
                        ((nlsf[i] - frame->nlsf[i]) * offset >> 2);
                silk_lsf2lpc(nlsf_leadin, lpc_leadin, order);
            } else  /* avoid re-computation for a (roughly) 1-in-4 occurrence */
                memcpy(lpc_leadin, frame->lpc, 16 * sizeof(float));
        } else
            offset = 4;
        s->nlsf_interp_factor = offset;

        silk_lsf2lpc(nlsf, lpc, order);
    } else {
        s->nlsf_interp_factor = 4;
        silk_lsf2lpc(nlsf, lpc, order);
    }

    memcpy(frame->nlsf, nlsf, order * sizeof(nlsf[0]));
    memcpy(frame->lpc,  lpc,  order * sizeof(lpc[0]));
}