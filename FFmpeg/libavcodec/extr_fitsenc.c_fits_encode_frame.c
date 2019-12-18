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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
typedef  int uint16_t ;
struct TYPE_12__ {int pix_fmt; int height; int width; } ;
struct TYPE_11__ {int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_10__ {int size; int /*<<< orphan*/  flags; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ AVPacket ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
#define  AV_PIX_FMT_GBRAP 133 
#define  AV_PIX_FMT_GBRAP16BE 132 
#define  AV_PIX_FMT_GBRP 131 
#define  AV_PIX_FMT_GBRP16BE 130 
#define  AV_PIX_FMT_GRAY16BE 129 
#define  AV_PIX_FMT_GRAY8 128 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int const AV_RB16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bytestream_put_be16 (int /*<<< orphan*/ **,int const) ; 
 int ff_alloc_packet2 (TYPE_3__*,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fits_encode_frame(AVCodecContext *avctx, AVPacket *pkt,
                            const AVFrame *pict, int *got_packet)
{
    AVFrame * const p = (AVFrame *)pict;
    uint8_t *bytestream, *bytestream_start, *ptr;
    const uint16_t flip = (1 << 15);
    uint64_t data_size = 0, padded_data_size = 0;
    int ret, bitpix, naxis3 = 1, i, j, k, bytes_left;
    int map[] = {2, 0, 1, 3}; // mapping from GBRA -> RGBA as RGBA is to be stored in FITS file..

    switch (avctx->pix_fmt) {
    case AV_PIX_FMT_GRAY8:
    case AV_PIX_FMT_GRAY16BE:
        map[0] = 0; // grayscale images should be directly mapped
        if (avctx->pix_fmt == AV_PIX_FMT_GRAY8) {
            bitpix = 8;
        } else {
            bitpix = 16;
        }
        break;
    case AV_PIX_FMT_GBRP:
    case AV_PIX_FMT_GBRAP:
        bitpix = 8;
        if (avctx->pix_fmt == AV_PIX_FMT_GBRP) {
            naxis3 = 3;
        } else {
            naxis3 = 4;
        }
        break;
    case AV_PIX_FMT_GBRP16BE:
    case AV_PIX_FMT_GBRAP16BE:
        bitpix = 16;
        if (avctx->pix_fmt == AV_PIX_FMT_GBRP16BE) {
            naxis3 = 3;
        } else {
            naxis3 = 4;
        }
        break;
    default:
        av_log(avctx, AV_LOG_ERROR, "unsupported pixel format\n");
        return AVERROR(EINVAL);
    }

    data_size = (bitpix >> 3) * avctx->height * avctx->width * naxis3;
    padded_data_size = ((data_size + 2879) / 2880 ) * 2880;

    if ((ret = ff_alloc_packet2(avctx, pkt, padded_data_size, 0)) < 0)
        return ret;

    bytestream_start =
    bytestream       = pkt->data;

    for (k = 0; k < naxis3; k++) {
        for (i = 0; i < avctx->height; i++) {
            ptr = p->data[map[k]] + (avctx->height - i - 1) * p->linesize[map[k]];
            if (bitpix == 16) {
                for (j = 0; j < avctx->width; j++) {
                    // subtracting bzero is equivalent to first bit flip
                    bytestream_put_be16(&bytestream, AV_RB16(ptr) ^ flip);
                    ptr += 2;
                }
            } else {
                memcpy(bytestream, ptr, avctx->width);
                bytestream += avctx->width;
            }
        }
    }

    bytes_left = padded_data_size - data_size;
    memset(bytestream, 0, bytes_left);
    bytestream += bytes_left;

    pkt->size   = bytestream - bytestream_start;
    pkt->flags |= AV_PKT_FLAG_KEY;
    *got_packet = 1;

    return 0;
}