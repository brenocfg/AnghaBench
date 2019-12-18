#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_16__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int int8_t ;
struct TYPE_23__ {int width; int bpp; int bppcount; int* subsampling; int* yuv_line; int yuv_line_size; int compr; int* deinvert_buf; scalar_t__ tiff_type; int strips; scalar_t__ fill_order; TYPE_16__* avctx; scalar_t__ is_bayer; int /*<<< orphan*/  gb; int /*<<< orphan*/  lzw; scalar_t__ planar; } ;
typedef  TYPE_1__ TiffContext ;
struct TYPE_25__ {scalar_t__ format; } ;
struct TYPE_24__ {int flags; int nb_components; } ;
struct TYPE_22__ {scalar_t__ pix_fmt; } ;
typedef  int /*<<< orphan*/  PutByteContext ;
typedef  TYPE_2__ AVPixFmtDescriptor ;
typedef  TYPE_3__ AVFrame ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_PIX_FMT_FLAG_PLANAR ; 
 int AV_PIX_FMT_FLAG_RGB ; 
 scalar_t__ AV_PIX_FMT_GRAY12 ; 
 scalar_t__ AV_PIX_FMT_PAL8 ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  FF_LZW_TIFF ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int TIFF_ADOBE_DEFLATE ; 
 int TIFF_CCITT_RLE ; 
 int TIFF_DEFLATE ; 
 int TIFF_G3 ; 
 int TIFF_G4 ; 
 int TIFF_LZMA ; 
 int TIFF_LZW ; 
 int TIFF_NEWJPEG ; 
