#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_20__ {int palettes_count; unsigned int* palettes; int cur_palette; int frame_size; int size; int /*<<< orphan*/  last_frame; int /*<<< orphan*/  buf; TYPE_5__* avctx; } ;
typedef  TYPE_1__ XanContext ;
struct TYPE_24__ {int height; TYPE_1__* priv_data; } ;
struct TYPE_23__ {int* linesize; int /*<<< orphan*/ * data; } ;
struct TYPE_22__ {int size; int /*<<< orphan*/ * data; } ;
struct TYPE_21__ {int /*<<< orphan*/  buffer; } ;
typedef  TYPE_2__ GetByteContext ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int AVPALETTE_COUNT ; 
 int /*<<< orphan*/  AVPALETTE_SIZE ; 
 int /*<<< orphan*/  AV_GET_BUFFER_FLAG_REF ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFMIN (int,int) ; 
 int PALETTES_MAX ; 
 int PALETTE_COUNT ; 
 int PALETTE_SIZE ; 
#define  PALT_TAG 130 
#define  SHOT_TAG 129 
#define  VGA__TAG 128 
 int av_frame_ref (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  av_frame_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,...) ; 
 unsigned int* av_realloc_array (unsigned int*,int,int /*<<< orphan*/ ) ; 
 int bytestream2_get_be32 (TYPE_2__*) ; 
 int bytestream2_get_bytes_left (TYPE_2__*) ; 
 size_t bytestream2_get_byteu (TYPE_2__*) ; 
 void* bytestream2_get_le32 (TYPE_2__*) ; 
 int /*<<< orphan*/  bytestream2_init (TYPE_2__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  bytestream2_skip (TYPE_2__*,int) ; 
 int ff_get_buffer (TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int gamma_corr (size_t) ; 
 int* gamma_lookup ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned int*,int /*<<< orphan*/ ) ; 
 scalar_t__ xan_wc3_decode_frame (TYPE_1__*,TYPE_4__*) ; 

__attribute__((used)) static int xan_decode_frame(AVCodecContext *avctx,
                            void *data, int *got_frame,
                            AVPacket *avpkt)
{
    AVFrame *frame = data;
    const uint8_t *buf = avpkt->data;
    int ret, buf_size = avpkt->size;
    XanContext *s = avctx->priv_data;
    GetByteContext ctx;
    int tag = 0;

    bytestream2_init(&ctx, buf, buf_size);
    while (bytestream2_get_bytes_left(&ctx) > 8 && tag != VGA__TAG) {
        unsigned *tmpptr;
        uint32_t new_pal;
        int size;
        int i;
        tag  = bytestream2_get_le32(&ctx);
        size = bytestream2_get_be32(&ctx);
        if (size < 0) {
            av_log(avctx, AV_LOG_ERROR, "Invalid tag size %d\n", size);
            return AVERROR_INVALIDDATA;
        }
        size = FFMIN(size, bytestream2_get_bytes_left(&ctx));
        switch (tag) {
        case PALT_TAG:
            if (size < PALETTE_SIZE)
                return AVERROR_INVALIDDATA;
            if (s->palettes_count >= PALETTES_MAX)
                return AVERROR_INVALIDDATA;
            tmpptr = av_realloc_array(s->palettes,
                                      s->palettes_count + 1, AVPALETTE_SIZE);
            if (!tmpptr)
                return AVERROR(ENOMEM);
            s->palettes = tmpptr;
            tmpptr += s->palettes_count * AVPALETTE_COUNT;
            for (i = 0; i < PALETTE_COUNT; i++) {
#if RUNTIME_GAMMA
                int r = gamma_corr(bytestream2_get_byteu(&ctx));
                int g = gamma_corr(bytestream2_get_byteu(&ctx));
                int b = gamma_corr(bytestream2_get_byteu(&ctx));
#else
                int r = gamma_lookup[bytestream2_get_byteu(&ctx)];
                int g = gamma_lookup[bytestream2_get_byteu(&ctx)];
                int b = gamma_lookup[bytestream2_get_byteu(&ctx)];
#endif
                *tmpptr++ = (0xFFU << 24) | (r << 16) | (g << 8) | b;
            }
            s->palettes_count++;
            break;
        case SHOT_TAG:
            if (size < 4)
                return AVERROR_INVALIDDATA;
            new_pal = bytestream2_get_le32(&ctx);
            if (new_pal < s->palettes_count) {
                s->cur_palette = new_pal;
            } else
                av_log(avctx, AV_LOG_ERROR, "Invalid palette selected\n");
            break;
        case VGA__TAG:
            break;
        default:
            bytestream2_skip(&ctx, size);
            break;
        }
    }
    buf_size = bytestream2_get_bytes_left(&ctx);

    if (s->palettes_count <= 0) {
        av_log(s->avctx, AV_LOG_ERROR, "No palette found\n");
        return AVERROR_INVALIDDATA;
    }

    if ((ret = ff_get_buffer(avctx, frame, AV_GET_BUFFER_FLAG_REF)) < 0)
        return ret;

    if (!s->frame_size)
        s->frame_size = frame->linesize[0] * s->avctx->height;

    memcpy(frame->data[1],
           s->palettes + s->cur_palette * AVPALETTE_COUNT, AVPALETTE_SIZE);

    s->buf = ctx.buffer;
    s->size = buf_size;

    if (xan_wc3_decode_frame(s, frame) < 0)
        return AVERROR_INVALIDDATA;

    av_frame_unref(s->last_frame);
    if ((ret = av_frame_ref(s->last_frame, frame)) < 0)
        return ret;

    *got_frame = 1;

    /* always report that the buffer was completely consumed */
    return buf_size;
}