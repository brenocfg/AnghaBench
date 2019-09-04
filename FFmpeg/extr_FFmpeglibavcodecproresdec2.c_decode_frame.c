#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
struct TYPE_15__ {void* f; } ;
typedef  TYPE_1__ ThreadFrame ;
struct TYPE_19__ {TYPE_2__* priv_data; } ;
struct TYPE_18__ {int key_frame; int /*<<< orphan*/  pict_type; } ;
struct TYPE_17__ {char* data; int size; } ;
struct TYPE_16__ {int first_field; scalar_t__ frame_type; TYPE_4__* frame; } ;
typedef  TYPE_2__ ProresContext ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
 scalar_t__ AV_RL32 (char const*) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 int decode_frame_header (TYPE_2__*,char const*,int,TYPE_5__*) ; 
 int decode_picture (TYPE_5__*) ; 
 int decode_picture_header (TYPE_5__*,char const*,int) ; 
 int ff_thread_get_buffer (TYPE_5__*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decode_frame(AVCodecContext *avctx, void *data, int *got_frame,
                        AVPacket *avpkt)
{
    ProresContext *ctx = avctx->priv_data;
    ThreadFrame tframe = { .f = data };
    AVFrame *frame = data;
    const uint8_t *buf = avpkt->data;
    int buf_size = avpkt->size;
    int frame_hdr_size, pic_size, ret;

    if (buf_size < 28 || AV_RL32(buf + 4) != AV_RL32("icpf")) {
        av_log(avctx, AV_LOG_ERROR, "invalid frame header\n");
        return AVERROR_INVALIDDATA;
    }

    ctx->frame = frame;
    ctx->frame->pict_type = AV_PICTURE_TYPE_I;
    ctx->frame->key_frame = 1;
    ctx->first_field = 1;

    buf += 8;
    buf_size -= 8;

    frame_hdr_size = decode_frame_header(ctx, buf, buf_size, avctx);
    if (frame_hdr_size < 0)
        return frame_hdr_size;

    buf += frame_hdr_size;
    buf_size -= frame_hdr_size;

 decode_picture:
    pic_size = decode_picture_header(avctx, buf, buf_size);
    if (pic_size < 0) {
        av_log(avctx, AV_LOG_ERROR, "error decoding picture header\n");
        return pic_size;
    }

    if (ctx->first_field)
        if ((ret = ff_thread_get_buffer(avctx, &tframe, 0)) < 0)
            return ret;

    if ((ret = decode_picture(avctx)) < 0) {
        av_log(avctx, AV_LOG_ERROR, "error decoding picture\n");
        return ret;
    }

    buf += pic_size;
    buf_size -= pic_size;

    if (ctx->frame_type && buf_size > 0 && ctx->first_field) {
        ctx->first_field = 0;
        goto decode_picture;
    }

    *got_frame      = 1;

    return avpkt->size;
}