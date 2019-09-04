#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_13__ {int width; int height; int pix_fmt; } ;
struct TYPE_12__ {int** data; int* linesize; } ;
struct TYPE_11__ {int* data; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ AVPacket ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int ALIAS_HEADER_SIZE ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
#define  AV_PIX_FMT_BGR24 129 
#define  AV_PIX_FMT_GRAY8 128 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int AV_RB24 (int*) ; 
 int /*<<< orphan*/  EINVAL ; 
 int INT_MAX ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  av_shrink_packet (TYPE_1__*,int) ; 
 int /*<<< orphan*/  bytestream_put_be16 (int**,int) ; 
 int /*<<< orphan*/  bytestream_put_be24 (int**,int) ; 
 int /*<<< orphan*/  bytestream_put_be32 (int**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bytestream_put_byte (int**,int) ; 
 int ff_alloc_packet2 (TYPE_3__*,TYPE_1__*,int,int) ; 

__attribute__((used)) static int encode_frame(AVCodecContext *avctx, AVPacket *pkt,
                        const AVFrame *frame, int *got_packet)
{
    int width, height, bits_pixel, i, j, length, ret;
    uint8_t *in_buf, *buf;

#if FF_API_CODED_FRAME
FF_DISABLE_DEPRECATION_WARNINGS
    avctx->coded_frame->pict_type = AV_PICTURE_TYPE_I;
    avctx->coded_frame->key_frame = 1;
FF_ENABLE_DEPRECATION_WARNINGS
#endif

    width  = avctx->width;
    height = avctx->height;

    if (width > 65535 || height > 65535 ||
        width * height >= INT_MAX / 4 - ALIAS_HEADER_SIZE) {
        av_log(avctx, AV_LOG_ERROR, "Invalid image size %dx%d.\n", width, height);
        return AVERROR_INVALIDDATA;
    }

    switch (avctx->pix_fmt) {
    case AV_PIX_FMT_GRAY8:
        bits_pixel = 8;
        break;
    case AV_PIX_FMT_BGR24:
        bits_pixel = 24;
        break;
    default:
        return AVERROR(EINVAL);
    }

    length = ALIAS_HEADER_SIZE + 4 * width * height; // max possible
    if ((ret = ff_alloc_packet2(avctx, pkt, length, ALIAS_HEADER_SIZE + height*2)) < 0) {
        av_log(avctx, AV_LOG_ERROR, "Error getting output packet of size %d.\n", length);
        return ret;
    }

    buf = pkt->data;

    /* Encode header. */
    bytestream_put_be16(&buf, width);
    bytestream_put_be16(&buf, height);
    bytestream_put_be32(&buf, 0); /* X, Y offset */
    bytestream_put_be16(&buf, bits_pixel);

    for (j = 0; j < height; j++) {
        in_buf = frame->data[0] + frame->linesize[0] * j;
        for (i = 0; i < width; ) {
            int count = 0;
            int pixel;

            if (avctx->pix_fmt == AV_PIX_FMT_GRAY8) {
                pixel = *in_buf;
                while (count < 255 && count + i < width && pixel == *in_buf) {
                    count++;
                    in_buf++;
                }
                bytestream_put_byte(&buf, count);
                bytestream_put_byte(&buf, pixel);
            } else { /* AV_PIX_FMT_BGR24 */
                pixel = AV_RB24(in_buf);
                while (count < 255 && count + i < width &&
                       pixel == AV_RB24(in_buf)) {
                    count++;
                    in_buf += 3;
                }
                bytestream_put_byte(&buf, count);
                bytestream_put_be24(&buf, pixel);
            }
            i += count;
        }
    }

    /* Total length */
    av_shrink_packet(pkt, buf - pkt->data);
    pkt->flags |= AV_PKT_FLAG_KEY;
    *got_packet = 1;

    return 0;
}