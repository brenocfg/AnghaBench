#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned char uint8_t ;
struct TYPE_14__ {unsigned int height; scalar_t__ pix_fmt; int bits_per_coded_sample; TYPE_1__* priv_data; } ;
struct TYPE_13__ {unsigned char** data; unsigned int* linesize; int palette_has_changed; } ;
struct TYPE_12__ {unsigned char* data; int size; } ;
struct TYPE_11__ {unsigned int planes; unsigned char* planemap; unsigned char* pal; } ;
typedef  TYPE_1__ EightBpsContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AVPALETTE_SIZE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_PIX_FMT_0RGB32 ; 
 int /*<<< orphan*/  AV_PKT_DATA_PALETTE ; 
 unsigned int av_be2ne16 (unsigned short const) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,int) ; 
 unsigned char* av_packet_get_side_data (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int ff_get_buffer (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int) ; 

__attribute__((used)) static int decode_frame(AVCodecContext *avctx, void *data,
                        int *got_frame, AVPacket *avpkt)
{
    AVFrame *frame = data;
    const uint8_t *buf = avpkt->data;
    int buf_size       = avpkt->size;
    EightBpsContext * const c = avctx->priv_data;
    const unsigned char *encoded = buf;
    unsigned char *pixptr, *pixptr_end;
    unsigned int height = avctx->height; // Real image height
    unsigned int dlen, p, row;
    const unsigned char *lp, *dp, *ep;
    unsigned char count;
    unsigned int px_inc;
    unsigned int planes     = c->planes;
    unsigned char *planemap = c->planemap;
    int ret;

    if ((ret = ff_get_buffer(avctx, frame, 0)) < 0)
        return ret;

    ep = encoded + buf_size;

    /* Set data pointer after line lengths */
    dp = encoded + planes * (height << 1);

    px_inc = planes + (avctx->pix_fmt == AV_PIX_FMT_0RGB32);

    for (p = 0; p < planes; p++) {
        /* Lines length pointer for this plane */
        lp = encoded + p * (height << 1);

        /* Decode a plane */
        for (row = 0; row < height; row++) {
            pixptr = frame->data[0] + row * frame->linesize[0] + planemap[p];
            pixptr_end = pixptr + frame->linesize[0];
            if (ep - lp < row * 2 + 2)
                return AVERROR_INVALIDDATA;
            dlen = av_be2ne16(*(const unsigned short *)(lp + row * 2));
            /* Decode a row of this plane */
            while (dlen > 0) {
                if (ep - dp <= 1)
                    return AVERROR_INVALIDDATA;
                if ((count = *dp++) <= 127) {
                    count++;
                    dlen -= count + 1;
                    if (pixptr_end - pixptr < count * px_inc)
                        break;
                    if (ep - dp < count)
                        return AVERROR_INVALIDDATA;
                    while (count--) {
                        *pixptr = *dp++;
                        pixptr += px_inc;
                    }
                } else {
                    count = 257 - count;
                    if (pixptr_end - pixptr < count * px_inc)
                        break;
                    while (count--) {
                        *pixptr = *dp;
                        pixptr += px_inc;
                    }
                    dp++;
                    dlen -= 2;
                }
            }
        }
    }

    if (avctx->bits_per_coded_sample <= 8) {
        int size;
        const uint8_t *pal = av_packet_get_side_data(avpkt,
                                                     AV_PKT_DATA_PALETTE,
                                                     &size);
        if (pal && size == AVPALETTE_SIZE) {
            frame->palette_has_changed = 1;
            memcpy(c->pal, pal, AVPALETTE_SIZE);
        } else if (pal) {
            av_log(avctx, AV_LOG_ERROR, "Palette size %d is wrong\n", size);
        }

        memcpy (frame->data[1], c->pal, AVPALETTE_SIZE);
    }

    *got_frame = 1;

    /* always report that the buffer was completely consumed */
    return buf_size;
}