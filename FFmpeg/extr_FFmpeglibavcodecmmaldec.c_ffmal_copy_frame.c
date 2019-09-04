#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_21__ {scalar_t__ pix_fmt; int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_4__* priv_data; } ;
struct TYPE_20__ {void* pkt_dts; void* pts; int /*<<< orphan*/  linesize; int /*<<< orphan*/  data; int /*<<< orphan*/  top_field_first; int /*<<< orphan*/  interlaced_frame; } ;
struct TYPE_19__ {int /*<<< orphan*/  pool_out; int /*<<< orphan*/  top_field_first; int /*<<< orphan*/  interlaced_frame; } ;
struct TYPE_18__ {scalar_t__ pts; TYPE_2__* type; scalar_t__ data; } ;
struct TYPE_16__ {scalar_t__* offset; } ;
struct TYPE_17__ {TYPE_1__ video; } ;
typedef  TYPE_3__ MMAL_BUFFER_HEADER_T ;
typedef  TYPE_4__ MMALDecodeContext ;
typedef  TYPE_5__ AVFrame ;
typedef  TYPE_6__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_UNKNOWN ; 
 void* AV_NOPTS_VALUE ; 
 scalar_t__ AV_PIX_FMT_MMAL ; 
 int FFALIGN (int /*<<< orphan*/ ,int) ; 
 scalar_t__ MMAL_TIME_UNKNOWN ; 
 int /*<<< orphan*/  av_image_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_image_fill_arrays (int /*<<< orphan*/ **,int*,scalar_t__,scalar_t__,int,int,int) ; 
 int ff_decode_frame_props (TYPE_6__*,TYPE_5__*) ; 
 int ff_get_buffer (TYPE_6__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int ffmmal_set_ref (TYPE_5__*,int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static int ffmal_copy_frame(AVCodecContext *avctx,  AVFrame *frame,
                            MMAL_BUFFER_HEADER_T *buffer)
{
    MMALDecodeContext *ctx = avctx->priv_data;
    int ret = 0;

    frame->interlaced_frame = ctx->interlaced_frame;
    frame->top_field_first = ctx->top_field_first;

    if (avctx->pix_fmt == AV_PIX_FMT_MMAL) {
        if (!ctx->pool_out)
            return AVERROR_UNKNOWN; // format change code failed with OOM previously

        if ((ret = ff_decode_frame_props(avctx, frame)) < 0)
            goto done;

        if ((ret = ffmmal_set_ref(frame, ctx->pool_out, buffer)) < 0)
            goto done;
    } else {
        int w = FFALIGN(avctx->width, 32);
        int h = FFALIGN(avctx->height, 16);
        uint8_t *src[4];
        int linesize[4];

        if ((ret = ff_get_buffer(avctx, frame, 0)) < 0)
            goto done;

        av_image_fill_arrays(src, linesize,
                             buffer->data + buffer->type->video.offset[0],
                             avctx->pix_fmt, w, h, 1);
        av_image_copy(frame->data, frame->linesize, src, linesize,
                      avctx->pix_fmt, avctx->width, avctx->height);
    }

    frame->pts = buffer->pts == MMAL_TIME_UNKNOWN ? AV_NOPTS_VALUE : buffer->pts;
#if FF_API_PKT_PTS
FF_DISABLE_DEPRECATION_WARNINGS
    frame->pkt_pts = frame->pts;
FF_ENABLE_DEPRECATION_WARNINGS
#endif
    frame->pkt_dts = AV_NOPTS_VALUE;

done:
    return ret;
}