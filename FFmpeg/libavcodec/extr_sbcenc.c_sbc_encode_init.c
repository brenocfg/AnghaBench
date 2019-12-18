#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sbc_frame {scalar_t__ mode; int subbands; int blocks; int bitpool; int frequency; int channels; int codesize; int /*<<< orphan*/  crc_ctx; void* allocation; } ;
struct TYPE_10__ {int position; int increment; int /*<<< orphan*/  X; } ;
struct TYPE_9__ {scalar_t__ profile; int channels; int sample_rate; int frame_size; int global_quality; int bit_rate; TYPE_1__* codec; TYPE_2__* priv_data; } ;
struct TYPE_8__ {int msbc; int max_delay; TYPE_5__ dsp; struct sbc_frame frame; } ;
struct TYPE_7__ {scalar_t__* supported_samplerates; } ;
typedef  TYPE_2__ SBCEncContext ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_CRC_8_EBU ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ FF_PROFILE_SBC_MSBC ; 
 int FF_QP2LAMBDA ; 
 int MSBC_BLOCKS ; 
 void* SBC_AM_LOUDNESS ; 
 scalar_t__ SBC_MODE_DUAL_CHANNEL ; 
 scalar_t__ SBC_MODE_JOINT_STEREO ; 
 void* SBC_MODE_MONO ; 
 scalar_t__ SBC_MODE_STEREO ; 
 int SBC_X_BUFFER_SIZE ; 
 int av_clip (int,int,int) ; 
 int /*<<< orphan*/  av_crc_get_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ff_sbcdsp_init (TYPE_5__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sbc_encode_init(AVCodecContext *avctx)
{
    SBCEncContext *sbc = avctx->priv_data;
    struct sbc_frame *frame = &sbc->frame;

    if (avctx->profile == FF_PROFILE_SBC_MSBC)
        sbc->msbc = 1;

    if (sbc->msbc) {
        if (avctx->channels != 1) {
            av_log(avctx, AV_LOG_ERROR, "mSBC require mono channel.\n");
            return AVERROR(EINVAL);
        }

        if (avctx->sample_rate != 16000) {
            av_log(avctx, AV_LOG_ERROR, "mSBC require 16 kHz samplerate.\n");
            return AVERROR(EINVAL);
        }

        frame->mode = SBC_MODE_MONO;
        frame->subbands = 8;
        frame->blocks = MSBC_BLOCKS;
        frame->allocation = SBC_AM_LOUDNESS;
        frame->bitpool = 26;

        avctx->frame_size = 8 * MSBC_BLOCKS;
    } else {
        int d;

        if (avctx->global_quality > 255*FF_QP2LAMBDA) {
            av_log(avctx, AV_LOG_ERROR, "bitpool > 255 is not allowed.\n");
            return AVERROR(EINVAL);
        }

        if (avctx->channels == 1) {
            frame->mode = SBC_MODE_MONO;
            if (sbc->max_delay <= 3000 || avctx->bit_rate > 270000)
                frame->subbands = 4;
            else
                frame->subbands = 8;
        } else {
            if (avctx->bit_rate < 180000 || avctx->bit_rate > 420000)
                frame->mode = SBC_MODE_JOINT_STEREO;
            else
                frame->mode = SBC_MODE_STEREO;
            if (sbc->max_delay <= 4000 || avctx->bit_rate > 420000)
                frame->subbands = 4;
            else
                frame->subbands = 8;
        }
        /* sbc algorithmic delay is ((blocks + 10) * subbands - 2) / sample_rate */
        frame->blocks = av_clip(((sbc->max_delay * avctx->sample_rate + 2)
                               / (1000000 * frame->subbands)) - 10, 4, 16) & ~3;

        frame->allocation = SBC_AM_LOUDNESS;

        d = frame->blocks * ((frame->mode == SBC_MODE_DUAL_CHANNEL) + 1);
        frame->bitpool = (((avctx->bit_rate * frame->subbands * frame->blocks) / avctx->sample_rate)
                          - 4 * frame->subbands * avctx->channels
                          - (frame->mode == SBC_MODE_JOINT_STEREO)*frame->subbands - 32 + d/2) / d;
        if (avctx->global_quality > 0)
            frame->bitpool = avctx->global_quality / FF_QP2LAMBDA;

        avctx->frame_size = 4*((frame->subbands >> 3) + 1) * 4*(frame->blocks >> 2);
    }

    for (int i = 0; avctx->codec->supported_samplerates[i]; i++)
        if (avctx->sample_rate == avctx->codec->supported_samplerates[i])
            frame->frequency = i;

    frame->channels = avctx->channels;
    frame->codesize = frame->subbands * frame->blocks * avctx->channels * 2;
    frame->crc_ctx = av_crc_get_table(AV_CRC_8_EBU);

    memset(&sbc->dsp.X, 0, sizeof(sbc->dsp.X));
    sbc->dsp.position = (SBC_X_BUFFER_SIZE - frame->subbands * 9) & ~7;
    sbc->dsp.increment = sbc->msbc ? 1 : 4;
    ff_sbcdsp_init(&sbc->dsp);

    return 0;
}