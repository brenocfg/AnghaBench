#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int int16_t ;
struct TYPE_27__ {int amp_index; } ;
struct TYPE_26__ {int channels; TYPE_2__* priv_data; } ;
struct TYPE_25__ {int nb_samples; int** data; scalar_t__* extended_data; } ;
struct TYPE_24__ {int* data; int size; } ;
struct TYPE_23__ {int* audio; scalar_t__ past_frame_type; scalar_t__ cur_frame_type; int erased_frames; int* prev_lsp; int* excitation; int* prev_excitation; int interp_gain; int sid_gain; int cur_gain; int* sid_lsp; int* synth_mem; int /*<<< orphan*/  lsp_index; TYPE_9__* subframe; int /*<<< orphan*/  cng_random_seed; int /*<<< orphan*/  random_seed; int /*<<< orphan*/  interp_index; int /*<<< orphan*/  cur_rate; int /*<<< orphan*/ * pitch_lag; } ;
struct TYPE_22__ {scalar_t__ postfilter; TYPE_3__* ch; } ;
struct TYPE_21__ {int index; int /*<<< orphan*/  opt_gain; int /*<<< orphan*/  sc_gain; } ;
typedef  TYPE_1__ PPFParam ;
typedef  TYPE_2__ G723_1_Context ;
typedef  TYPE_3__ G723_1_ChannelContext ;
typedef  TYPE_4__ AVPacket ;
typedef  TYPE_5__ AVFrame ;
typedef  TYPE_6__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ ACTIVE_FRAME ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  CNG_RANDOM_SEED ; 
 int FRAME_LEN ; 
 int LPC_ORDER ; 
 int PITCH_MAX ; 
 scalar_t__ SID_FRAME ; 
 int SUBFRAMES ; 
 int SUBFRAME_LEN ; 
 scalar_t__ UNTRANSMITTED_FRAME ; 
 int av_clip_int16 (int) ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  comp_interp_index (TYPE_3__*,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  comp_ppf_coeff (TYPE_3__*,int,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int estimate_sid_gain (TYPE_3__*) ; 
 int /*<<< orphan*/  ff_acelp_weighted_vector_sum (int*,int*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  ff_celp_lp_synthesis_filter (int*,int*,int*,int,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ff_g723_1_gen_acb_excitation (int*,int*,int /*<<< orphan*/ ,TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_g723_1_inverse_quant (int*,int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ff_g723_1_lsp_interpolate (int*,int*,int*) ; 
 int ff_get_buffer (TYPE_6__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int* fixed_cb_gain ; 
 int /*<<< orphan*/  formant_postfilter (TYPE_3__*,int*,int*,int*) ; 
 int* frame_size ; 
 int /*<<< orphan*/  gen_fcb_excitation (int*,TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  generate_noise (TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  residual_interp (int*,int*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int sid_gain_to_lsp_index (int) ; 
 scalar_t__ unpack_bitstream (TYPE_3__*,int const*,int) ; 

__attribute__((used)) static int g723_1_decode_frame(AVCodecContext *avctx, void *data,
                               int *got_frame_ptr, AVPacket *avpkt)
{
    G723_1_Context *s  = avctx->priv_data;
    AVFrame *frame     = data;
    const uint8_t *buf = avpkt->data;
    int buf_size       = avpkt->size;
    int dec_mode       = buf[0] & 3;

    PPFParam ppf[SUBFRAMES];
    int16_t cur_lsp[LPC_ORDER];
    int16_t lpc[SUBFRAMES * LPC_ORDER];
    int16_t acb_vector[SUBFRAME_LEN];
    int16_t *out;
    int bad_frame = 0, i, j, ret;

    if (buf_size < frame_size[dec_mode] * avctx->channels) {
        if (buf_size)
            av_log(avctx, AV_LOG_WARNING,
                   "Expected %d bytes, got %d - skipping packet\n",
                   frame_size[dec_mode], buf_size);
        *got_frame_ptr = 0;
        return buf_size;
    }

    frame->nb_samples = FRAME_LEN;
    if ((ret = ff_get_buffer(avctx, frame, 0)) < 0)
        return ret;

    for (int ch = 0; ch < avctx->channels; ch++) {
        G723_1_ChannelContext *p = &s->ch[ch];
        int16_t *audio = p->audio;

        if (unpack_bitstream(p, buf + ch * (buf_size / avctx->channels),
                             buf_size / avctx->channels) < 0) {
            bad_frame = 1;
            if (p->past_frame_type == ACTIVE_FRAME)
                p->cur_frame_type = ACTIVE_FRAME;
            else
                p->cur_frame_type = UNTRANSMITTED_FRAME;
        }

        out = (int16_t *)frame->extended_data[ch];

        if (p->cur_frame_type == ACTIVE_FRAME) {
            if (!bad_frame)
                p->erased_frames = 0;
            else if (p->erased_frames != 3)
                p->erased_frames++;

            ff_g723_1_inverse_quant(cur_lsp, p->prev_lsp, p->lsp_index, bad_frame);
            ff_g723_1_lsp_interpolate(lpc, cur_lsp, p->prev_lsp);

            /* Save the lsp_vector for the next frame */
            memcpy(p->prev_lsp, cur_lsp, LPC_ORDER * sizeof(*p->prev_lsp));

            /* Generate the excitation for the frame */
            memcpy(p->excitation, p->prev_excitation,
                   PITCH_MAX * sizeof(*p->excitation));
            if (!p->erased_frames) {
                int16_t *vector_ptr = p->excitation + PITCH_MAX;

                /* Update interpolation gain memory */
                p->interp_gain = fixed_cb_gain[(p->subframe[2].amp_index +
                                                p->subframe[3].amp_index) >> 1];
                for (i = 0; i < SUBFRAMES; i++) {
                    gen_fcb_excitation(vector_ptr, &p->subframe[i], p->cur_rate,
                                       p->pitch_lag[i >> 1], i);
                    ff_g723_1_gen_acb_excitation(acb_vector,
                                                 &p->excitation[SUBFRAME_LEN * i],
                                                 p->pitch_lag[i >> 1],
                                                 &p->subframe[i], p->cur_rate);
                    /* Get the total excitation */
                    for (j = 0; j < SUBFRAME_LEN; j++) {
                        int v = av_clip_int16(vector_ptr[j] * 2);
                        vector_ptr[j] = av_clip_int16(v + acb_vector[j]);
                    }
                    vector_ptr += SUBFRAME_LEN;
                }

                vector_ptr = p->excitation + PITCH_MAX;

                p->interp_index = comp_interp_index(p, p->pitch_lag[1],
                                                    &p->sid_gain, &p->cur_gain);

                /* Perform pitch postfiltering */
                if (s->postfilter) {
                    i = PITCH_MAX;
                    for (j = 0; j < SUBFRAMES; i += SUBFRAME_LEN, j++)
                        comp_ppf_coeff(p, i, p->pitch_lag[j >> 1],
                                       ppf + j, p->cur_rate);

                    for (i = 0, j = 0; j < SUBFRAMES; i += SUBFRAME_LEN, j++)
                        ff_acelp_weighted_vector_sum(p->audio + LPC_ORDER + i,
                                                     vector_ptr + i,
                                                     vector_ptr + i + ppf[j].index,
                                                     ppf[j].sc_gain,
                                                     ppf[j].opt_gain,
                                                     1 << 14, 15, SUBFRAME_LEN);
                } else {
                    audio = vector_ptr - LPC_ORDER;
                }

                /* Save the excitation for the next frame */
                memcpy(p->prev_excitation, p->excitation + FRAME_LEN,
                       PITCH_MAX * sizeof(*p->excitation));
            } else {
                p->interp_gain = (p->interp_gain * 3 + 2) >> 2;
                if (p->erased_frames == 3) {
                    /* Mute output */
                    memset(p->excitation, 0,
                           (FRAME_LEN + PITCH_MAX) * sizeof(*p->excitation));
                    memset(p->prev_excitation, 0,
                           PITCH_MAX * sizeof(*p->excitation));
                    memset(frame->data[0], 0,
                           (FRAME_LEN + LPC_ORDER) * sizeof(int16_t));
                } else {
                    int16_t *buf = p->audio + LPC_ORDER;

                    /* Regenerate frame */
                    residual_interp(p->excitation, buf, p->interp_index,
                                    p->interp_gain, &p->random_seed);

                    /* Save the excitation for the next frame */
                    memcpy(p->prev_excitation, buf + (FRAME_LEN - PITCH_MAX),
                           PITCH_MAX * sizeof(*p->excitation));
                }
            }
            p->cng_random_seed = CNG_RANDOM_SEED;
        } else {
            if (p->cur_frame_type == SID_FRAME) {
                p->sid_gain = sid_gain_to_lsp_index(p->subframe[0].amp_index);
                ff_g723_1_inverse_quant(p->sid_lsp, p->prev_lsp, p->lsp_index, 0);
            } else if (p->past_frame_type == ACTIVE_FRAME) {
                p->sid_gain = estimate_sid_gain(p);
            }

            if (p->past_frame_type == ACTIVE_FRAME)
                p->cur_gain = p->sid_gain;
            else
                p->cur_gain = (p->cur_gain * 7 + p->sid_gain) >> 3;
            generate_noise(p);
            ff_g723_1_lsp_interpolate(lpc, p->sid_lsp, p->prev_lsp);
            /* Save the lsp_vector for the next frame */
            memcpy(p->prev_lsp, p->sid_lsp, LPC_ORDER * sizeof(*p->prev_lsp));
        }

        p->past_frame_type = p->cur_frame_type;

        memcpy(p->audio, p->synth_mem, LPC_ORDER * sizeof(*p->audio));
        for (i = LPC_ORDER, j = 0; j < SUBFRAMES; i += SUBFRAME_LEN, j++)
            ff_celp_lp_synthesis_filter(p->audio + i, &lpc[j * LPC_ORDER],
                                        audio + i, SUBFRAME_LEN, LPC_ORDER,
                                        0, 1, 1 << 12);
        memcpy(p->synth_mem, p->audio + FRAME_LEN, LPC_ORDER * sizeof(*p->audio));

        if (s->postfilter) {
            formant_postfilter(p, lpc, p->audio, out);
        } else { // if output is not postfiltered it should be scaled by 2
            for (i = 0; i < FRAME_LEN; i++)
                out[i] = av_clip_int16(2 * p->audio[LPC_ORDER + i]);
        }
    }

    *got_frame_ptr = 1;

    return frame_size[dec_mode] * avctx->channels;
}