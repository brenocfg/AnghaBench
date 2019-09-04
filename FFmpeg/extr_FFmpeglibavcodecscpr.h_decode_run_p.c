#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_3__ {int height; int width; int bits_per_coded_sample; } ;
typedef  TYPE_1__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 

__attribute__((used)) static int decode_run_p(AVCodecContext *avctx, uint32_t ptype, int run,
                        int x, int y, uint32_t clr,
                        uint32_t *dst, uint32_t *prev,
                        int linesize, int plinesize,
                        uint32_t *bx, uint32_t *by,
                        uint32_t backstep, int sx1, int sx2,
                        int *cx, int *cx1)
{
    uint32_t r, g, b;
    int z;

    switch (ptype) {
    case 0:
        while (run-- > 0) {
            if (*by >= avctx->height)
                return AVERROR_INVALIDDATA;

            dst[*by * linesize + *bx] = clr;
            (*bx)++;
            if (*bx >= x * 16 + sx2 || *bx >= avctx->width) {
                *bx = x * 16 + sx1;
                (*by)++;
            }
        }
        break;
    case 1:
        while (run-- > 0) {
            if (*bx == 0) {
                if (*by < 1)
                    return AVERROR_INVALIDDATA;
                z = backstep;
            } else {
                z = 0;
            }

            if (*by >= avctx->height)
                return AVERROR_INVALIDDATA;

            clr = dst[*by * linesize + *bx - 1 - z];
            dst[*by * linesize + *bx] = clr;
            (*bx)++;
            if (*bx >= x * 16 + sx2 || *bx >= avctx->width) {
                *bx = x * 16 + sx1;
                (*by)++;
            }
        }
        break;
    case 2:
        while (run-- > 0) {
            if (*by < 1 || *by >= avctx->height)
                return AVERROR_INVALIDDATA;

            clr = dst[(*by - 1) * linesize + *bx];
            dst[*by * linesize + *bx] = clr;
            (*bx)++;
            if (*bx >= x * 16 + sx2 || *bx >= avctx->width) {
                *bx = x * 16 + sx1;
                (*by)++;
            }
        }
        break;
    case 3:
        while (run-- > 0) {
            if (*by >= avctx->height)
                return AVERROR_INVALIDDATA;

            clr = prev[*by * plinesize + *bx];
            dst[*by * linesize + *bx] = clr;
            (*bx)++;
            if (*bx >= x * 16 + sx2 || *bx >= avctx->width) {
                *bx = x * 16 + sx1;
                (*by)++;
            }
        }
        break;
    case 4:
        while (run-- > 0) {
            uint8_t *odst = (uint8_t *)dst;

            if (*by < 1 || *by >= avctx->height)
                return AVERROR_INVALIDDATA;

            if (*bx == 0) {
                if (*by < 2)
                    return AVERROR_INVALIDDATA;
                z = backstep;
            } else {
                z = 0;
            }

            r = odst[((*by - 1) * linesize + *bx) * 4] +
                odst[(*by * linesize + *bx - 1 - z) * 4] -
                odst[((*by - 1) * linesize + *bx - 1 - z) * 4];
            g = odst[((*by - 1) * linesize + *bx) * 4 + 1] +
                odst[(*by * linesize + *bx - 1 - z) * 4 + 1] -
                odst[((*by - 1) * linesize + *bx - 1 - z) * 4 + 1];
            b = odst[((*by - 1) * linesize + *bx) * 4 + 2] +
                odst[(*by * linesize + *bx - 1 - z) * 4 + 2] -
                odst[((*by - 1) * linesize + *bx - 1 - z) * 4 + 2];
            clr = ((b & 0xFF) << 16) + ((g & 0xFF) << 8) + (r & 0xFF);
            dst[*by * linesize + *bx] = clr;
            (*bx)++;
            if (*bx >= x * 16 + sx2 || *bx >= avctx->width) {
                *bx = x * 16 + sx1;
                (*by)++;
            }
        }
        break;
    case 5:
        while (run-- > 0) {
            if (*by < 1 || *by >= avctx->height)
                return AVERROR_INVALIDDATA;

            if (*bx == 0) {
                if (*by < 2)
                    return AVERROR_INVALIDDATA;
                z = backstep;
            } else {
                z = 0;
            }

            clr = dst[(*by - 1) * linesize + *bx - 1 - z];
            dst[*by * linesize + *bx] = clr;
            (*bx)++;
            if (*bx >= x * 16 + sx2 || *bx >= avctx->width) {
                *bx = x * 16 + sx1;
                (*by)++;
            }
        }
        break;
    }

    if (avctx->bits_per_coded_sample == 16) {
        *cx1 = (clr & 0x3F00) >> 2;
        *cx = (clr & 0x3FFFFF) >> 16;
    } else {
        *cx1 = (clr & 0xFC00) >> 4;
        *cx = (clr & 0xFFFFFF) >> 18;
    }

    return 0;
}