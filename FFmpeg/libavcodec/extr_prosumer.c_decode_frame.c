#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int int64_t ;
struct TYPE_12__ {int height; int width; scalar_t__ discard_damaged_percentage; TYPE_1__* priv_data; } ;
struct TYPE_11__ {int* linesize; int key_frame; int /*<<< orphan*/  pict_type; int /*<<< orphan*/ ** data; } ;
struct TYPE_10__ {int size; int /*<<< orphan*/  data; } ;
struct TYPE_9__ {int size; int stride; int /*<<< orphan*/ * decbuffer; scalar_t__ initial_line; int /*<<< orphan*/  pb; int /*<<< orphan*/  lut; int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ ProSumerContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
 int AV_RL32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int bytestream2_get_bytes_left_p (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bytestream2_init_writer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int bytestream2_tell_p (int /*<<< orphan*/ *) ; 
 int decompress (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ff_get_buffer (TYPE_4__*,TYPE_3__* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vertical_predict (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int decode_frame(AVCodecContext *avctx, void *data,
                        int *got_frame, AVPacket *avpkt)
{
    ProSumerContext *s = avctx->priv_data;
    AVFrame * const frame = data;
    int ret;

    if (avpkt->size <= 32)
        return AVERROR_INVALIDDATA;

    bytestream2_init(&s->gb, avpkt->data, avpkt->size);
    bytestream2_init_writer(&s->pb, s->decbuffer, s->size);
    ret = decompress(&s->gb, AV_RL32(avpkt->data + 28) >> 1, &s->pb, s->lut);
    if (ret < 0)
        return ret;
    if (bytestream2_get_bytes_left_p(&s->pb) > s->size * (int64_t)avctx->discard_damaged_percentage / 100)
        return AVERROR_INVALIDDATA;

    av_assert0(s->size >= bytestream2_get_bytes_left_p(&s->pb));
    memset(s->decbuffer + bytestream2_tell_p(&s->pb), 0, bytestream2_get_bytes_left_p(&s->pb));

    vertical_predict((uint32_t *)s->decbuffer, 0, (uint32_t *)s->initial_line, s->stride, 1);
    vertical_predict((uint32_t *)s->decbuffer, s->stride, (uint32_t *)s->decbuffer, s->stride, avctx->height - 1);

    ret = ff_get_buffer(avctx, frame, 0);
    if (ret < 0)
        return ret;

    for (int i = avctx->height - 1; i >= 0 ; i--) {
        uint8_t *y = &frame->data[0][i * frame->linesize[0]];
        uint8_t *u = &frame->data[1][i * frame->linesize[1]];
        uint8_t *v = &frame->data[2][i * frame->linesize[2]];
        const uint8_t *src = s->decbuffer + (avctx->height - 1 - i) * s->stride;

        for (int j = 0; j < avctx->width; j += 8) {
            *(u++) = *src++;
            *(y++) = *src++;
            *(v++) = *src++;
            *(y++) = *src++;

            *(u++) = *src++;
            *(y++) = *src++;
            *(v++) = *src++;
            *(y++) = *src++;

            *(y++) = *src++;
            *(y++) = *src++;
            *(y++) = *src++;
            *(y++) = *src++;
        }
    }

    frame->pict_type = AV_PICTURE_TYPE_I;
    frame->key_frame = 1;
    *got_frame = 1;

    return avpkt->size;
}