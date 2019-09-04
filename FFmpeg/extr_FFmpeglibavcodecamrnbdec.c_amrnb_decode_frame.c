#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_44__   TYPE_9__ ;
typedef  struct TYPE_43__   TYPE_8__ ;
typedef  struct TYPE_42__   TYPE_7__ ;
typedef  struct TYPE_41__   TYPE_6__ ;
typedef  struct TYPE_40__   TYPE_5__ ;
typedef  struct TYPE_39__   TYPE_4__ ;
typedef  struct TYPE_38__   TYPE_3__ ;
typedef  struct TYPE_37__   TYPE_2__ ;
typedef  struct TYPE_36__   TYPE_1__ ;
typedef  struct TYPE_35__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_44__ {scalar_t__ pitch_lag; int /*<<< orphan*/  member_0; } ;
struct TYPE_43__ {int /*<<< orphan*/  pulses; } ;
struct TYPE_42__ {TYPE_10__* priv_data; } ;
struct TYPE_41__ {scalar_t__* data; int /*<<< orphan*/  nb_samples; } ;
struct TYPE_40__ {int size; int /*<<< orphan*/ * data; } ;
struct TYPE_39__ {int /*<<< orphan*/  (* weighted_vector_sumf ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double,double,size_t) ;} ;
struct TYPE_38__ {int /*<<< orphan*/  (* acelp_apply_order_2_transfer_function ) (float*,float*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_37__ {int (* dot_productf ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ;} ;
struct TYPE_36__ {TYPE_8__* subframe; } ;
struct TYPE_35__ {scalar_t__ cur_frame_mode; double* fixed_gain; int /*<<< orphan*/ * lsf_q; int /*<<< orphan*/  lsf_avg; TYPE_4__ acelpv_ctx; int /*<<< orphan*/  high_pass_mem; TYPE_3__ acelpf_ctx; int /*<<< orphan*/ * fixed_vector; int /*<<< orphan*/ * lpc; int /*<<< orphan*/ * samples_in; int /*<<< orphan*/ * excitation; int /*<<< orphan*/ * pitch_gain; int /*<<< orphan*/  prediction_error; TYPE_2__ celpm_ctx; TYPE_1__ frame; int /*<<< orphan*/ * lsp; } ;
typedef  TYPE_5__ AVPacket ;
typedef  TYPE_6__ AVFrame ;
typedef  TYPE_7__ AVCodecContext ;
typedef  TYPE_8__ AMRNBSubframe ;
typedef  TYPE_9__ AMRFixed ;
typedef  TYPE_10__ AMRContext ;

/* Variables and functions */
 int /*<<< orphan*/  AMR_BLOCK_SIZE ; 
 int AMR_SAMPLE_SCALE ; 
 int AMR_SUBFRAME_SIZE ; 
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 size_t LP_FILTER_ORDER ; 
 scalar_t__ MODE_12k2 ; 
 scalar_t__ MODE_DTX ; 
 scalar_t__ NO_DATA ; 
 float* anti_sparseness (TYPE_10__*,TYPE_9__*,int /*<<< orphan*/ *,float,float*) ; 
 int /*<<< orphan*/  av_log (TYPE_7__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avpriv_report_missing_feature (TYPE_7__*,char*) ; 
 int /*<<< orphan*/  decode_fixed_sparse (TYPE_9__*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  decode_gains (TYPE_10__*,TYPE_8__ const*,scalar_t__,int,float*) ; 
 int /*<<< orphan*/  decode_pitch_vector (TYPE_10__*,TYPE_8__ const*,int) ; 
 int /*<<< orphan*/ * energy_mean ; 
 int /*<<< orphan*/  energy_pred_fac ; 
 int /*<<< orphan*/  ff_acelp_lspd2lpc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 double ff_amr_set_fixed_gain (float,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_clear_fixed_vector (int /*<<< orphan*/ *,TYPE_9__*,int) ; 
 int ff_get_buffer (TYPE_7__*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_set_fixed_vector (int /*<<< orphan*/ *,TYPE_9__*,double,int) ; 
 float fixed_gain_smooth (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int* frame_sizes_nb ; 
 int highpass_gain ; 
 int /*<<< orphan*/  highpass_poles ; 
 int /*<<< orphan*/  highpass_zeros ; 
 int /*<<< orphan*/  lsf2lsp_3 (TYPE_10__*) ; 
 int /*<<< orphan*/  lsf2lsp_5 (TYPE_10__*) ; 
 int /*<<< orphan*/  pitch_sharpening (TYPE_10__*,int,scalar_t__,TYPE_9__*) ; 
 int /*<<< orphan*/  postfilter (TYPE_10__*,int /*<<< orphan*/ ,float*) ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub2 (float*,float*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double,double,size_t) ; 
 scalar_t__ synthesis (TYPE_10__*,int /*<<< orphan*/ ,float,float const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  truncf (int /*<<< orphan*/ ) ; 
 scalar_t__ unpack_bitstream (TYPE_10__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  update_state (TYPE_10__*) ; 

__attribute__((used)) static int amrnb_decode_frame(AVCodecContext *avctx, void *data,
                              int *got_frame_ptr, AVPacket *avpkt)
{

    AMRContext *p = avctx->priv_data;        // pointer to private data
    AVFrame *frame     = data;
    const uint8_t *buf = avpkt->data;
    int buf_size       = avpkt->size;
    float *buf_out;                          // pointer to the output data buffer
    int i, subframe, ret;
    float fixed_gain_factor;
    AMRFixed fixed_sparse = {0};             // fixed vector up to anti-sparseness processing
    float spare_vector[AMR_SUBFRAME_SIZE];   // extra stack space to hold result from anti-sparseness processing
    float synth_fixed_gain;                  // the fixed gain that synthesis should use
    const float *synth_fixed_vector;         // pointer to the fixed vector that synthesis should use

    /* get output buffer */
    frame->nb_samples = AMR_BLOCK_SIZE;
    if ((ret = ff_get_buffer(avctx, frame, 0)) < 0)
        return ret;
    buf_out = (float *)frame->data[0];

    p->cur_frame_mode = unpack_bitstream(p, buf, buf_size);
    if (p->cur_frame_mode == NO_DATA) {
        av_log(avctx, AV_LOG_ERROR, "Corrupt bitstream\n");
        return AVERROR_INVALIDDATA;
    }
    if (p->cur_frame_mode == MODE_DTX) {
        avpriv_report_missing_feature(avctx, "dtx mode");
        av_log(avctx, AV_LOG_INFO, "Note: libopencore_amrnb supports dtx\n");
        return AVERROR_PATCHWELCOME;
    }

    if (p->cur_frame_mode == MODE_12k2) {
        lsf2lsp_5(p);
    } else
        lsf2lsp_3(p);

    for (i = 0; i < 4; i++)
        ff_acelp_lspd2lpc(p->lsp[i], p->lpc[i], 5);

    for (subframe = 0; subframe < 4; subframe++) {
        const AMRNBSubframe *amr_subframe = &p->frame.subframe[subframe];

        decode_pitch_vector(p, amr_subframe, subframe);

        decode_fixed_sparse(&fixed_sparse, amr_subframe->pulses,
                            p->cur_frame_mode, subframe);

        // The fixed gain (section 6.1.3) depends on the fixed vector
        // (section 6.1.2), but the fixed vector calculation uses
        // pitch sharpening based on the on the pitch gain (section 6.1.3).
        // So the correct order is: pitch gain, pitch sharpening, fixed gain.
        decode_gains(p, amr_subframe, p->cur_frame_mode, subframe,
                     &fixed_gain_factor);

        pitch_sharpening(p, subframe, p->cur_frame_mode, &fixed_sparse);

        if (fixed_sparse.pitch_lag == 0) {
            av_log(avctx, AV_LOG_ERROR, "The file is corrupted, pitch_lag = 0 is not allowed\n");
            return AVERROR_INVALIDDATA;
        }
        ff_set_fixed_vector(p->fixed_vector, &fixed_sparse, 1.0,
                            AMR_SUBFRAME_SIZE);

        p->fixed_gain[4] =
            ff_amr_set_fixed_gain(fixed_gain_factor,
                       p->celpm_ctx.dot_productf(p->fixed_vector,
                                                               p->fixed_vector,
                                                               AMR_SUBFRAME_SIZE) /
                                  AMR_SUBFRAME_SIZE,
                       p->prediction_error,
                       energy_mean[p->cur_frame_mode], energy_pred_fac);

        // The excitation feedback is calculated without any processing such
        // as fixed gain smoothing. This isn't mentioned in the specification.
        for (i = 0; i < AMR_SUBFRAME_SIZE; i++)
            p->excitation[i] *= p->pitch_gain[4];
        ff_set_fixed_vector(p->excitation, &fixed_sparse, p->fixed_gain[4],
                            AMR_SUBFRAME_SIZE);

        // In the ref decoder, excitation is stored with no fractional bits.
        // This step prevents buzz in silent periods. The ref encoder can
        // emit long sequences with pitch factor greater than one. This
        // creates unwanted feedback if the excitation vector is nonzero.
        // (e.g. test sequence T19_795.COD in 3GPP TS 26.074)
        for (i = 0; i < AMR_SUBFRAME_SIZE; i++)
            p->excitation[i] = truncf(p->excitation[i]);

        // Smooth fixed gain.
        // The specification is ambiguous, but in the reference source, the
        // smoothed value is NOT fed back into later fixed gain smoothing.
        synth_fixed_gain = fixed_gain_smooth(p, p->lsf_q[subframe],
                                             p->lsf_avg, p->cur_frame_mode);

        synth_fixed_vector = anti_sparseness(p, &fixed_sparse, p->fixed_vector,
                                             synth_fixed_gain, spare_vector);

        if (synthesis(p, p->lpc[subframe], synth_fixed_gain,
                      synth_fixed_vector, &p->samples_in[LP_FILTER_ORDER], 0))
            // overflow detected -> rerun synthesis scaling pitch vector down
            // by a factor of 4, skipping pitch vector contribution emphasis
            // and adaptive gain control
            synthesis(p, p->lpc[subframe], synth_fixed_gain,
                      synth_fixed_vector, &p->samples_in[LP_FILTER_ORDER], 1);

        postfilter(p, p->lpc[subframe], buf_out + subframe * AMR_SUBFRAME_SIZE);

        // update buffers and history
        ff_clear_fixed_vector(p->fixed_vector, &fixed_sparse, AMR_SUBFRAME_SIZE);
        update_state(p);
    }

    p->acelpf_ctx.acelp_apply_order_2_transfer_function(buf_out,
                                             buf_out, highpass_zeros,
                                             highpass_poles,
                                             highpass_gain * AMR_SAMPLE_SCALE,
                                             p->high_pass_mem, AMR_BLOCK_SIZE);

    /* Update averaged lsf vector (used for fixed gain smoothing).
     *
     * Note that lsf_avg should not incorporate the current frame's LSFs
     * for fixed_gain_smooth.
     * The specification has an incorrect formula: the reference decoder uses
     * qbar(n-1) rather than qbar(n) in section 6.1(4) equation 71. */
    p->acelpv_ctx.weighted_vector_sumf(p->lsf_avg, p->lsf_avg, p->lsf_q[3],
                            0.84, 0.16, LP_FILTER_ORDER);

    *got_frame_ptr = 1;

    /* return the amount of bytes consumed if everything was OK */
    return frame_sizes_nb[p->cur_frame_mode] + 1; // +7 for rounding and +8 for TOC
}