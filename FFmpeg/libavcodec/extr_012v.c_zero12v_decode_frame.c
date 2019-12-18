#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_11__ {int width; int height; scalar_t__ codec_tag; } ;
struct TYPE_10__ {int key_frame; int* linesize; scalar_t__* data; int /*<<< orphan*/  pict_type; } ;
struct TYPE_9__ {int size; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ AVPacket ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
 int AV_RL32 (int /*<<< orphan*/  const*) ; 
 scalar_t__ MKTAG (int /*<<< orphan*/ ,char,char,char) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int const,int) ; 
 int ff_get_buffer (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

__attribute__((used)) static int zero12v_decode_frame(AVCodecContext *avctx, void *data,
                                int *got_frame, AVPacket *avpkt)
{
    int line, ret;
    const int width = avctx->width;
    AVFrame *pic = data;
    uint16_t *y, *u, *v;
    const uint8_t *line_end, *src = avpkt->data;
    int stride = avctx->width * 8 / 3;

    if (width <= 1 || avctx->height <= 0) {
        av_log(avctx, AV_LOG_ERROR, "Dimensions %dx%d not supported.\n", width, avctx->height);
        return AVERROR_INVALIDDATA;
    }

    if (   avctx->codec_tag == MKTAG('0', '1', '2', 'v')
        && avpkt->size % avctx->height == 0
        && avpkt->size / avctx->height * 3 >= width * 8)
        stride = avpkt->size / avctx->height;

    if (avpkt->size < avctx->height * stride) {
        av_log(avctx, AV_LOG_ERROR, "Packet too small: %d instead of %d\n",
               avpkt->size, avctx->height * stride);
        return AVERROR_INVALIDDATA;
    }

    if ((ret = ff_get_buffer(avctx, pic, 0)) < 0)
        return ret;

    pic->pict_type = AV_PICTURE_TYPE_I;
    pic->key_frame = 1;

    line_end = avpkt->data + stride;
    for (line = 0; line < avctx->height; line++) {
        uint16_t y_temp[6] = {0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000};
        uint16_t u_temp[3] = {0x8000, 0x8000, 0x8000};
        uint16_t v_temp[3] = {0x8000, 0x8000, 0x8000};
        int x;
        y = (uint16_t *)(pic->data[0] + line * pic->linesize[0]);
        u = (uint16_t *)(pic->data[1] + line * pic->linesize[1]);
        v = (uint16_t *)(pic->data[2] + line * pic->linesize[2]);

        for (x = 0; x < width; x += 6) {
            uint32_t t;

            if (width - x < 6 || line_end - src < 16) {
                y = y_temp;
                u = u_temp;
                v = v_temp;
            }

            if (line_end - src < 4)
                break;

            t = AV_RL32(src);
            src += 4;
            *u++ = t <<  6 & 0xFFC0;
            *y++ = t >>  4 & 0xFFC0;
            *v++ = t >> 14 & 0xFFC0;

            if (line_end - src < 4)
                break;

            t = AV_RL32(src);
            src += 4;
            *y++ = t <<  6 & 0xFFC0;
            *u++ = t >>  4 & 0xFFC0;
            *y++ = t >> 14 & 0xFFC0;

            if (line_end - src < 4)
                break;

            t = AV_RL32(src);
            src += 4;
            *v++ = t <<  6 & 0xFFC0;
            *y++ = t >>  4 & 0xFFC0;
            *u++ = t >> 14 & 0xFFC0;

            if (line_end - src < 4)
                break;

            t = AV_RL32(src);
            src += 4;
            *y++ = t <<  6 & 0xFFC0;
            *v++ = t >>  4 & 0xFFC0;
            *y++ = t >> 14 & 0xFFC0;

            if (width - x < 6)
                break;
        }

        if (x < width) {
            y = x   + (uint16_t *)(pic->data[0] + line * pic->linesize[0]);
            u = x/2 + (uint16_t *)(pic->data[1] + line * pic->linesize[1]);
            v = x/2 + (uint16_t *)(pic->data[2] + line * pic->linesize[2]);
            memcpy(y, y_temp, sizeof(*y) * (width - x));
            memcpy(u, u_temp, sizeof(*u) * (width - x + 1) / 2);
            memcpy(v, v_temp, sizeof(*v) * (width - x + 1) / 2);
        }

        line_end += stride;
        src = line_end - stride;
    }

    *got_frame = 1;

    return avpkt->size;
}