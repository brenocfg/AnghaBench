#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct sbc_frame {scalar_t__ mode; int subbands; int channels; int blocks; int bitpool; int codesize; int /*<<< orphan*/  scale_factor; int /*<<< orphan*/  sb_sample_f; } ;
struct TYPE_11__ {int (* sbc_calc_scalefactors_j ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ;int /*<<< orphan*/  (* sbc_calc_scalefactors ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ;int /*<<< orphan*/  X; int /*<<< orphan*/  position; int /*<<< orphan*/  (* sbc_enc_process_input_4s ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ;int /*<<< orphan*/  (* sbc_enc_process_input_8s ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ;} ;
struct TYPE_10__ {TYPE_1__* priv_data; } ;
struct TYPE_9__ {int nb_samples; int /*<<< orphan*/ * data; } ;
struct TYPE_8__ {int /*<<< orphan*/  msbc; TYPE_6__ dsp; struct sbc_frame frame; } ;
typedef  TYPE_1__ SBCEncContext ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ JOINT_STEREO ; 
 scalar_t__ SBC_MODE_DUAL_CHANNEL ; 
 scalar_t__ SBC_MODE_JOINT_STEREO ; 
 int /*<<< orphan*/  emms_c () ; 
 int ff_alloc_packet2 (TYPE_3__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbc_analyze_audio (TYPE_6__*,struct sbc_frame*) ; 
 int /*<<< orphan*/  sbc_pack_frame (int /*<<< orphan*/ *,struct sbc_frame*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int sbc_encode_frame(AVCodecContext *avctx, AVPacket *avpkt,
                            const AVFrame *av_frame, int *got_packet_ptr)
{
    SBCEncContext *sbc = avctx->priv_data;
    struct sbc_frame *frame = &sbc->frame;
    uint8_t joint = frame->mode == SBC_MODE_JOINT_STEREO;
    uint8_t dual  = frame->mode == SBC_MODE_DUAL_CHANNEL;
    int ret, j = 0;

    int frame_length = 4 + (4 * frame->subbands * frame->channels) / 8
                     + ((frame->blocks * frame->bitpool * (1 + dual)
                     + joint * frame->subbands) + 7) / 8;

    /* input must be large enough to encode a complete frame */
    if (av_frame->nb_samples * frame->channels * 2 < frame->codesize)
        return 0;

    if ((ret = ff_alloc_packet2(avctx, avpkt, frame_length, 0)) < 0)
        return ret;

    /* Select the needed input data processing function and call it */
    if (frame->subbands == 8)
        sbc->dsp.position = sbc->dsp.sbc_enc_process_input_8s(
                sbc->dsp.position, av_frame->data[0], sbc->dsp.X,
                frame->subbands * frame->blocks, frame->channels);
    else
        sbc->dsp.position = sbc->dsp.sbc_enc_process_input_4s(
                sbc->dsp.position, av_frame->data[0], sbc->dsp.X,
                frame->subbands * frame->blocks, frame->channels);

    sbc_analyze_audio(&sbc->dsp, &sbc->frame);

    if (frame->mode == JOINT_STEREO)
        j = sbc->dsp.sbc_calc_scalefactors_j(frame->sb_sample_f,
                                             frame->scale_factor,
                                             frame->blocks,
                                             frame->subbands);
    else
        sbc->dsp.sbc_calc_scalefactors(frame->sb_sample_f,
                                       frame->scale_factor,
                                       frame->blocks,
                                       frame->channels,
                                       frame->subbands);
    emms_c();
    sbc_pack_frame(avpkt, frame, j, sbc->msbc);

    *got_packet_ptr = 1;
    return 0;
}