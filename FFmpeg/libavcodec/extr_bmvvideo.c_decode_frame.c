#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int int16_t ;
struct TYPE_13__ {int height; int /*<<< orphan*/  width; TYPE_1__* priv_data; } ;
struct TYPE_12__ {int** data; int palette_has_changed; int /*<<< orphan*/ * linesize; } ;
struct TYPE_11__ {scalar_t__ data; int size; } ;
struct TYPE_10__ {scalar_t__ stream; int* pal; int* frame; } ;
typedef  TYPE_1__ BMVDecContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AVPALETTE_SIZE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int BMV_AUDIO ; 
 int BMV_COMMAND ; 
 int BMV_INTRA ; 
 int BMV_PALETTE ; 
 int BMV_PRINT ; 
 int BMV_SCROLL ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int bytestream_get_be24 (scalar_t__*) ; 
 int bytestream_get_byte (scalar_t__*) ; 
 scalar_t__ bytestream_get_le16 (scalar_t__*) ; 
 scalar_t__ decode_bmv_frame (scalar_t__,scalar_t__,int*,int) ; 
 int ff_get_buffer (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decode_frame(AVCodecContext *avctx, void *data, int *got_frame,
                        AVPacket *pkt)
{
    BMVDecContext * const c = avctx->priv_data;
    AVFrame *frame = data;
    int type, scr_off;
    int i, ret;
    uint8_t *srcptr, *outptr;

    c->stream = pkt->data;
    type = bytestream_get_byte(&c->stream);
    if (type & BMV_AUDIO) {
        int blobs = bytestream_get_byte(&c->stream);
        if (pkt->size < blobs * 65 + 2) {
            av_log(avctx, AV_LOG_ERROR, "Audio data doesn't fit in frame\n");
            return AVERROR_INVALIDDATA;
        }
        c->stream += blobs * 65;
    }
    if (type & BMV_COMMAND) {
        int command_size = (type & BMV_PRINT) ? 8 : 10;
        if (c->stream - pkt->data + command_size > pkt->size) {
            av_log(avctx, AV_LOG_ERROR, "Command data doesn't fit in frame\n");
            return AVERROR_INVALIDDATA;
        }
        c->stream += command_size;
    }
    if (type & BMV_PALETTE) {
        if (c->stream - pkt->data > pkt->size - 768) {
            av_log(avctx, AV_LOG_ERROR, "Palette data doesn't fit in frame\n");
            return AVERROR_INVALIDDATA;
        }
        for (i = 0; i < 256; i++)
            c->pal[i] = 0xFFU << 24 | bytestream_get_be24(&c->stream);
    }
    if (type & BMV_SCROLL) {
        if (c->stream - pkt->data > pkt->size - 2) {
            av_log(avctx, AV_LOG_ERROR, "Screen offset data doesn't fit in frame\n");
            return AVERROR_INVALIDDATA;
        }
        scr_off = (int16_t)bytestream_get_le16(&c->stream);
    } else if ((type & BMV_INTRA) == BMV_INTRA) {
        scr_off = -640;
    } else {
        scr_off = 0;
    }

    if ((ret = ff_get_buffer(avctx, frame, 0)) < 0)
        return ret;

    if (decode_bmv_frame(c->stream, pkt->size - (c->stream - pkt->data), c->frame, scr_off)) {
        av_log(avctx, AV_LOG_ERROR, "Error decoding frame data\n");
        return AVERROR_INVALIDDATA;
    }

    memcpy(frame->data[1], c->pal, AVPALETTE_SIZE);
    frame->palette_has_changed = type & BMV_PALETTE;

    outptr = frame->data[0];
    srcptr = c->frame;

    for (i = 0; i < avctx->height; i++) {
        memcpy(outptr, srcptr, avctx->width);
        srcptr += avctx->width;
        outptr += frame->linesize[0];
    }

    *got_frame = 1;

    /* always report that the buffer was completely consumed */
    return pkt->size;
}