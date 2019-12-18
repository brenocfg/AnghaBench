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

__attribute__((used)) static int decode_run_i(AVCodecContext *avctx, uint32_t ptype, int run,
                        int *px, int *py, uint32_t clr, uint32_t *dst,
                        int linesize, uint32_t *plx, uint32_t *ply,
                        uint32_t backstep, int off, int *cx, int *cx1)
{
    uint32_t r, g, b;
    int z;
    int x = *px,
        y = *py;
    uint32_t lx = *plx,
             ly = *ply;

    if (y >= avctx->height)
        return AVERROR_INVALIDDATA;

    switch (ptype) {
    case 0:
        while (run-- > 0) {
            dst[y * linesize + x] = clr;
            lx = x;
            ly = y;
            (x)++;
            if (x >= avctx->width) {
                x = 0;
                (y)++;
                if (y >= avctx->height && run)
                    return AVERROR_INVALIDDATA;
            }
        }
        break;
    case 1:
        while (run-- > 0) {
            dst[y * linesize + x] = dst[ly * linesize + lx];
            lx = x;
            ly = y;
            (x)++;
            if (x >= avctx->width) {
                x = 0;
                (y)++;
                if (y >= avctx->height && run)
                    return AVERROR_INVALIDDATA;
            }
        }
        clr = dst[ly * linesize + lx];
        break;
    case 2:
        if (y < 1)
            return AVERROR_INVALIDDATA;

        while (run-- > 0) {
            clr = dst[y * linesize + x + off + 1];
            dst[y * linesize + x] = clr;
            lx = x;
            ly = y;
            (x)++;
            if (x >= avctx->width) {
                x = 0;
                (y)++;
                if (y >= avctx->height && run)
                    return AVERROR_INVALIDDATA;
            }
        }
        break;
    case 4:
        if (y < 1 || (y == 1 && x == 0))
            return AVERROR_INVALIDDATA;

        while (run-- > 0) {
            uint8_t *odst = (uint8_t *)dst;
            int off1 = (ly * linesize + lx) * 4;
            int off2 = ((y * linesize + x) + off) * 4;

            if (x == 0) {
                z = backstep * 4;
            } else {
                z = 0;
            }

            r = odst[off1] +
                odst[off2 + 4] -
                odst[off2 - z ];
            g = odst[off1 + 1] +
                odst[off2 + 5] -
                odst[off2 - z  + 1];
            b = odst[off1 + 2] +
                odst[off2 + 6] -
                odst[off2 - z  + 2];
            clr = ((b & 0xFF) << 16) + ((g & 0xFF) << 8) + (r & 0xFF);
            dst[y * linesize + x] = clr;
            lx = x;
            ly = y;
            (x)++;
            if (x >= avctx->width) {
                x = 0;
                (y)++;
                if (y >= avctx->height && run)
                    return AVERROR_INVALIDDATA;
            }
        }
        break;
    case 5:
        if (y < 1 || (y == 1 && x == 0))
            return AVERROR_INVALIDDATA;

        while (run-- > 0) {
            if (x == 0) {
                z = backstep;
            } else {
                z = 0;
            }

            clr = dst[y * linesize + x + off - z];
            dst[y * linesize + x] = clr;
            lx = x;
            ly = y;
            (x)++;
            if (x >= avctx->width) {
                x = 0;
                (y)++;
                if (y >= avctx->height && run)
                    return AVERROR_INVALIDDATA;
            }
        }
        break;
    }

    *px = x;
    *py = y;
    *plx= lx;
    *ply= ly;

    if (avctx->bits_per_coded_sample == 16) {
        *cx1 = (clr & 0x3F00) >> 2;
        *cx = (clr & 0x3FFFFF) >> 16;
    } else {
        *cx1 = (clr & 0xFC00) >> 4;
        *cx = (clr & 0xFFFFFF) >> 18;
    }

    return 0;
}