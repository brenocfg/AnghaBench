#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_11__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int int64_t ;
struct TYPE_19__ {scalar_t__ pix_fmt; TYPE_1__* priv_data; } ;
struct TYPE_18__ {int** data; int* linesize; int palette_has_changed; int /*<<< orphan*/  pict_type; } ;
struct TYPE_17__ {int size; int /*<<< orphan*/  data; } ;
struct TYPE_15__ {int* buffer; } ;
struct TYPE_16__ {int channel_count; int channel_depth; int* tmp; int line_size; int pixel_size; int width; int color_mode; int uncompressed_size; int height; scalar_t__ compression; int const* palette; TYPE_11__ gb; TYPE_4__* avctx; } ;
typedef  TYPE_1__ PSDContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int AVPALETTE_SIZE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
 scalar_t__ AV_PIX_FMT_GBRAP ; 
 scalar_t__ AV_PIX_FMT_GBRAP16BE ; 
 void* AV_PIX_FMT_GBRP ; 
 void* AV_PIX_FMT_GBRP16BE ; 
 scalar_t__ AV_PIX_FMT_GRAY16BE ; 
 scalar_t__ AV_PIX_FMT_GRAY8 ; 
 scalar_t__ AV_PIX_FMT_GRAYF32BE ; 
 scalar_t__ AV_PIX_FMT_MONOWHITE ; 
 scalar_t__ AV_PIX_FMT_PAL8 ; 
 scalar_t__ AV_PIX_FMT_YA16BE ; 
 scalar_t__ AV_PIX_FMT_YA8 ; 
 int AV_RB16 (int const*) ; 
 int /*<<< orphan*/  AV_WB16 (int*,int) ; 
 int /*<<< orphan*/  ENOMEM ; 
