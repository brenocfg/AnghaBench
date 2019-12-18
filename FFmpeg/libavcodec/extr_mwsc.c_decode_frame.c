#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_20__ {int avail_in; int total_out; int /*<<< orphan*/  avail_out; int /*<<< orphan*/  next_out; int /*<<< orphan*/ * next_in; } ;
struct TYPE_19__ {int height; int width; TYPE_1__* priv_data; } ;
struct TYPE_18__ {int* linesize; scalar_t__ key_frame; int /*<<< orphan*/  pict_type; int /*<<< orphan*/ * data; } ;
struct TYPE_17__ {int size; int /*<<< orphan*/ * data; } ;
struct TYPE_16__ {TYPE_12__* prev_frame; TYPE_5__ zstream; int /*<<< orphan*/  decomp_buf; int /*<<< orphan*/  decomp_size; } ;
struct TYPE_15__ {int* linesize; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  PutByteContext ;
typedef  TYPE_1__ MWSCContext ;
typedef  int /*<<< orphan*/  GetByteContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_EXTERNAL ; 
 int /*<<< orphan*/  AV_GET_BUFFER_FLAG_REF ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_P ; 
 int /*<<< orphan*/  Z_FINISH ; 
 int Z_OK ; 
 int Z_STREAM_END ; 
 int av_frame_ref (TYPE_12__*,TYPE_3__*) ; 
 int /*<<< orphan*/  av_frame_unref (TYPE_12__*) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  bytestream2_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bytestream2_init_writer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int ff_get_buffer (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int inflate (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int inflateReset (TYPE_5__*) ; 
 scalar_t__ rle_uncompress (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int,int) ; 

__attribute__((used)) static int decode_frame(AVCodecContext *avctx,
                        void *data, int *got_frame,
                        AVPacket *avpkt)
{
    MWSCContext *s = avctx->priv_data;
    AVFrame *frame = data;
    uint8_t *buf = avpkt->data;
    int buf_size = avpkt->size;
    GetByteContext gb;
    GetByteContext gbp;
    PutByteContext pb;
    int ret;

    ret = inflateReset(&s->zstream);
    if (ret != Z_OK) {
        av_log(avctx, AV_LOG_ERROR, "Inflate reset error: %d\n", ret);
        return AVERROR_EXTERNAL;
    }
    s->zstream.next_in   = buf;
    s->zstream.avail_in  = buf_size;
    s->zstream.next_out  = s->decomp_buf;
    s->zstream.avail_out = s->decomp_size;
    ret = inflate(&s->zstream, Z_FINISH);
    if (ret != Z_STREAM_END) {
        av_log(avctx, AV_LOG_ERROR, "Inflate error: %d\n", ret);
        return AVERROR_EXTERNAL;
    }

    if ((ret = ff_get_buffer(avctx, frame, AV_GET_BUFFER_FLAG_REF)) < 0)
        return ret;

    bytestream2_init(&gb, s->decomp_buf, s->zstream.total_out);
    bytestream2_init(&gbp, s->prev_frame->data[0], avctx->height * s->prev_frame->linesize[0]);
    bytestream2_init_writer(&pb, frame->data[0], avctx->height * frame->linesize[0]);

    frame->key_frame = rle_uncompress(&gb, &pb, &gbp, avctx->width, avctx->height, avctx->width * 3,
                                      frame->linesize[0], s->prev_frame->linesize[0]);

    frame->pict_type = frame->key_frame ? AV_PICTURE_TYPE_I : AV_PICTURE_TYPE_P;

    av_frame_unref(s->prev_frame);
    if ((ret = av_frame_ref(s->prev_frame, frame)) < 0)
        return ret;

    *got_frame = 1;

    return avpkt->size;
}