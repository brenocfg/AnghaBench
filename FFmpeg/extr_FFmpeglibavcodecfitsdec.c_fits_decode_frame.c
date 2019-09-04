#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int int64_t ;
typedef  int int32_t ;
typedef  int int16_t ;
struct TYPE_18__ {int height; int width; int /*<<< orphan*/  pix_fmt; TYPE_2__* priv_data; } ;
struct TYPE_17__ {int* data; int* linesize; int key_frame; int /*<<< orphan*/  pict_type; int /*<<< orphan*/ * metadata; } ;
struct TYPE_16__ {int* data; int size; } ;
struct TYPE_15__ {int blank_val; } ;
struct TYPE_14__ {int bitpix; int* naxisn; int blank; int bscale; int bzero; int data_min; int data_max; int /*<<< orphan*/  blank_found; scalar_t__ rgb; } ;
typedef  TYPE_1__ FITSHeader ;
typedef  TYPE_2__ FITSContext ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
 int /*<<< orphan*/  AV_PIX_FMT_GBRAP ; 
 int /*<<< orphan*/  AV_PIX_FMT_GBRAP16 ; 
 int /*<<< orphan*/  AV_PIX_FMT_GBRP ; 
 int /*<<< orphan*/  AV_PIX_FMT_GBRP16 ; 
 int /*<<< orphan*/  AV_PIX_FMT_GRAY16 ; 
 int /*<<< orphan*/  AV_PIX_FMT_GRAY8 ; 
 int AV_RB16 (int const*) ; 
 int AV_RB32 (int const*) ; 
 int AV_RB64 (int const*) ; 
 int abs (int) ; 
 double av_int2double (int) ; 
 float av_int2float (int) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,int) ; 
 int ff_get_buffer (TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int ff_set_dimensions (TYPE_5__*,int,int) ; 
 int fits_read_header (TYPE_5__*,int const**,TYPE_1__*,int const*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int fits_decode_frame(AVCodecContext *avctx, void *data, int *got_frame, AVPacket *avpkt)
{
    AVFrame *p=data;
    const uint8_t *ptr8 = avpkt->data, *end;
    uint8_t t8;
    int16_t t16;
    int32_t t32;
    int64_t t64;
    float   tflt;
    double  tdbl;
    int ret, i, j, k;
    const int map[] = {2, 0, 1, 3}; // mapping from GBRA -> RGBA as RGBA is to be stored in FITS file..
    uint8_t *dst8;
    uint16_t *dst16;
    uint64_t t;
    FITSHeader header;
    FITSContext * fitsctx = avctx->priv_data;

    end = ptr8 + avpkt->size;
    p->metadata = NULL;
    ret = fits_read_header(avctx, &ptr8, &header, end, &p->metadata);
    if (ret < 0)
        return ret;

    if (header.rgb) {
        if (header.bitpix == 8) {
            if (header.naxisn[2] == 3) {
                avctx->pix_fmt = AV_PIX_FMT_GBRP;
            } else {
                avctx->pix_fmt = AV_PIX_FMT_GBRAP;
            }
        } else if (header.bitpix == 16) {
            if (header.naxisn[2] == 3) {
                avctx->pix_fmt = AV_PIX_FMT_GBRP16;
            } else {
                avctx->pix_fmt = AV_PIX_FMT_GBRAP16;
            }
        } else {
            av_log(avctx, AV_LOG_ERROR, "unsupported BITPIX = %d\n", header.bitpix);
            return AVERROR_INVALIDDATA;
        }
    } else {
        if (header.bitpix == 8) {
            avctx->pix_fmt = AV_PIX_FMT_GRAY8;
        } else {
            avctx->pix_fmt = AV_PIX_FMT_GRAY16;
        }
    }

    if ((ret = ff_set_dimensions(avctx, header.naxisn[0], header.naxisn[1])) < 0)
        return ret;

    if ((ret = ff_get_buffer(avctx, p, 0)) < 0)
        return ret;

    /*
     * FITS stores images with bottom row first. Therefore we have
     * to fill the image from bottom to top.
     */
    if (header.rgb) {
        switch(header.bitpix) {
#define CASE_RGB(cas, dst, type, dref) \
    case cas: \
        for (k = 0; k < header.naxisn[2]; k++) { \
            for (i = 0; i < avctx->height; i++) { \
                dst = (type *) (p->data[map[k]] + (avctx->height - i - 1) * p->linesize[map[k]]); \
                for (j = 0; j < avctx->width; j++) { \
                    t32 = dref(ptr8); \
                    if (!header.blank_found || t32 != header.blank) { \
                        t = t32 * header.bscale + header.bzero; \
                    } else { \
                        t = fitsctx->blank_val; \
                    } \
                    *dst++ = (type) t; \
                    ptr8 += cas >> 3; \
                } \
            } \
        } \
        break

            CASE_RGB(8, dst8, uint8_t, *);
            CASE_RGB(16, dst16, uint16_t, AV_RB16);
        }
    } else {
        switch (header.bitpix) {
#define CASE_GRAY(cas, dst, type, t, rd) \
    case cas: \
        for (i = 0; i < avctx->height; i++) { \
            dst = (type *) (p->data[0] + (avctx->height-i-1)* p->linesize[0]); \
            for (j = 0; j < avctx->width; j++) { \
                t = rd; \
                if (!header.blank_found || t != header.blank) { \
                    *dst++ = ((t - header.data_min) * ((1 << (sizeof(type) * 8)) - 1)) / (header.data_max - header.data_min); \
                } else { \
                    *dst++ = fitsctx->blank_val; \
                } \
                ptr8 += abs(cas) >> 3; \
            } \
        } \
        break

            CASE_GRAY(-64, dst16, uint16_t, tdbl, av_int2double(AV_RB64(ptr8)));
            CASE_GRAY(-32, dst16, uint16_t, tflt, av_int2float(AV_RB32(ptr8)));
            CASE_GRAY(8, dst8, uint8_t, t8, ptr8[0]);
            CASE_GRAY(16, dst16, uint16_t, t16, AV_RB16(ptr8));
            CASE_GRAY(32, dst16, uint16_t, t32, AV_RB32(ptr8));
            CASE_GRAY(64, dst16, uint16_t, t64, AV_RB64(ptr8));
            default:
                av_log(avctx, AV_LOG_ERROR, "invalid BITPIX, %d\n", header.bitpix);
                return AVERROR_INVALIDDATA;
        }
    }

    p->key_frame = 1;
    p->pict_type = AV_PICTURE_TYPE_I;

    *got_frame = 1;

    return avpkt->size;
}