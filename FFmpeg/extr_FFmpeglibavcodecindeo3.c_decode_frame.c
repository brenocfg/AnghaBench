#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_16__ {scalar_t__ skip_frame; int height; TYPE_1__* priv_data; } ;
struct TYPE_15__ {int /*<<< orphan*/ * linesize; int /*<<< orphan*/ * data; } ;
struct TYPE_14__ {int size; int /*<<< orphan*/ * data; } ;
struct TYPE_13__ {int frame_flags; int buf_sel; int /*<<< orphan*/ * planes; int /*<<< orphan*/  v_data_size; int /*<<< orphan*/  v_data_ptr; int /*<<< orphan*/  u_data_size; int /*<<< orphan*/  u_data_ptr; int /*<<< orphan*/  y_data_size; int /*<<< orphan*/  y_data_ptr; } ;
typedef  TYPE_1__ Indeo3DecodeContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ AVDISCARD_NONKEY ; 
 scalar_t__ AVDISCARD_NONREF ; 
 int BS_BUFFER ; 
 int BS_KEYFRAME ; 
 int BS_NONREF ; 
 int decode_frame_headers (TYPE_1__*,TYPE_4__*,int /*<<< orphan*/  const*,int) ; 
 int decode_plane (TYPE_1__*,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ff_get_buffer (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_plane (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int decode_frame(AVCodecContext *avctx, void *data, int *got_frame,
                        AVPacket *avpkt)
{
    Indeo3DecodeContext *ctx = avctx->priv_data;
    const uint8_t *buf = avpkt->data;
    int buf_size       = avpkt->size;
    AVFrame *frame     = data;
    int res;

    res = decode_frame_headers(ctx, avctx, buf, buf_size);
    if (res < 0)
        return res;

    /* skip sync(null) frames */
    if (res) {
        // we have processed 16 bytes but no data was decoded
        *got_frame = 0;
        return buf_size;
    }

    /* skip droppable INTER frames if requested */
    if (ctx->frame_flags & BS_NONREF &&
       (avctx->skip_frame >= AVDISCARD_NONREF))
        return 0;

    /* skip INTER frames if requested */
    if (!(ctx->frame_flags & BS_KEYFRAME) && avctx->skip_frame >= AVDISCARD_NONKEY)
        return 0;

    /* use BS_BUFFER flag for buffer switching */
    ctx->buf_sel = (ctx->frame_flags >> BS_BUFFER) & 1;

    if ((res = ff_get_buffer(avctx, frame, 0)) < 0)
        return res;

    /* decode luma plane */
    if ((res = decode_plane(ctx, avctx, ctx->planes, ctx->y_data_ptr, ctx->y_data_size, 40)))
        return res;

    /* decode chroma planes */
    if ((res = decode_plane(ctx, avctx, &ctx->planes[1], ctx->u_data_ptr, ctx->u_data_size, 10)))
        return res;

    if ((res = decode_plane(ctx, avctx, &ctx->planes[2], ctx->v_data_ptr, ctx->v_data_size, 10)))
        return res;

    output_plane(&ctx->planes[0], ctx->buf_sel,
                 frame->data[0], frame->linesize[0],
                 avctx->height);
    output_plane(&ctx->planes[1], ctx->buf_sel,
                 frame->data[1], frame->linesize[1],
                 (avctx->height + 3) >> 2);
    output_plane(&ctx->planes[2], ctx->buf_sel,
                 frame->data[2], frame->linesize[2],
                 (avctx->height + 3) >> 2);

    *got_frame = 1;

    return buf_size;
}