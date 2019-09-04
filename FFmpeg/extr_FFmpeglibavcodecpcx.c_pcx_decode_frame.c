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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_11__ {void* den; void* num; } ;
struct TYPE_14__ {int err_recognition; int /*<<< orphan*/  pix_fmt; TYPE_1__ sample_aspect_ratio; } ;
struct TYPE_13__ {int** data; unsigned int* linesize; int /*<<< orphan*/  pict_type; } ;
struct TYPE_12__ {int size; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  GetByteContext ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int AV_EF_EXPLODE ; 
 scalar_t__ AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
 int /*<<< orphan*/  AV_PIX_FMT_PAL8 ; 
 int /*<<< orphan*/  AV_PIX_FMT_RGB24 ; 
 int /*<<< orphan*/  AV_WN32A (int*,int) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int PCX_HEADER_SIZE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  av_free (int*) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int* av_malloc (scalar_t__) ; 
 int bytestream2_get_byte (int /*<<< orphan*/ *) ; 
 unsigned int bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 int bytestream2_get_byteu (int /*<<< orphan*/ *) ; 
 void* bytestream2_get_le16u (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bytestream2_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bytestream2_skipu (int /*<<< orphan*/ *,int) ; 
 int bytestream2_tell (int /*<<< orphan*/ *) ; 
 int ff_get_buffer (TYPE_4__*,TYPE_3__* const,int /*<<< orphan*/ ) ; 
 int ff_set_dimensions (TYPE_4__*,unsigned int,unsigned int) ; 
 int get_bits (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  init_get_bits8 (int /*<<< orphan*/ *,int*,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,unsigned int) ; 
 int /*<<< orphan*/  pcx_palette (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pcx_rle_decode (int /*<<< orphan*/ *,int*,unsigned int,int) ; 

__attribute__((used)) static int pcx_decode_frame(AVCodecContext *avctx, void *data, int *got_frame,
                            AVPacket *avpkt)
{
    GetByteContext gb;
    AVFrame * const p  = data;
    int compressed, xmin, ymin, xmax, ymax;
    int ret;
    unsigned int w, h, bits_per_pixel, bytes_per_line, nplanes, stride, y, x,
                 bytes_per_scanline;
    uint8_t *ptr, *scanline;

    if (avpkt->size < PCX_HEADER_SIZE) {
        av_log(avctx, AV_LOG_ERROR, "Packet too small\n");
        return AVERROR_INVALIDDATA;
    }

    bytestream2_init(&gb, avpkt->data, avpkt->size);

    if (bytestream2_get_byteu(&gb) != 0x0a || bytestream2_get_byteu(&gb) > 5) {
        av_log(avctx, AV_LOG_ERROR, "this is not PCX encoded data\n");
        return AVERROR_INVALIDDATA;
    }

    compressed                     = bytestream2_get_byteu(&gb);
    bits_per_pixel                 = bytestream2_get_byteu(&gb);
    xmin                           = bytestream2_get_le16u(&gb);
    ymin                           = bytestream2_get_le16u(&gb);
    xmax                           = bytestream2_get_le16u(&gb);
    ymax                           = bytestream2_get_le16u(&gb);
    avctx->sample_aspect_ratio.num = bytestream2_get_le16u(&gb);
    avctx->sample_aspect_ratio.den = bytestream2_get_le16u(&gb);

    if (xmax < xmin || ymax < ymin) {
        av_log(avctx, AV_LOG_ERROR, "invalid image dimensions\n");
        return AVERROR_INVALIDDATA;
    }

    w = xmax - xmin + 1;
    h = ymax - ymin + 1;

    bytestream2_skipu(&gb, 49);
    nplanes            = bytestream2_get_byteu(&gb);
    bytes_per_line     = bytestream2_get_le16u(&gb);
    bytes_per_scanline = nplanes * bytes_per_line;

    if (bytes_per_scanline < (w * bits_per_pixel * nplanes + 7) / 8 ||
        (!compressed && bytes_per_scanline > bytestream2_get_bytes_left(&gb) / h)) {
        av_log(avctx, AV_LOG_ERROR, "PCX data is corrupted\n");
        return AVERROR_INVALIDDATA;
    }

    switch ((nplanes << 8) + bits_per_pixel) {
    case 0x0308:
        avctx->pix_fmt = AV_PIX_FMT_RGB24;
        break;
    case 0x0108:
    case 0x0104:
    case 0x0102:
    case 0x0101:
    case 0x0401:
    case 0x0301:
    case 0x0201:
        avctx->pix_fmt = AV_PIX_FMT_PAL8;
        break;
    default:
        av_log(avctx, AV_LOG_ERROR, "invalid PCX file\n");
        return AVERROR_INVALIDDATA;
    }

    bytestream2_skipu(&gb, 60);

    if ((ret = ff_set_dimensions(avctx, w, h)) < 0)
        return ret;

    if ((ret = ff_get_buffer(avctx, p, 0)) < 0)
        return ret;

    p->pict_type = AV_PICTURE_TYPE_I;

    ptr    = p->data[0];
    stride = p->linesize[0];

    scanline = av_malloc(bytes_per_scanline + AV_INPUT_BUFFER_PADDING_SIZE);
    if (!scanline)
        return AVERROR(ENOMEM);

    if (nplanes == 3 && bits_per_pixel == 8) {
        for (y = 0; y < h; y++) {
            ret = pcx_rle_decode(&gb, scanline, bytes_per_scanline, compressed);
            if (ret < 0)
                goto end;

            for (x = 0; x < w; x++) {
                ptr[3 * x]     = scanline[x];
                ptr[3 * x + 1] = scanline[x + bytes_per_line];
                ptr[3 * x + 2] = scanline[x + (bytes_per_line << 1)];
            }

            ptr += stride;
        }
    } else if (nplanes == 1 && bits_per_pixel == 8) {
        int palstart = avpkt->size - 769;

        if (avpkt->size < 769) {
            av_log(avctx, AV_LOG_ERROR, "File is too short\n");
            ret = avctx->err_recognition & AV_EF_EXPLODE ?
                  AVERROR_INVALIDDATA : avpkt->size;
            goto end;
        }

        for (y = 0; y < h; y++, ptr += stride) {
            ret = pcx_rle_decode(&gb, scanline, bytes_per_scanline, compressed);
            if (ret < 0)
                goto end;
            memcpy(ptr, scanline, w);
        }

        if (bytestream2_tell(&gb) != palstart) {
            av_log(avctx, AV_LOG_WARNING, "image data possibly corrupted\n");
            bytestream2_seek(&gb, palstart, SEEK_SET);
        }
        if (bytestream2_get_byte(&gb) != 12) {
            av_log(avctx, AV_LOG_ERROR, "expected palette after image data\n");
            ret = avctx->err_recognition & AV_EF_EXPLODE ?
                  AVERROR_INVALIDDATA : avpkt->size;
            goto end;
        }
    } else if (nplanes == 1) {   /* all packed formats, max. 16 colors */
        GetBitContext s;

        for (y = 0; y < h; y++) {
            init_get_bits8(&s, scanline, bytes_per_scanline);

            ret = pcx_rle_decode(&gb, scanline, bytes_per_scanline, compressed);
            if (ret < 0)
                goto end;

            for (x = 0; x < w; x++)
                ptr[x] = get_bits(&s, bits_per_pixel);
            ptr += stride;
        }
    } else {    /* planar, 4, 8 or 16 colors */
        int i;

        for (y = 0; y < h; y++) {
            ret = pcx_rle_decode(&gb, scanline, bytes_per_scanline, compressed);
            if (ret < 0)
                goto end;

            for (x = 0; x < w; x++) {
                int m = 0x80 >> (x & 7), v = 0;
                for (i = nplanes - 1; i >= 0; i--) {
                    v <<= 1;
                    v  += !!(scanline[i * bytes_per_line + (x >> 3)] & m);
                }
                ptr[x] = v;
            }
            ptr += stride;
        }
    }

    ret = bytestream2_tell(&gb);
    if (nplanes == 1 && bits_per_pixel == 8) {
        pcx_palette(&gb, (uint32_t *)p->data[1], 256);
        ret += 256 * 3;
    } else if (bits_per_pixel * nplanes == 1) {
        AV_WN32A(p->data[1]  , 0xFF000000);
        AV_WN32A(p->data[1]+4, 0xFFFFFFFF);
    } else if (bits_per_pixel < 8) {
        bytestream2_seek(&gb, 16, SEEK_SET);
        pcx_palette(&gb, (uint32_t *)p->data[1], 16);
    }

    *got_frame = 1;

end:
    av_free(scanline);
    return ret;
}