#define  TIFF_PACKBITS 129 
#define  TIFF_RAW 128 
 scalar_t__ TIFF_TYPE_CINEMADNG ; 
 scalar_t__ TIFF_TYPE_DNG ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_fast_padded_malloc (int**,int*,int) ; 
 int /*<<< orphan*/  av_log (TYPE_16__*,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__* av_pix_fmt_desc_get (scalar_t__) ; 
 scalar_t__ bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 scalar_t__ bytestream2_get_eof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_init (int /*<<< orphan*/ *,int const*,int) ; 
 int /*<<< orphan*/  bytestream2_init_writer (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  bytestream2_seek_p (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int deinvert_buffer (TYPE_1__*,int const*,int) ; 
 int /*<<< orphan*/  dng_blit (TYPE_1__*,int*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 
 int dng_decode_strip (TYPE_16__*,TYPE_3__*) ; 
 int ff_lzw_decode (int /*<<< orphan*/ ,int*,int) ; 
 int ff_lzw_decode_init (int /*<<< orphan*/ ,int,int const*,int,int /*<<< orphan*/ ) ; 
 int* ff_reverse ; 
 int /*<<< orphan*/  horizontal_fill (TYPE_1__*,int,int*,int,int const*,int,int,int) ; 
 int tiff_unpack_fax (TYPE_1__*,int*,int,int const*,int,int,int) ; 
 int tiff_unpack_lzma (TYPE_1__*,TYPE_3__*,int*,int,int const*,int,int,int,int,int) ; 
 int tiff_unpack_zlib (TYPE_1__*,TYPE_3__*,int*,int,int const*,int,int,int,int,int) ; 
 int /*<<< orphan*/  unpack_gray (TYPE_1__*,TYPE_3__*,int*,int,int,int) ; 
 int /*<<< orphan*/  unpack_yuv (TYPE_1__*,TYPE_3__*,int*,int) ; 

__attribute__((used)) static int tiff_unpack_strip(TiffContext *s, AVFrame *p, uint8_t *dst, int stride,
                             const uint8_t *src, int size, int strip_start, int lines)
{
    PutByteContext pb;
    int c, line, pixels, code, ret;
    const uint8_t *ssrc = src;
    int width = ((s->width * s->bpp) + 7) >> 3;
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(p->format);
    int is_yuv = !(desc->flags & AV_PIX_FMT_FLAG_RGB) &&
                 (desc->flags & AV_PIX_FMT_FLAG_PLANAR) &&
                 desc->nb_components >= 3;
    int is_dng;

    if (s->planar)
        width /= s->bppcount;

    if (size <= 0)
        return AVERROR_INVALIDDATA;

    if (is_yuv) {
        int bytes_per_row = (((s->width - 1) / s->subsampling[0] + 1) * s->bpp *
                            s->subsampling[0] * s->subsampling[1] + 7) >> 3;
        av_fast_padded_malloc(&s->yuv_line, &s->yuv_line_size, bytes_per_row);
        if (s->yuv_line == NULL) {
            av_log(s->avctx, AV_LOG_ERROR, "Not enough memory\n");
            return AVERROR(ENOMEM);
        }
        dst = s->yuv_line;
        stride = 0;

        width = (s->width - 1) / s->subsampling[0] + 1;
        width = width * s->subsampling[0] * s->subsampling[1] + 2*width;
        av_assert0(width <= bytes_per_row);
        av_assert0(s->bpp == 24);
    }
    if (s->is_bayer) {
        width = (s->bpp * s->width + 7) >> 3;
    }
    if (p->format == AV_PIX_FMT_GRAY12) {
        av_fast_padded_malloc(&s->yuv_line, &s->yuv_line_size, width);
        if (s->yuv_line == NULL) {
            av_log(s->avctx, AV_LOG_ERROR, "Not enough memory\n");
            return AVERROR(ENOMEM);
        }
        dst = s->yuv_line;
        stride = 0;
    }

    if (s->compr == TIFF_DEFLATE || s->compr == TIFF_ADOBE_DEFLATE) {
#if CONFIG_ZLIB
        return tiff_unpack_zlib(s, p, dst, stride, src, size, width, lines,
                                strip_start, is_yuv);
#else
        av_log(s->avctx, AV_LOG_ERROR,
               "zlib support not enabled, "
               "deflate compression not supported\n");
        return AVERROR(ENOSYS);
#endif
    }
    if (s->compr == TIFF_LZMA) {
#if CONFIG_LZMA
        return tiff_unpack_lzma(s, p, dst, stride, src, size, width, lines,
                                strip_start, is_yuv);
#else
        av_log(s->avctx, AV_LOG_ERROR,
               "LZMA support not enabled\n");
        return AVERROR(ENOSYS);
#endif
    }
    if (s->compr == TIFF_LZW) {
        if (s->fill_order) {
            if ((ret = deinvert_buffer(s, src, size)) < 0)
                return ret;
            ssrc = src = s->deinvert_buf;
        }
        if (size > 1 && !src[0] && (src[1]&1)) {
            av_log(s->avctx, AV_LOG_ERROR, "Old style LZW is unsupported\n");
        }
        if ((ret = ff_lzw_decode_init(s->lzw, 8, src, size, FF_LZW_TIFF)) < 0) {
            av_log(s->avctx, AV_LOG_ERROR, "Error initializing LZW decoder\n");
            return ret;
        }
        for (line = 0; line < lines; line++) {
            pixels = ff_lzw_decode(s->lzw, dst, width);
            if (pixels < width) {
                av_log(s->avctx, AV_LOG_ERROR, "Decoded only %i bytes of %i\n",
                       pixels, width);
                return AVERROR_INVALIDDATA;
            }
            if (s->bpp < 8 && s->avctx->pix_fmt == AV_PIX_FMT_PAL8)
                horizontal_fill(s, s->bpp, dst, 1, dst, 0, width, 0);
            if (is_yuv) {
                unpack_yuv(s, p, dst, strip_start + line);
                line += s->subsampling[1] - 1;
            } else if (p->format == AV_PIX_FMT_GRAY12) {
                unpack_gray(s, p, dst, strip_start + line, width, s->bpp);
            }
            dst += stride;
        }
        return 0;
    }
    if (s->compr == TIFF_CCITT_RLE ||
        s->compr == TIFF_G3        ||
        s->compr == TIFF_G4) {
        if (is_yuv || p->format == AV_PIX_FMT_GRAY12)
            return AVERROR_INVALIDDATA;

        return tiff_unpack_fax(s, dst, stride, src, size, width, lines);
    }

    bytestream2_init(&s->gb, src, size);
    bytestream2_init_writer(&pb, dst, is_yuv ? s->yuv_line_size : (stride * lines));

    is_dng = (s->tiff_type == TIFF_TYPE_DNG || s->tiff_type == TIFF_TYPE_CINEMADNG);

    /* Decode JPEG-encoded DNGs with strips */
    if (s->compr == TIFF_NEWJPEG && is_dng) {
        if (s->strips > 1) {
            av_log(s->avctx, AV_LOG_ERROR, "More than one DNG JPEG strips unsupported\n");
            return AVERROR_PATCHWELCOME;
        }
        if ((ret = dng_decode_strip(s->avctx, p)) < 0)
            return ret;
        return 0;
    }

    for (line = 0; line < lines; line++) {
        if (src - ssrc > size) {
            av_log(s->avctx, AV_LOG_ERROR, "Source data overread\n");
            return AVERROR_INVALIDDATA;
        }

        if (bytestream2_get_bytes_left(&s->gb) == 0 || bytestream2_get_eof(&pb))
            break;
        bytestream2_seek_p(&pb, stride * line, SEEK_SET);
        switch (s->compr) {
        case TIFF_RAW:
            if (ssrc + size - src < width)
                return AVERROR_INVALIDDATA;

            if (!s->fill_order) {
                horizontal_fill(s, s->bpp * (s->avctx->pix_fmt == AV_PIX_FMT_PAL8 || s->is_bayer),
                                dst, 1, src, 0, width, 0);
            } else {
                int i;
                for (i = 0; i < width; i++)
                    dst[i] = ff_reverse[src[i]];
            }

            /* Color processing for DNG images with uncompressed strips (non-tiled) */
            if (is_dng) {
                int is_u16, pixel_size_bytes, pixel_size_bits;

                is_u16 = (s->bpp > 8);
                pixel_size_bits = (is_u16 ? 16 : 8);
                pixel_size_bytes = (is_u16 ? sizeof(uint16_t) : sizeof(uint8_t));

                dng_blit(s,
                         dst,
                         0, // no stride, only 1 line
                         dst,
                         0, // no stride, only 1 line
                         width / pixel_size_bytes * pixel_size_bits / s->bpp * s->bppcount, // need to account for [1, 16] bpp
                         1,
                         0, // single-component variation is only preset in JPEG-encoded DNGs
                         is_u16);
            }

            src += width;
            break;
        case TIFF_PACKBITS:
            for (pixels = 0; pixels < width;) {
                if (ssrc + size - src < 2) {
                    av_log(s->avctx, AV_LOG_ERROR, "Read went out of bounds\n");
                    return AVERROR_INVALIDDATA;
                }
                code = s->fill_order ? (int8_t) ff_reverse[*src++]: (int8_t) *src++;
                if (code >= 0) {
                    code++;
                    if (pixels + code > width ||
                        ssrc + size - src < code) {
                        av_log(s->avctx, AV_LOG_ERROR,
                               "Copy went out of bounds\n");
                        return AVERROR_INVALIDDATA;
                    }
                    horizontal_fill(s, s->bpp * (s->avctx->pix_fmt == AV_PIX_FMT_PAL8),
                                    dst, 1, src, 0, code, pixels);
                    src    += code;
                    pixels += code;
                } else if (code != -128) { // -127..-1
                    code = (-code) + 1;
                    if (pixels + code > width) {
                        av_log(s->avctx, AV_LOG_ERROR,
                               "Run went out of bounds\n");
                        return AVERROR_INVALIDDATA;
                    }
                    c = *src++;
                    horizontal_fill(s, s->bpp * (s->avctx->pix_fmt == AV_PIX_FMT_PAL8),
                                    dst, 0, NULL, c, code, pixels);
                    pixels += code;
                }
            }
            if (s->fill_order) {
                int i;
                for (i = 0; i < width; i++)
                    dst[i] = ff_reverse[dst[i]];
            }
            break;
        }
        if (is_yuv) {
            unpack_yuv(s, p, dst, strip_start + line);
            line += s->subsampling[1] - 1;
        } else if (p->format == AV_PIX_FMT_GRAY12) {
            unpack_gray(s, p, dst, strip_start + line, width, s->bpp);
        }
        dst += stride;
    }
    return 0;
}