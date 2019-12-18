#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_13__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_17__ {int width; int height; int* frame_buffer; int* palette; TYPE_13__* last_frame; TYPE_9__* avctx; } ;
typedef  TYPE_1__ TgvContext ;
struct TYPE_21__ {int width; int height; } ;
struct TYPE_20__ {TYPE_1__* priv_data; } ;
struct TYPE_19__ {int key_frame; int* linesize; int /*<<< orphan*/  pict_type; scalar_t__* data; } ;
struct TYPE_18__ {int size; int /*<<< orphan*/ * data; } ;
struct TYPE_16__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int AVPALETTE_COUNT ; 
 int AVPALETTE_SIZE ; 
 int /*<<< orphan*/  AV_GET_BUFFER_FLAG_REF ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_P ; 
 int AV_RB24 (int /*<<< orphan*/  const*) ; 
 void* AV_RL16 (int /*<<< orphan*/  const*) ; 
 int AV_RL32 (int /*<<< orphan*/  const*) ; 
 int EA_PREAMBLE_SIZE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int av_frame_ref (TYPE_13__*,TYPE_3__*) ; 
 int /*<<< orphan*/  av_frame_unref (TYPE_13__*) ; 
 int /*<<< orphan*/  av_freep (int**) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int* av_mallocz (int) ; 
 int ff_get_buffer (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int ff_set_dimensions (TYPE_9__*,int,int) ; 
 int kVGT_TAG ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int*,int) ; 
 scalar_t__ tgv_decode_inter (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ unpack (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int*,int,int) ; 

__attribute__((used)) static int tgv_decode_frame(AVCodecContext *avctx,
                            void *data, int *got_frame,
                            AVPacket *avpkt)
{
    const uint8_t *buf     = avpkt->data;
    int buf_size           = avpkt->size;
    TgvContext *s          = avctx->priv_data;
    const uint8_t *buf_end = buf + buf_size;
    AVFrame *frame         = data;
    int chunk_type, ret;

    if (buf_end - buf < EA_PREAMBLE_SIZE)
        return AVERROR_INVALIDDATA;

    chunk_type = AV_RL32(&buf[0]);
    buf       += EA_PREAMBLE_SIZE;

    if (chunk_type == kVGT_TAG) {
        int pal_count, i;
        if(buf_end - buf < 12) {
            av_log(avctx, AV_LOG_WARNING, "truncated header\n");
            return AVERROR_INVALIDDATA;
        }

        s->width  = AV_RL16(&buf[0]);
        s->height = AV_RL16(&buf[2]);
        if (s->avctx->width != s->width || s->avctx->height != s->height) {
            av_freep(&s->frame_buffer);
            av_frame_unref(s->last_frame);
            if ((ret = ff_set_dimensions(s->avctx, s->width, s->height)) < 0)
                return ret;
        }

        pal_count = AV_RL16(&buf[6]);
        buf += 12;
        for(i = 0; i < pal_count && i < AVPALETTE_COUNT && buf_end - buf >= 3; i++) {
            s->palette[i] = 0xFFU << 24 | AV_RB24(buf);
            buf += 3;
        }
        if (buf_end - buf < 5) {
            return AVERROR_INVALIDDATA;
        }
    }

    if ((ret = ff_get_buffer(avctx, frame, AV_GET_BUFFER_FLAG_REF)) < 0)
        return ret;

    memcpy(frame->data[1], s->palette, AVPALETTE_SIZE);

    if (chunk_type == kVGT_TAG) {
        int y;
        frame->key_frame = 1;
        frame->pict_type = AV_PICTURE_TYPE_I;

        if (!s->frame_buffer &&
            !(s->frame_buffer = av_mallocz(s->width * s->height)))
            return AVERROR(ENOMEM);

        if (unpack(buf, buf_end, s->frame_buffer, s->avctx->width, s->avctx->height) < 0) {
            av_log(avctx, AV_LOG_WARNING, "truncated intra frame\n");
            return AVERROR_INVALIDDATA;
        }
        for (y = 0; y < s->height; y++)
            memcpy(frame->data[0]  + y * frame->linesize[0],
                   s->frame_buffer + y * s->width,
                   s->width);
    } else {
        if (!s->last_frame->data[0]) {
            av_log(avctx, AV_LOG_WARNING, "inter frame without corresponding intra frame\n");
            return buf_size;
        }
        frame->key_frame = 0;
        frame->pict_type = AV_PICTURE_TYPE_P;
        if (tgv_decode_inter(s, frame, buf, buf_end) < 0) {
            av_log(avctx, AV_LOG_WARNING, "truncated inter frame\n");
            return AVERROR_INVALIDDATA;
        }
    }

    av_frame_unref(s->last_frame);
    if ((ret = av_frame_ref(s->last_frame, frame)) < 0)
        return ret;

    *got_frame = 1;

    return buf_size;
}