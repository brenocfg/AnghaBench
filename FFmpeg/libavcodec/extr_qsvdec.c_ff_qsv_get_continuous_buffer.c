#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_9__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ data; } ;
struct TYPE_11__ {int pix_fmt; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_10__ {int* linesize; scalar_t__* data; TYPE_9__** buf; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_1__ AVFrame ;
typedef  TYPE_2__ AVCodecContext ;
typedef  int /*<<< orphan*/  AVBufferPool ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
#define  AV_PIX_FMT_NV12 129 
#define  AV_PIX_FMT_P010 128 
 int /*<<< orphan*/  ENOMEM ; 
 int FFALIGN (int /*<<< orphan*/ ,int) ; 
 TYPE_9__* av_buffer_pool_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int ff_attach_decode_data (TYPE_1__*) ; 
 int /*<<< orphan*/  ff_decode_frame_props (TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static int ff_qsv_get_continuous_buffer(AVCodecContext *avctx, AVFrame *frame, AVBufferPool *pool)
{
    int ret = 0;

    ff_decode_frame_props(avctx, frame);

    frame->width       = avctx->width;
    frame->height      = avctx->height;

    switch (avctx->pix_fmt) {
    case AV_PIX_FMT_NV12:
        frame->linesize[0] = FFALIGN(avctx->width, 128);
        break;
    case AV_PIX_FMT_P010:
        frame->linesize[0] = 2 * FFALIGN(avctx->width, 128);
        break;
    default:
        av_log(avctx, AV_LOG_ERROR, "Unsupported pixel format.\n");
        return AVERROR(ENOMEM);
    }

    frame->linesize[1] = frame->linesize[0];
    frame->buf[0]      = av_buffer_pool_get(pool);
    if (!frame->buf[0])
        return AVERROR(ENOMEM);

    frame->data[0] = frame->buf[0]->data;
    frame->data[1] = frame->data[0] +
                            frame->linesize[0] * FFALIGN(avctx->height, 64);

    ret = ff_attach_decode_data(frame);
    if (ret < 0)
        return ret;

    return 0;
}