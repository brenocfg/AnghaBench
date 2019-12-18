#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uLongf ;
struct TYPE_16__ {int* linesize; scalar_t__* data; } ;
struct TYPE_15__ {int width; int height; int /*<<< orphan*/  pix_fmt; TYPE_1__* priv_data; } ;
struct TYPE_14__ {int key_frame; int /*<<< orphan*/  pict_type; } ;
struct TYPE_13__ {int size; int* data; } ;
struct TYPE_12__ {TYPE_8__* current; int /*<<< orphan*/  inflated_buf; int /*<<< orphan*/  inflated_size; } ;
typedef  TYPE_1__ ScreenpressoContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AVERROR_UNKNOWN ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_P ; 
 int /*<<< orphan*/  AV_PIX_FMT_BGR0 ; 
 int /*<<< orphan*/  AV_PIX_FMT_BGR24 ; 
 int /*<<< orphan*/  AV_PIX_FMT_RGB555LE ; 
 int FFALIGN (int,int) ; 
 int av_frame_ref (TYPE_3__*,TYPE_8__*) ; 
 int /*<<< orphan*/  av_image_copy_plane (scalar_t__,int,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,int) ; 
 int ff_reget_buffer (TYPE_4__*,TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sum_delta_flipped (scalar_t__,int,int /*<<< orphan*/ ,int,int,int) ; 
 int uncompress (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int) ; 

__attribute__((used)) static int screenpresso_decode_frame(AVCodecContext *avctx, void *data,
                                     int *got_frame, AVPacket *avpkt)
{
    ScreenpressoContext *ctx = avctx->priv_data;
    AVFrame *frame = data;
    uLongf length = ctx->inflated_size;
    int keyframe, component_size, src_linesize;
    int ret;

    /* Size check */
    if (avpkt->size < 3) {
        av_log(avctx, AV_LOG_ERROR, "Packet too small (%d)\n", avpkt->size);
        return AVERROR_INVALIDDATA;
    }

    /* Compression level (4 bits) and keyframe information (1 bit) */
    av_log(avctx, AV_LOG_DEBUG, "Compression level %d\n", avpkt->data[0] >> 4);
    keyframe = avpkt->data[0] & 1;

    /* Pixel size */
    component_size = ((avpkt->data[1] >> 2) & 0x03) + 1;
    switch (component_size) {
    case 2:
        avctx->pix_fmt = AV_PIX_FMT_RGB555LE;
        break;
    case 3:
        avctx->pix_fmt = AV_PIX_FMT_BGR24;
        break;
    case 4:
        avctx->pix_fmt = AV_PIX_FMT_BGR0;
        break;
    default:
        av_log(avctx, AV_LOG_ERROR, "Invalid bits per pixel value (%d)\n",
               component_size);
        return AVERROR_INVALIDDATA;
    }

    /* Inflate the frame after the 2 byte header */
    ret = uncompress(ctx->inflated_buf, &length,
                     avpkt->data + 2, avpkt->size - 2);
    if (ret) {
        av_log(avctx, AV_LOG_ERROR, "Deflate error %d.\n", ret);
        return AVERROR_UNKNOWN;
    }

    ret = ff_reget_buffer(avctx, ctx->current, 0);
    if (ret < 0)
        return ret;

    /* Codec has aligned strides */
    src_linesize = FFALIGN(avctx->width * component_size, 4);

    /* When a keyframe is found, copy it (flipped) */
    if (keyframe)
        av_image_copy_plane(ctx->current->data[0] +
                            ctx->current->linesize[0] * (avctx->height - 1),
                            -1 * ctx->current->linesize[0],
                            ctx->inflated_buf, src_linesize,
                            avctx->width * component_size, avctx->height);
    /* Otherwise sum the delta on top of the current frame */
    else
        sum_delta_flipped(ctx->current->data[0], ctx->current->linesize[0],
                          ctx->inflated_buf, src_linesize,
                          avctx->width * component_size, avctx->height);

    /* Frame is ready to be output */
    ret = av_frame_ref(frame, ctx->current);
    if (ret < 0)
        return ret;

    /* Usual properties */
    if (keyframe) {
        frame->pict_type = AV_PICTURE_TYPE_I;
        frame->key_frame = 1;
    } else {
        frame->pict_type = AV_PICTURE_TYPE_P;
    }
    *got_frame = 1;

    return avpkt->size;
}