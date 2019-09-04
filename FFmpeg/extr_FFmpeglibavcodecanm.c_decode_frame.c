#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_13__ {int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_12__ {int height; int /*<<< orphan*/  width; TYPE_1__* priv_data; } ;
struct TYPE_11__ {int size; int /*<<< orphan*/  data; } ;
struct TYPE_10__ {TYPE_5__* frame; int /*<<< orphan*/  palette; scalar_t__ x; int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ AnmContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AVPALETTE_SIZE ; 
 int av_frame_ref (void*,TYPE_5__*) ; 
 int /*<<< orphan*/  avpriv_request_sample (TYPE_3__*,char*) ; 
 int bytestream2_get_byte (int /*<<< orphan*/ *) ; 
 scalar_t__ bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 int bytestream2_get_le16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  bytestream2_skip (int /*<<< orphan*/ *,int) ; 
 int ff_reget_buffer (TYPE_3__*,TYPE_5__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ op (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,scalar_t__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int decode_frame(AVCodecContext *avctx,
                        void *data, int *got_frame,
                        AVPacket *avpkt)
{
    AnmContext *s = avctx->priv_data;
    const int buf_size = avpkt->size;
    uint8_t *dst, *dst_end;
    int count, ret;

    if ((ret = ff_reget_buffer(avctx, s->frame)) < 0)
        return ret;
    dst     = s->frame->data[0];
    dst_end = s->frame->data[0] + s->frame->linesize[0]*avctx->height;

    bytestream2_init(&s->gb, avpkt->data, buf_size);

    if (bytestream2_get_byte(&s->gb) != 0x42) {
        avpriv_request_sample(avctx, "Unknown record type");
        return AVERROR_INVALIDDATA;
    }
    if (bytestream2_get_byte(&s->gb)) {
        avpriv_request_sample(avctx, "Padding bytes");
        return AVERROR_PATCHWELCOME;
    }
    bytestream2_skip(&s->gb, 2);

    s->x = 0;
    do {
        /* if statements are ordered by probability */
#define OP(gb, pixel, count) \
    op(&dst, dst_end, (gb), (pixel), (count), &s->x, avctx->width, s->frame->linesize[0])

        int type = bytestream2_get_byte(&s->gb);
        count = type & 0x7F;
        type >>= 7;
        if (count) {
            if (OP(type ? NULL : &s->gb, -1, count)) break;
        } else if (!type) {
            int pixel;
            count = bytestream2_get_byte(&s->gb);  /* count==0 gives nop */
            pixel = bytestream2_get_byte(&s->gb);
            if (OP(NULL, pixel, count)) break;
        } else {
            int pixel;
            type = bytestream2_get_le16(&s->gb);
            count = type & 0x3FFF;
            type >>= 14;
            if (!count) {
                if (type == 0)
                    break; // stop
                if (type == 2) {
                    avpriv_request_sample(avctx, "Unknown opcode");
                    return AVERROR_PATCHWELCOME;
                }
                continue;
            }
            pixel = type == 3 ? bytestream2_get_byte(&s->gb) : -1;
            if (type == 1) count += 0x4000;
            if (OP(type == 2 ? &s->gb : NULL, pixel, count)) break;
        }
    } while (bytestream2_get_bytes_left(&s->gb) > 0);

    memcpy(s->frame->data[1], s->palette, AVPALETTE_SIZE);

    *got_frame = 1;
    if ((ret = av_frame_ref(data, s->frame)) < 0)
        return ret;

    return buf_size;
}