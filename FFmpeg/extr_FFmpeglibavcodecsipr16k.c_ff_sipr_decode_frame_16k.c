#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fixed_vector ;
struct TYPE_10__ {void* pitch_lag; int /*<<< orphan*/  pitch_fac; } ;
struct TYPE_9__ {float* synth_buf; float* excitation; float* lsp_history_16k; float* synth; double* energy_history; float* iir_mem; int /*<<< orphan*/  mem_preemph; int /*<<< orphan*/  filt_mem; void* pitch_lag_prev; int /*<<< orphan*/  lsf_history; } ;
struct TYPE_8__ {size_t* gp_index; size_t* gc_index; int /*<<< orphan*/ * fc_indexes; int /*<<< orphan*/ * pitch_delay; int /*<<< orphan*/  ma_pred_switch; int /*<<< orphan*/  vq_indexes; } ;
typedef  TYPE_1__ SiprParameters ;
typedef  TYPE_2__ SiprContext ;
typedef  TYPE_3__ AMRFixed ;

/* Variables and functions */
 void* DIVIDE_BY_3 (int) ; 
 int /*<<< orphan*/  FFMIN (float,double) ; 
 int /*<<< orphan*/  LP_FILTER_ORDER ; 
 int LP_FILTER_ORDER_16k ; 
 int LSFQ_DIFF_MIN ; 
 int L_INTERPOL ; 
 int L_SUBFR_16k ; 
 double M_LN10 ; 
 double M_LN2 ; 
 int PITCH_MAX ; 
 int /*<<< orphan*/  PITCH_MIN ; 
 int SUBFRAME_COUNT_16k ; 
 float acelp_decode_gain_codef (int /*<<< orphan*/ ,float*,double,int /*<<< orphan*/ ,double*,int,int) ; 
 int /*<<< orphan*/  acelp_lp_decodef (float*,float*,double*,float*) ; 
 int dec_delay3_1st (int /*<<< orphan*/ ) ; 
 int dec_delay3_2nd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*) ; 
 int /*<<< orphan*/  ff_acelp_interpolatef (float*,float*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ff_celp_lp_synthesis_filterf (float*,float*,float*,int,int) ; 
 int /*<<< orphan*/  ff_decode_10_pulses_35bits (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ff_fc_4pulses_8bits_tracks_13 ; 
 int /*<<< orphan*/  ff_set_fixed_vector (float*,TYPE_3__*,double,int) ; 
 int /*<<< orphan*/  ff_set_min_dist_lsf (float*,int,int) ; 
 int /*<<< orphan*/  ff_weighted_vector_sumf (float*,float*,float*,float,float,int) ; 
 float* gain_cb_16k ; 
 float* gain_pitch_cb_16k ; 
 double log10f (float) ; 
 int /*<<< orphan*/  lsf2lsp (float*,double*) ; 
 int /*<<< orphan*/  lsf_decode_fp_16k (int /*<<< orphan*/ ,float*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (float*,...) ; 
 int /*<<< orphan*/  memmove (float*,float*,int) ; 
 int /*<<< orphan*/  memset (float*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  postfilter (float*,float*,float*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pred_16k ; 
 int /*<<< orphan*/  sinc_win ; 
 int /*<<< orphan*/  sqrt (int) ; 

void ff_sipr_decode_frame_16k(SiprContext *ctx, SiprParameters *params,
                              float *out_data)
{
    int frame_size = SUBFRAME_COUNT_16k * L_SUBFR_16k;
    float *synth = ctx->synth_buf + LP_FILTER_ORDER_16k;
    float lsf_new[LP_FILTER_ORDER_16k];
    double lsp_new[LP_FILTER_ORDER_16k];
    float Az[2][LP_FILTER_ORDER_16k];
    float fixed_vector[L_SUBFR_16k];
    float pitch_fac, gain_code;

    int i;
    int pitch_delay_3x;

    float *excitation = ctx->excitation + 292;

    lsf_decode_fp_16k(ctx->lsf_history, lsf_new, params->vq_indexes,
                      params->ma_pred_switch);

    ff_set_min_dist_lsf(lsf_new, LSFQ_DIFF_MIN / 2, LP_FILTER_ORDER_16k);

    lsf2lsp(lsf_new, lsp_new);

    acelp_lp_decodef(Az[0], Az[1], lsp_new, ctx->lsp_history_16k);

    memcpy(ctx->lsp_history_16k, lsp_new, LP_FILTER_ORDER_16k * sizeof(double));

    memcpy(synth - LP_FILTER_ORDER_16k, ctx->synth,
           LP_FILTER_ORDER_16k * sizeof(*synth));

    for (i = 0; i < SUBFRAME_COUNT_16k; i++) {
        int i_subfr = i * L_SUBFR_16k;
        AMRFixed f;
        float gain_corr_factor;
        int pitch_delay_int;
        int pitch_delay_frac;

        if (!i) {
            pitch_delay_3x = dec_delay3_1st(params->pitch_delay[i]);
        } else
            pitch_delay_3x = dec_delay3_2nd(params->pitch_delay[i],
                                            PITCH_MIN, PITCH_MAX,
                                            ctx->pitch_lag_prev);

        pitch_fac = gain_pitch_cb_16k[params->gp_index[i]];
        f.pitch_fac = FFMIN(pitch_fac, 1.0);
        f.pitch_lag = DIVIDE_BY_3(pitch_delay_3x+1);
        ctx->pitch_lag_prev = f.pitch_lag;

        pitch_delay_int  = DIVIDE_BY_3(pitch_delay_3x + 2);
        pitch_delay_frac = pitch_delay_3x + 2 - 3*pitch_delay_int;

        ff_acelp_interpolatef(&excitation[i_subfr],
                              &excitation[i_subfr] - pitch_delay_int + 1,
                              sinc_win, 3, pitch_delay_frac + 1,
                              LP_FILTER_ORDER, L_SUBFR_16k);


        memset(fixed_vector, 0, sizeof(fixed_vector));

        ff_decode_10_pulses_35bits(params->fc_indexes[i], &f,
                                   ff_fc_4pulses_8bits_tracks_13, 5, 4);

        ff_set_fixed_vector(fixed_vector, &f, 1.0, L_SUBFR_16k);

        gain_corr_factor = gain_cb_16k[params->gc_index[i]];
        gain_code = gain_corr_factor *
            acelp_decode_gain_codef(sqrt(L_SUBFR_16k), fixed_vector,
                                    19.0 - 15.0/(0.05*M_LN10/M_LN2),
                                    pred_16k, ctx->energy_history,
                                    L_SUBFR_16k, 2);

        ctx->energy_history[1] = ctx->energy_history[0];
        ctx->energy_history[0] = 20.0 * log10f(gain_corr_factor);

        ff_weighted_vector_sumf(&excitation[i_subfr], &excitation[i_subfr],
                                fixed_vector, pitch_fac,
                                gain_code, L_SUBFR_16k);

        ff_celp_lp_synthesis_filterf(synth + i_subfr, Az[i],
                                     &excitation[i_subfr], L_SUBFR_16k,
                                     LP_FILTER_ORDER_16k);

    }
    memcpy(ctx->synth, synth + frame_size - LP_FILTER_ORDER_16k,
           LP_FILTER_ORDER_16k * sizeof(*synth));

    memmove(ctx->excitation, ctx->excitation + 2 * L_SUBFR_16k,
            (L_INTERPOL+PITCH_MAX) * sizeof(float));

    postfilter(out_data, synth, ctx->iir_mem, ctx->filt_mem, ctx->mem_preemph);

    memcpy(ctx->iir_mem, Az[1], LP_FILTER_ORDER_16k * sizeof(float));
}