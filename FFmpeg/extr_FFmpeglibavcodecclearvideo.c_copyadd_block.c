#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_7__ {int coded_width; int coded_height; } ;
struct TYPE_6__ {int* linesize; int** data; } ;
typedef  TYPE_1__ AVFrame ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int av_clip_uint8 (int) ; 

__attribute__((used)) static int copyadd_block(AVCodecContext *avctx, AVFrame *dst, AVFrame *src,
                         int plane, int x, int y, int dx, int dy, int size, int bias)
{
    int shift = plane > 0;
    int sx = x + dx;
    int sy = y + dy;
    int sstride   = src->linesize[plane];
    int dstride   = dst->linesize[plane];
    int soff      = sx + sy * sstride;
    uint8_t *sbuf = src->data[plane];
    int doff      = x + y * dstride;
    uint8_t *dbuf = dst->data[plane];
    int i, j;

    if (x < 0 || sx < 0 || y < 0 || sy < 0 ||
        x + size > avctx->coded_width >> shift ||
        y + size > avctx->coded_height >> shift ||
        sx + size > avctx->coded_width >> shift ||
        sy + size > avctx->coded_height >> shift)
        return AVERROR_INVALIDDATA;

    for (j = 0; j < size; j++) {
        uint8_t *dptr = &dbuf[doff];
        uint8_t *sptr = &sbuf[soff];

        for (i = 0; i < size; i++) {
            int val = sptr[i] + bias;

            dptr[i] = av_clip_uint8(val);
        }

        doff += dstride;
        soff += sstride;
    }

    return 0;
}