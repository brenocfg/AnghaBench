#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_26__ {scalar_t__ mb_decision; int /*<<< orphan*/  (* execute2 ) (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ;TYPE_2__* priv_data; } ;
struct TYPE_25__ {scalar_t__* linesize; int /*<<< orphan*/ * data; } ;
struct TYPE_24__ {int /*<<< orphan*/  flags; int /*<<< orphan*/ * data; } ;
struct TYPE_22__ {int mb_height; } ;
struct TYPE_23__ {int cur_field; int* slice_size; int data_offset; int coding_unit_size; int qscale; scalar_t__ interlaced; TYPE_1__ m; int /*<<< orphan*/ * msip; int /*<<< orphan*/ * src; int /*<<< orphan*/  frame_size; } ;
typedef  TYPE_2__ DNXHDEncContext ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  AV_WB32 (int /*<<< orphan*/ *,int) ; 
 scalar_t__ FF_MB_DECISION_RD ; 
 int FF_QP2LAMBDA ; 
 int /*<<< orphan*/  av_assert1 (int) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 int dnxhd_encode_fast (TYPE_5__*,TYPE_2__*) ; 
 int dnxhd_encode_rdo (TYPE_5__*,TYPE_2__*) ; 
 int /*<<< orphan*/  dnxhd_encode_thread ; 
 int /*<<< orphan*/  dnxhd_load_picture (TYPE_2__*,TYPE_4__ const*) ; 
 int /*<<< orphan*/  dnxhd_setup_threads_slices (TYPE_2__*) ; 
 int /*<<< orphan*/  dnxhd_write_header (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int ff_alloc_packet2 (TYPE_5__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_side_data_set_encoder_stats (TYPE_3__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int dnxhd_encode_picture(AVCodecContext *avctx, AVPacket *pkt,
                                const AVFrame *frame, int *got_packet)
{
    DNXHDEncContext *ctx = avctx->priv_data;
    int first_field = 1;
    int offset, i, ret;
    uint8_t *buf;

    if ((ret = ff_alloc_packet2(avctx, pkt, ctx->frame_size, 0)) < 0)
        return ret;
    buf = pkt->data;

    dnxhd_load_picture(ctx, frame);

encode_coding_unit:
    for (i = 0; i < 3; i++) {
        ctx->src[i] = frame->data[i];
        if (ctx->interlaced && ctx->cur_field)
            ctx->src[i] += frame->linesize[i];
    }

    dnxhd_write_header(avctx, buf);

    if (avctx->mb_decision == FF_MB_DECISION_RD)
        ret = dnxhd_encode_rdo(avctx, ctx);
    else
        ret = dnxhd_encode_fast(avctx, ctx);
    if (ret < 0) {
        av_log(avctx, AV_LOG_ERROR,
               "picture could not fit ratecontrol constraints, increase qmax\n");
        return ret;
    }

    dnxhd_setup_threads_slices(ctx);

    offset = 0;
    for (i = 0; i < ctx->m.mb_height; i++) {
        AV_WB32(ctx->msip + i * 4, offset);
        offset += ctx->slice_size[i];
        av_assert1(!(ctx->slice_size[i] & 3));
    }

    avctx->execute2(avctx, dnxhd_encode_thread, buf, NULL, ctx->m.mb_height);

    av_assert1(ctx->data_offset + offset + 4 <= ctx->coding_unit_size);
    memset(buf + ctx->data_offset + offset, 0,
           ctx->coding_unit_size - 4 - offset - ctx->data_offset);

    AV_WB32(buf + ctx->coding_unit_size - 4, 0x600DC0DE); // EOF

    if (ctx->interlaced && first_field) {
        first_field     = 0;
        ctx->cur_field ^= 1;
        buf            += ctx->coding_unit_size;
        goto encode_coding_unit;
    }

#if FF_API_CODED_FRAME
FF_DISABLE_DEPRECATION_WARNINGS
    avctx->coded_frame->quality = ctx->qscale * FF_QP2LAMBDA;
FF_ENABLE_DEPRECATION_WARNINGS
#endif

    ff_side_data_set_encoder_stats(pkt, ctx->qscale * FF_QP2LAMBDA, NULL, 0, AV_PICTURE_TYPE_I);

    pkt->flags |= AV_PKT_FLAG_KEY;
    *got_packet = 1;
    return 0;
}