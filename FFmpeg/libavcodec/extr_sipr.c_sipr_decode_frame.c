#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_18__ {TYPE_2__* priv_data; } ;
struct TYPE_17__ {int nb_samples; scalar_t__* data; } ;
struct TYPE_16__ {int size; int /*<<< orphan*/ * data; } ;
struct TYPE_15__ {size_t mode; int /*<<< orphan*/  (* decode_frame ) (TYPE_2__*,int /*<<< orphan*/ *,float*) ;TYPE_5__* avctx; } ;
struct TYPE_14__ {int bits_per_frame; int frames_per_packet; int subframe_count; } ;
typedef  int /*<<< orphan*/  SiprParameters ;
typedef  TYPE_1__ SiprModeParam ;
typedef  TYPE_2__ SiprContext ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int L_SUBFR_16k ; 
 size_t MODE_16k ; 
 int SUBFR_SIZE ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  decode_parameters (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__ const*) ; 
 int ff_get_buffer (TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_get_bits (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 TYPE_1__* modes ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ *,float*) ; 

__attribute__((used)) static int sipr_decode_frame(AVCodecContext *avctx, void *data,
                             int *got_frame_ptr, AVPacket *avpkt)
{
    SiprContext *ctx = avctx->priv_data;
    AVFrame *frame   = data;
    const uint8_t *buf=avpkt->data;
    SiprParameters parm;
    const SiprModeParam *mode_par = &modes[ctx->mode];
    GetBitContext gb;
    float *samples;
    int subframe_size = ctx->mode == MODE_16k ? L_SUBFR_16k : SUBFR_SIZE;
    int i, ret;

    ctx->avctx = avctx;
    if (avpkt->size < (mode_par->bits_per_frame >> 3)) {
        av_log(avctx, AV_LOG_ERROR,
               "Error processing packet: packet size (%d) too small\n",
               avpkt->size);
        return AVERROR_INVALIDDATA;
    }

    /* get output buffer */
    frame->nb_samples = mode_par->frames_per_packet * subframe_size *
                        mode_par->subframe_count;
    if ((ret = ff_get_buffer(avctx, frame, 0)) < 0)
        return ret;
    samples = (float *)frame->data[0];

    init_get_bits(&gb, buf, mode_par->bits_per_frame);

    for (i = 0; i < mode_par->frames_per_packet; i++) {
        decode_parameters(&parm, &gb, mode_par);

        ctx->decode_frame(ctx, &parm, samples);

        samples += subframe_size * mode_par->subframe_count;
    }

    *got_frame_ptr = 1;

    return mode_par->bits_per_frame >> 3;
}