#define  PSD_BITMAP 133 
#define  PSD_CMYK 132 
#define  PSD_DUOTONE 131 
#define  PSD_GRAYSCALE 130 
#define  PSD_INDEXED 129 
#define  PSD_RGB 128 
 scalar_t__ PSD_RLE ; 
 int /*<<< orphan*/  av_freep (int**) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 int* av_malloc (int) ; 
 int /*<<< orphan*/  avpriv_report_missing_feature (TYPE_4__*,char*,int) ; 
 int bytestream2_get_bytes_left (TYPE_11__*) ; 
 int /*<<< orphan*/  bytestream2_init (TYPE_11__*,int /*<<< orphan*/ ,int) ; 
 int decode_header (TYPE_1__*) ; 
 int decode_rle (TYPE_1__*) ; 
 int ff_get_buffer (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 

__attribute__((used)) static int decode_frame(AVCodecContext *avctx, void *data,
                        int *got_frame, AVPacket *avpkt)
{
    int ret;
    uint8_t *ptr;
    const uint8_t *ptr_data;
    int index_out, c, y, x, p;
    uint8_t eq_channel[4] = {2,0,1,3};/* RGBA -> GBRA channel order */
    uint8_t plane_number;

    AVFrame *picture = data;

    PSDContext *s = avctx->priv_data;
    s->avctx     = avctx;
    s->channel_count = 0;
    s->channel_depth = 0;
    s->tmp           = NULL;
    s->line_size     = 0;

    bytestream2_init(&s->gb, avpkt->data, avpkt->size);

    if ((ret = decode_header(s)) < 0)
        return ret;

    s->pixel_size = s->channel_depth >> 3;/* in byte */
    s->line_size = s->width * s->pixel_size;

    switch (s->color_mode) {
    case PSD_BITMAP:
        if (s->channel_depth != 1 || s->channel_count != 1) {
            av_log(s->avctx, AV_LOG_ERROR,
                    "Invalid bitmap file (channel_depth %d, channel_count %d)\n",
                    s->channel_depth, s->channel_count);
            return AVERROR_INVALIDDATA;
        }
        s->line_size = s->width + 7 >> 3;
        avctx->pix_fmt = AV_PIX_FMT_MONOWHITE;
        break;
    case PSD_INDEXED:
        if (s->channel_depth != 8 || s->channel_count != 1) {
            av_log(s->avctx, AV_LOG_ERROR,
                   "Invalid indexed file (channel_depth %d, channel_count %d)\n",
                   s->channel_depth, s->channel_count);
            return AVERROR_INVALIDDATA;
        }
        avctx->pix_fmt = AV_PIX_FMT_PAL8;
        break;
    case PSD_CMYK:
        if (s->channel_count == 4) {
            if (s->channel_depth == 8) {
                avctx->pix_fmt = AV_PIX_FMT_GBRP;
            } else if (s->channel_depth == 16) {
                avctx->pix_fmt = AV_PIX_FMT_GBRP16BE;
            } else {
                avpriv_report_missing_feature(avctx, "channel depth %d for cmyk", s->channel_depth);
                return AVERROR_PATCHWELCOME;
            }
        } else if (s->channel_count == 5) {
            if (s->channel_depth == 8) {
                avctx->pix_fmt = AV_PIX_FMT_GBRAP;
            } else if (s->channel_depth == 16) {
                avctx->pix_fmt = AV_PIX_FMT_GBRAP16BE;
            } else {
                avpriv_report_missing_feature(avctx, "channel depth %d for cmyk", s->channel_depth);
                return AVERROR_PATCHWELCOME;
            }
        } else {
            avpriv_report_missing_feature(avctx, "channel count %d for cmyk", s->channel_count);
            return AVERROR_PATCHWELCOME;
        }
        break;
    case PSD_RGB:
        if (s->channel_count == 3) {
            if (s->channel_depth == 8) {
                avctx->pix_fmt = AV_PIX_FMT_GBRP;
            } else if (s->channel_depth == 16) {
                avctx->pix_fmt = AV_PIX_FMT_GBRP16BE;
            } else {
                avpriv_report_missing_feature(avctx, "channel depth %d for rgb", s->channel_depth);
                return AVERROR_PATCHWELCOME;
            }
        } else if (s->channel_count == 4) {
            if (s->channel_depth == 8) {
                avctx->pix_fmt = AV_PIX_FMT_GBRAP;
            } else if (s->channel_depth == 16) {
                avctx->pix_fmt = AV_PIX_FMT_GBRAP16BE;
            } else {
                avpriv_report_missing_feature(avctx, "channel depth %d for rgb", s->channel_depth);
                return AVERROR_PATCHWELCOME;
            }
        } else {
            avpriv_report_missing_feature(avctx, "channel count %d for rgb", s->channel_count);
            return AVERROR_PATCHWELCOME;
        }
        break;
    case PSD_DUOTONE:
        av_log(avctx, AV_LOG_WARNING, "ignoring unknown duotone specification.\n");
    case PSD_GRAYSCALE:
        if (s->channel_count == 1) {
            if (s->channel_depth == 8) {
                avctx->pix_fmt = AV_PIX_FMT_GRAY8;
            } else if (s->channel_depth == 16) {
                avctx->pix_fmt = AV_PIX_FMT_GRAY16BE;
            } else if (s->channel_depth == 32) {
                avctx->pix_fmt = AV_PIX_FMT_GRAYF32BE;
            } else {
                avpriv_report_missing_feature(avctx, "channel depth %d for grayscale", s->channel_depth);
                return AVERROR_PATCHWELCOME;
            }
        } else if (s->channel_count == 2) {
            if (s->channel_depth == 8) {
                avctx->pix_fmt = AV_PIX_FMT_YA8;
            } else if (s->channel_depth == 16) {
                avctx->pix_fmt = AV_PIX_FMT_YA16BE;
            } else {
                avpriv_report_missing_feature(avctx, "channel depth %d for grayscale", s->channel_depth);
                return AVERROR_PATCHWELCOME;
            }
        } else {
            avpriv_report_missing_feature(avctx, "channel count %d for grayscale", s->channel_count);
            return AVERROR_PATCHWELCOME;
        }
        break;
    default:
        avpriv_report_missing_feature(avctx, "color mode %d", s->color_mode);
        return AVERROR_PATCHWELCOME;
    }

    s->uncompressed_size = s->line_size * s->height * s->channel_count;

    if ((ret = ff_get_buffer(avctx, picture, 0)) < 0)
        return ret;

    /* decode picture if need */
    if (s->compression == PSD_RLE) {
        s->tmp = av_malloc(s->uncompressed_size);
        if (!s->tmp)
            return AVERROR(ENOMEM);

        ret = decode_rle(s);

        if (ret < 0) {
            av_freep(&s->tmp);
            return ret;
        }

        ptr_data = s->tmp;
    } else {
        if (bytestream2_get_bytes_left(&s->gb) < s->uncompressed_size) {
            av_log(s->avctx, AV_LOG_ERROR, "Not enough data for raw image data section.\n");
            return AVERROR_INVALIDDATA;
        }
        ptr_data = s->gb.buffer;
    }

    /* Store data */
    if ((avctx->pix_fmt == AV_PIX_FMT_YA8)||(avctx->pix_fmt == AV_PIX_FMT_YA16BE)){/* Interleaved */
        ptr = picture->data[0];
        for (c = 0; c < s->channel_count; c++) {
            for (y = 0; y < s->height; y++) {
                for (x = 0; x < s->width; x++) {
                    index_out = y * picture->linesize[0] + x * s->channel_count * s->pixel_size + c * s->pixel_size;
                    for (p = 0; p < s->pixel_size; p++) {
                        ptr[index_out + p] = *ptr_data;
                        ptr_data ++;
                    }
                }
            }
        }
    } else if (s->color_mode == PSD_CMYK) {
        uint8_t *dst[4] = { picture->data[0], picture->data[1], picture->data[2], picture->data[3] };
        const uint8_t *src[5] = { ptr_data };
        src[1] = src[0] + s->line_size * s->height;
        src[2] = src[1] + s->line_size * s->height;
        src[3] = src[2] + s->line_size * s->height;
        src[4] = src[3] + s->line_size * s->height;
        if (s->channel_depth == 8) {
            for (y = 0; y < s->height; y++) {
                for (x = 0; x < s->width; x++) {
                    int k = src[3][x];
                    int r = src[0][x] * k;
                    int g = src[1][x] * k;
                    int b = src[2][x] * k;
                    dst[0][x] = g * 257 >> 16;
                    dst[1][x] = b * 257 >> 16;
                    dst[2][x] = r * 257 >> 16;
                }
                dst[0] += picture->linesize[0];
                dst[1] += picture->linesize[1];
                dst[2] += picture->linesize[2];
                src[0] += s->line_size;
                src[1] += s->line_size;
                src[2] += s->line_size;
                src[3] += s->line_size;
            }
            if (avctx->pix_fmt == AV_PIX_FMT_GBRAP) {
                for (y = 0; y < s->height; y++) {
                    memcpy(dst[3], src[4], s->line_size);
                    src[4] += s->line_size;
                    dst[3] += picture->linesize[3];
                }
            }
        } else {
            for (y = 0; y < s->height; y++) {
                for (x = 0; x < s->width; x++) {
                    int64_t k = AV_RB16(&src[3][x * 2]);
                    int64_t r = AV_RB16(&src[0][x * 2]) * k;
                    int64_t g = AV_RB16(&src[1][x * 2]) * k;
                    int64_t b = AV_RB16(&src[2][x * 2]) * k;
                    AV_WB16(&dst[0][x * 2], g * 65537 >> 32);
                    AV_WB16(&dst[1][x * 2], b * 65537 >> 32);
                    AV_WB16(&dst[2][x * 2], r * 65537 >> 32);
                }
                dst[0] += picture->linesize[0];
                dst[1] += picture->linesize[1];
                dst[2] += picture->linesize[2];
                src[0] += s->line_size;
                src[1] += s->line_size;
                src[2] += s->line_size;
                src[3] += s->line_size;
            }
            if (avctx->pix_fmt == AV_PIX_FMT_GBRAP16BE) {
                for (y = 0; y < s->height; y++) {
                    memcpy(dst[3], src[4], s->line_size);
                    src[4] += s->line_size;
                    dst[3] += picture->linesize[3];
                }
            }
        }
    } else {/* Planar */
        if (s->channel_count == 1)/* gray 8 or gray 16be */
            eq_channel[0] = 0;/* assign first channel, to first plane */

        for (c = 0; c < s->channel_count; c++) {
            plane_number = eq_channel[c];
            ptr = picture->data[plane_number];/* get the right plane */
            for (y = 0; y < s->height; y++) {
                memcpy(ptr, ptr_data, s->line_size);
                ptr += picture->linesize[plane_number];
                ptr_data += s->line_size;
            }
        }
    }

    if (s->color_mode == PSD_INDEXED) {
        picture->palette_has_changed = 1;
        memcpy(picture->data[1], s->palette, AVPALETTE_SIZE);
    }

    av_freep(&s->tmp);

    picture->pict_type = AV_PICTURE_TYPE_I;
    *got_frame = 1;

    return avpkt->size;
}