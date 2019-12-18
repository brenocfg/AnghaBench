#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_12__ {scalar_t__ pix_fmt; int width; int height; } ;
struct TYPE_11__ {int key_frame; int** data; int* linesize; int /*<<< orphan*/  pict_type; } ;
struct TYPE_10__ {int size; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  GetByteContext ;
typedef  TYPE_1__ AVPacket ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int ALIAS_HEADER_SIZE ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
 scalar_t__ AV_PIX_FMT_BGR24 ; 
 scalar_t__ AV_PIX_FMT_GRAY8 ; 
 int /*<<< orphan*/  AV_WB24 (int*,int) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 int bytestream2_get_be16u (int /*<<< orphan*/ *) ; 
 int bytestream2_get_be24 (int /*<<< orphan*/ *) ; 
 int bytestream2_get_byte (int /*<<< orphan*/ *) ; 
 int bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 int bytestream2_get_byteu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bytestream2_skipu (int /*<<< orphan*/ *,int) ; 
 int ff_get_buffer (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int ff_set_dimensions (TYPE_3__*,int,int) ; 

__attribute__((used)) static int decode_frame(AVCodecContext *avctx, void *data, int *got_frame,
                        AVPacket *avpkt)
{
    AVFrame *f = data;
    GetByteContext gb;
    int width, height, ret, bits_pixel, pixel;
    uint8_t *out_buf;
    uint8_t count;
    int x, y;

    bytestream2_init(&gb, avpkt->data, avpkt->size);

    if (bytestream2_get_bytes_left(&gb) < ALIAS_HEADER_SIZE) {
        av_log(avctx, AV_LOG_ERROR, "Header too small %d.\n", avpkt->size);
        return AVERROR_INVALIDDATA;
    }

    width  = bytestream2_get_be16u(&gb);
    height = bytestream2_get_be16u(&gb);
    bytestream2_skipu(&gb, 4); // obsolete X, Y offset
    bits_pixel = bytestream2_get_be16u(&gb);

    if (bits_pixel == 24)
        avctx->pix_fmt = AV_PIX_FMT_BGR24;
    else if (bits_pixel == 8)
        avctx->pix_fmt = AV_PIX_FMT_GRAY8;
    else {
        av_log(avctx, AV_LOG_ERROR, "Invalid pixel format.\n");
        return AVERROR_INVALIDDATA;
    }

    ret = ff_set_dimensions(avctx, width, height);
    if (ret < 0)
        return ret;

    if (bytestream2_get_bytes_left(&gb) < width*height / 255)
        return AVERROR_INVALIDDATA;

    ret = ff_get_buffer(avctx, f, 0);
    if (ret < 0)
        return ret;

    f->pict_type = AV_PICTURE_TYPE_I;
    f->key_frame = 1;

    x = 0;
    y = 1;
    out_buf = f->data[0];
    while (bytestream2_get_bytes_left(&gb) > 0) {
        int i;

        /* set buffer at the right position at every new line */
        if (x == avctx->width) {
            x = 0;
            out_buf = f->data[0] + f->linesize[0] * y++;
            if (y > avctx->height) {
                av_log(avctx, AV_LOG_ERROR,
                       "Ended frame decoding with %d bytes left.\n",
                       bytestream2_get_bytes_left(&gb));
                return AVERROR_INVALIDDATA;
            }
        }

        /* read packet and copy data */
        count = bytestream2_get_byteu(&gb);
        if (!count || x + count > avctx->width) {
            av_log(avctx, AV_LOG_ERROR, "Invalid run length %d.\n", count);
            return AVERROR_INVALIDDATA;
        }

        if (avctx->pix_fmt == AV_PIX_FMT_BGR24) {
            pixel = bytestream2_get_be24(&gb);
            for (i = 0; i < count; i++) {
                AV_WB24(out_buf, pixel);
                out_buf += 3;
            }
        } else { // AV_PIX_FMT_GRAY8
            pixel = bytestream2_get_byte(&gb);
            for (i = 0; i < count; i++)
                *out_buf++ = pixel;
        }

        x += i;
    }

    if (x != width || y != height) {
        av_log(avctx, AV_LOG_ERROR, "Picture stopped at %d,%d.\n", x, y);
        return AVERROR_INVALIDDATA;
    }

    *got_frame = 1;
    return avpkt->size;
}