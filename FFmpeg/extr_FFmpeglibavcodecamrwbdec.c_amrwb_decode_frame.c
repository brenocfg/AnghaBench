#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_33__ {int (* dot_productf ) (int*,int*,int) ;} ;
struct TYPE_26__ {int /*<<< orphan*/  (* acelp_apply_order_2_transfer_function ) (float*,float*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_31__ {int /*<<< orphan*/  vad; TYPE_5__* subframe; int /*<<< orphan*/  isp_id; } ;
struct TYPE_32__ {size_t fr_cur_mode; double* isf_cur; double** isp; int* fixed_vector; int* pitch_gain; int* fixed_gain; float tilt_coef; int* excitation; float* samples_up; float* samples_hb; int /*<<< orphan*/  isf_past_final; int /*<<< orphan*/  isp_sub4_past; int /*<<< orphan*/  lpf_7_mem; int /*<<< orphan*/  bpf_6_7_mem; int /*<<< orphan*/  hpf_400_mem; TYPE_1__ acelpf_ctx; TYPE_8__ celpm_ctx; int /*<<< orphan*/  hpf_31_mem; int /*<<< orphan*/  demph_mem; int /*<<< orphan*/ * samples_az; int /*<<< orphan*/ * lp_coef; int /*<<< orphan*/  prev_tr_gain; int /*<<< orphan*/  pitch_vector; int /*<<< orphan*/  prediction_error; scalar_t__ first_frame; int /*<<< orphan*/  isf_q_past; TYPE_6__ frame; int /*<<< orphan*/  fr_quality; } ;
struct TYPE_30__ {int /*<<< orphan*/  hb_gain; int /*<<< orphan*/  vq_gain; int /*<<< orphan*/  pul_il; int /*<<< orphan*/  pul_ih; } ;
struct TYPE_29__ {TYPE_7__* priv_data; } ;
struct TYPE_28__ {int nb_samples; scalar_t__* data; } ;
struct TYPE_27__ {int size; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;
typedef  TYPE_5__ AMRWBSubFrame ;
typedef  TYPE_6__ AMRWBFrame ;
typedef  TYPE_7__ AMRWBContext ;

/* Variables and functions */
 int AMRWB_SFR_SIZE ; 
 int AMRWB_SFR_SIZE_16k ; 
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENERGY_MEAN ; 
 int LP_ORDER ; 
 size_t LP_ORDER_16k ; 
 int /*<<< orphan*/  MIN_ISF_SPACING ; 
 scalar_t__ MODE_23k85 ; 
 size_t MODE_6k60 ; 
 size_t MODE_SID ; 
 int /*<<< orphan*/  PREEMPH_FAC ; 
 size_t UPS_FIR_SIZE ; 
 size_t UPS_MEM_SIZE ; 
 int /*<<< orphan*/ * amr_bit_orderings_by_mode ; 
 float* anti_sparseness (TYPE_7__*,int*,float*) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  avpriv_request_sample (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  bpf_6_7_coef ; 
 int* cf_sizes_wb ; 
 int /*<<< orphan*/  de_emphasis (float*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decode_fixed_vector (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  decode_gains (int /*<<< orphan*/ ,size_t,float*,int*) ; 
 int /*<<< orphan*/  decode_isf_indices_36b (int /*<<< orphan*/ ,double*) ; 
 int /*<<< orphan*/  decode_isf_indices_46b (int /*<<< orphan*/ ,double*) ; 
 int decode_mime_header (TYPE_7__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  decode_pitch_vector (TYPE_7__*,TYPE_5__ const*,int) ; 
 int /*<<< orphan*/  energy_pred_fac ; 
 int /*<<< orphan*/  ff_acelp_lsf2lspd (double*,double*,int) ; 
 int /*<<< orphan*/  ff_amr_bit_reorder (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int ff_amr_set_fixed_gain (float,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_amrwb_lsp2lpc (double*,int /*<<< orphan*/ ,int) ; 
 int ff_get_buffer (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_set_min_dist_lsf (double*,int /*<<< orphan*/ ,int) ; 
 float find_hb_gain (TYPE_7__*,float*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_fir_filter (float*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  hb_synthesis (TYPE_7__*,int,float*,float*,double*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpf_31_gain ; 
 int /*<<< orphan*/  hpf_31_poles ; 
 int /*<<< orphan*/  hpf_400_gain ; 
 int /*<<< orphan*/  hpf_400_poles ; 
 int /*<<< orphan*/  hpf_zeros ; 
 int /*<<< orphan*/  interpolate_isp (double**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isf_add_mean_and_past (double*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpf_7_coef ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,double*,int) ; 
 float noise_enhancer (int,int /*<<< orphan*/ *,float,float) ; 
 int /*<<< orphan*/  pitch_enhancer (float*,float) ; 
 int /*<<< orphan*/  pitch_sharpening (TYPE_7__*,int*) ; 
 int /*<<< orphan*/  scaled_hb_excitation (TYPE_7__*,float*,float*,float) ; 
 float stability_factor (double*,int /*<<< orphan*/ ) ; 
 int stub1 (int*,int*,int) ; 
 int /*<<< orphan*/  stub2 (float*,float*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (float*,float*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  synthesis (TYPE_7__*,int /*<<< orphan*/ ,float*,float,float*,int /*<<< orphan*/ *) ; 
 int truncf (int) ; 
 int /*<<< orphan*/  update_sub_state (TYPE_7__*) ; 
 int /*<<< orphan*/  upsample_5_4 (float*,float*,int,TYPE_8__*) ; 
 float voice_factor (int /*<<< orphan*/ ,int,int*,int,TYPE_8__*) ; 

__attribute__((used)) static int amrwb_decode_frame(AVCodecContext *avctx, void *data,
                              int *got_frame_ptr, AVPacket *avpkt)
{
    AMRWBContext *ctx  = avctx->priv_data;
    AVFrame *frame     = data;
    AMRWBFrame   *cf   = &ctx->frame;
    const uint8_t *buf = avpkt->data;
    int buf_size       = avpkt->size;
    int expected_fr_size, header_size;
    float *buf_out;
    float spare_vector[AMRWB_SFR_SIZE];      // extra stack space to hold result from anti-sparseness processing
    float fixed_gain_factor;                 // fixed gain correction factor (gamma)
    float *synth_fixed_vector;               // pointer to the fixed vector that synthesis should use
    float synth_fixed_gain;                  // the fixed gain that synthesis should use
    float voice_fac, stab_fac;               // parameters used for gain smoothing
    float synth_exc[AMRWB_SFR_SIZE];         // post-processed excitation for synthesis
    float hb_exc[AMRWB_SFR_SIZE_16k];        // excitation for the high frequency band
    float hb_samples[AMRWB_SFR_SIZE_16k];    // filtered high-band samples from synthesis
    float hb_gain;
    int sub, i, ret;

    /* get output buffer */
    frame->nb_samples = 4 * AMRWB_SFR_SIZE_16k;
    if ((ret = ff_get_buffer(avctx, frame, 0)) < 0)
        return ret;
    buf_out = (float *)frame->data[0];

    header_size      = decode_mime_header(ctx, buf);
    if (ctx->fr_cur_mode > MODE_SID) {
        av_log(avctx, AV_LOG_ERROR,
               "Invalid mode %d\n", ctx->fr_cur_mode);
        return AVERROR_INVALIDDATA;
    }
    expected_fr_size = ((cf_sizes_wb[ctx->fr_cur_mode] + 7) >> 3) + 1;

    if (buf_size < expected_fr_size) {
        av_log(avctx, AV_LOG_ERROR,
            "Frame too small (%d bytes). Truncated file?\n", buf_size);
        *got_frame_ptr = 0;
        return AVERROR_INVALIDDATA;
    }

    if (!ctx->fr_quality || ctx->fr_cur_mode > MODE_SID)
        av_log(avctx, AV_LOG_ERROR, "Encountered a bad or corrupted frame\n");

    if (ctx->fr_cur_mode == MODE_SID) { /* Comfort noise frame */
        avpriv_request_sample(avctx, "SID mode");
        return AVERROR_PATCHWELCOME;
    }

    ff_amr_bit_reorder((uint16_t *) &ctx->frame, sizeof(AMRWBFrame),
        buf + header_size, amr_bit_orderings_by_mode[ctx->fr_cur_mode]);

    /* Decode the quantized ISF vector */
    if (ctx->fr_cur_mode == MODE_6k60) {
        decode_isf_indices_36b(cf->isp_id, ctx->isf_cur);
    } else {
        decode_isf_indices_46b(cf->isp_id, ctx->isf_cur);
    }

    isf_add_mean_and_past(ctx->isf_cur, ctx->isf_q_past);
    ff_set_min_dist_lsf(ctx->isf_cur, MIN_ISF_SPACING, LP_ORDER - 1);

    stab_fac = stability_factor(ctx->isf_cur, ctx->isf_past_final);

    ctx->isf_cur[LP_ORDER - 1] *= 2.0;
    ff_acelp_lsf2lspd(ctx->isp[3], ctx->isf_cur, LP_ORDER);

    /* Generate a ISP vector for each subframe */
    if (ctx->first_frame) {
        ctx->first_frame = 0;
        memcpy(ctx->isp_sub4_past, ctx->isp[3], LP_ORDER * sizeof(double));
    }
    interpolate_isp(ctx->isp, ctx->isp_sub4_past);

    for (sub = 0; sub < 4; sub++)
        ff_amrwb_lsp2lpc(ctx->isp[sub], ctx->lp_coef[sub], LP_ORDER);

    for (sub = 0; sub < 4; sub++) {
        const AMRWBSubFrame *cur_subframe = &cf->subframe[sub];
        float *sub_buf = buf_out + sub * AMRWB_SFR_SIZE_16k;

        /* Decode adaptive codebook (pitch vector) */
        decode_pitch_vector(ctx, cur_subframe, sub);
        /* Decode innovative codebook (fixed vector) */
        decode_fixed_vector(ctx->fixed_vector, cur_subframe->pul_ih,
                            cur_subframe->pul_il, ctx->fr_cur_mode);

        pitch_sharpening(ctx, ctx->fixed_vector);

        decode_gains(cur_subframe->vq_gain, ctx->fr_cur_mode,
                     &fixed_gain_factor, &ctx->pitch_gain[0]);

        ctx->fixed_gain[0] =
            ff_amr_set_fixed_gain(fixed_gain_factor,
                                  ctx->celpm_ctx.dot_productf(ctx->fixed_vector,
                                                               ctx->fixed_vector,
                                                               AMRWB_SFR_SIZE) /
                                  AMRWB_SFR_SIZE,
                       ctx->prediction_error,
                       ENERGY_MEAN, energy_pred_fac);

        /* Calculate voice factor and store tilt for next subframe */
        voice_fac      = voice_factor(ctx->pitch_vector, ctx->pitch_gain[0],
                                      ctx->fixed_vector, ctx->fixed_gain[0],
                                      &ctx->celpm_ctx);
        ctx->tilt_coef = voice_fac * 0.25 + 0.25;

        /* Construct current excitation */
        for (i = 0; i < AMRWB_SFR_SIZE; i++) {
            ctx->excitation[i] *= ctx->pitch_gain[0];
            ctx->excitation[i] += ctx->fixed_gain[0] * ctx->fixed_vector[i];
            ctx->excitation[i] = truncf(ctx->excitation[i]);
        }

        /* Post-processing of excitation elements */
        synth_fixed_gain = noise_enhancer(ctx->fixed_gain[0], &ctx->prev_tr_gain,
                                          voice_fac, stab_fac);

        synth_fixed_vector = anti_sparseness(ctx, ctx->fixed_vector,
                                             spare_vector);

        pitch_enhancer(synth_fixed_vector, voice_fac);

        synthesis(ctx, ctx->lp_coef[sub], synth_exc, synth_fixed_gain,
                  synth_fixed_vector, &ctx->samples_az[LP_ORDER]);

        /* Synthesis speech post-processing */
        de_emphasis(&ctx->samples_up[UPS_MEM_SIZE],
                    &ctx->samples_az[LP_ORDER], PREEMPH_FAC, ctx->demph_mem);

        ctx->acelpf_ctx.acelp_apply_order_2_transfer_function(&ctx->samples_up[UPS_MEM_SIZE],
            &ctx->samples_up[UPS_MEM_SIZE], hpf_zeros, hpf_31_poles,
            hpf_31_gain, ctx->hpf_31_mem, AMRWB_SFR_SIZE);

        upsample_5_4(sub_buf, &ctx->samples_up[UPS_FIR_SIZE],
                     AMRWB_SFR_SIZE_16k, &ctx->celpm_ctx);

        /* High frequency band (6.4 - 7.0 kHz) generation part */
        ctx->acelpf_ctx.acelp_apply_order_2_transfer_function(hb_samples,
            &ctx->samples_up[UPS_MEM_SIZE], hpf_zeros, hpf_400_poles,
            hpf_400_gain, ctx->hpf_400_mem, AMRWB_SFR_SIZE);

        hb_gain = find_hb_gain(ctx, hb_samples,
                               cur_subframe->hb_gain, cf->vad);

        scaled_hb_excitation(ctx, hb_exc, synth_exc, hb_gain);

        hb_synthesis(ctx, sub, &ctx->samples_hb[LP_ORDER_16k],
                     hb_exc, ctx->isf_cur, ctx->isf_past_final);

        /* High-band post-processing filters */
        hb_fir_filter(hb_samples, bpf_6_7_coef, ctx->bpf_6_7_mem,
                      &ctx->samples_hb[LP_ORDER_16k]);

        if (ctx->fr_cur_mode == MODE_23k85)
            hb_fir_filter(hb_samples, lpf_7_coef, ctx->lpf_7_mem,
                          hb_samples);

        /* Add the low and high frequency bands */
        for (i = 0; i < AMRWB_SFR_SIZE_16k; i++)
            sub_buf[i] = (sub_buf[i] + hb_samples[i]) * (1.0f / (1 << 15));

        /* Update buffers and history */
        update_sub_state(ctx);
    }

    /* update state for next frame */
    memcpy(ctx->isp_sub4_past, ctx->isp[3], LP_ORDER * sizeof(ctx->isp[3][0]));
    memcpy(ctx->isf_past_final, ctx->isf_cur, LP_ORDER * sizeof(float));

    *got_frame_ptr = 1;

    return expected_fr_size;
}