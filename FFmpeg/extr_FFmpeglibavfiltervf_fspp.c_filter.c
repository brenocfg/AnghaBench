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
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_3__ {int temp_stride; int log2_count; int hsub; int vsub; int* src; int prev_q; int /*<<< orphan*/ * temp; int /*<<< orphan*/  (* store_slice2 ) (int*,int /*<<< orphan*/ *,int,int const,int,int,int) ;int /*<<< orphan*/  (* store_slice ) (int*,int /*<<< orphan*/ *,int,int const,int,int,int) ;int /*<<< orphan*/  (* row_idct ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int const,int) ;int /*<<< orphan*/ * threshold_mtx; int /*<<< orphan*/  (* column_fidct ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  (* row_fdct ) (int /*<<< orphan*/ *,int*,int const,int) ;int /*<<< orphan*/ * threshold_mtx_noq; int /*<<< orphan*/  (* mul_thrmat ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  qscale_type; scalar_t__ qp; } ;
typedef  TYPE_1__ FSPPContext ;

/* Variables and functions */
 int BLOCKSZ ; 
 int /*<<< orphan*/ * DECLARE_ALIGNED (int,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ block_align ; 
 int ff_norm_qscale (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int32_t ; 
 int /*<<< orphan*/  memcpy (int*,int*,int const) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int*,int const,int) ; 
 int /*<<< orphan*/  stub10 (int*,int /*<<< orphan*/ *,int,int const,int,int,int) ; 
 int /*<<< orphan*/  stub11 (int*,int /*<<< orphan*/ *,int,int const,int,int,int) ; 
 int /*<<< orphan*/  stub12 (int*,int /*<<< orphan*/ *,int,int const,int,int,int) ; 
 int /*<<< orphan*/  stub13 (int*,int /*<<< orphan*/ *,int,int const,int,int,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int*,int const,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int const,int) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ *,int*,int const,int) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub9 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int const,int) ; 

__attribute__((used)) static void filter(FSPPContext *p, uint8_t *dst, uint8_t *src,
                   int dst_stride, int src_stride,
                   int width, int height,
                   uint8_t *qp_store, int qp_stride, int is_luma)
{
    int x, x0, y, es, qy, t;

    const int stride = is_luma ? p->temp_stride : (width + 16);
    const int step = 6 - p->log2_count;
    const int qpsh = 4 - p->hsub * !is_luma;
    const int qpsv = 4 - p->vsub * !is_luma;

    DECLARE_ALIGNED(32, int32_t, block_align)[4 * 8 * BLOCKSZ + 4 * 8 * BLOCKSZ];
    int16_t *block  = (int16_t *)block_align;
    int16_t *block3 = (int16_t *)(block_align + 4 * 8 * BLOCKSZ);

    memset(block3, 0, 4 * 8 * BLOCKSZ);

    if (!src || !dst) return;

    for (y = 0; y < height; y++) {
        int index = 8 + 8 * stride + y * stride;
        memcpy(p->src + index, src + y * src_stride, width);
        for (x = 0; x < 8; x++) {
            p->src[index         - x - 1] = p->src[index +         x    ];
            p->src[index + width + x    ] = p->src[index + width - x - 1];
        }
    }

    for (y = 0; y < 8; y++) {
        memcpy(p->src + (     7 - y    ) * stride, p->src + (     y + 8    ) * stride, stride);
        memcpy(p->src + (height + 8 + y) * stride, p->src + (height - y + 7) * stride, stride);
    }
    //FIXME (try edge emu)

    for (y = 8; y < 24; y++)
        memset(p->temp + 8 + y * stride, 0, width * sizeof(int16_t));

    for (y = step; y < height + 8; y += step) {    //step= 1,2
        const int y1 = y - 8 + step;                 //l5-7  l4-6;
        qy = y - 4;

        if (qy > height - 1) qy = height - 1;
        if (qy < 0) qy = 0;

        qy = (qy >> qpsv) * qp_stride;
        p->row_fdct(block, p->src + y * stride + 2 - (y&1), stride, 2);

        for (x0 = 0; x0 < width + 8 - 8 * (BLOCKSZ - 1); x0 += 8 * (BLOCKSZ - 1)) {
            p->row_fdct(block + 8 * 8, p->src + y * stride + 8 + x0 + 2 - (y&1), stride, 2 * (BLOCKSZ - 1));

            if (p->qp)
                p->column_fidct((int16_t *)(&p->threshold_mtx[0]), block + 0 * 8, block3 + 0 * 8, 8 * (BLOCKSZ - 1)); //yes, this is a HOTSPOT
            else
                for (x = 0; x < 8 * (BLOCKSZ - 1); x += 8) {
                    t = x + x0 - 2;                    //correct t=x+x0-2-(y&1), but its the same

                    if (t < 0) t = 0;                   //t always < width-2

                    t = qp_store[qy + (t >> qpsh)];
                    t = ff_norm_qscale(t, p->qscale_type);

                    if (t != p->prev_q) p->prev_q = t, p->mul_thrmat((int16_t *)(&p->threshold_mtx_noq[0]), (int16_t *)(&p->threshold_mtx[0]), t);
                    p->column_fidct((int16_t *)(&p->threshold_mtx[0]), block + x * 8, block3 + x * 8, 8); //yes, this is a HOTSPOT
                }
            p->row_idct(block3 + 0 * 8, p->temp + (y & 15) * stride + x0 + 2 - (y & 1), stride, 2 * (BLOCKSZ - 1));
            memmove(block,  block  + (BLOCKSZ - 1) * 64, 8 * 8 * sizeof(int16_t)); //cycling
            memmove(block3, block3 + (BLOCKSZ - 1) * 64, 6 * 8 * sizeof(int16_t));
        }

        es = width + 8 - x0; //  8, ...
        if (es > 8)
            p->row_fdct(block + 8 * 8, p->src + y * stride + 8 + x0 + 2 - (y & 1), stride, (es - 4) >> 2);

        p->column_fidct((int16_t *)(&p->threshold_mtx[0]), block, block3, es&(~1));
        if (es > 3)
            p->row_idct(block3 + 0 * 8, p->temp + (y & 15) * stride + x0 + 2 - (y & 1), stride, es >> 2);

        if (!(y1 & 7) && y1) {
            if (y1 & 8)
                p->store_slice(dst + (y1 - 8) * dst_stride, p->temp + 8 + 8 * stride,
                               dst_stride, stride, width, 8, 5 - p->log2_count);
            else
                p->store_slice2(dst + (y1 - 8) * dst_stride, p->temp + 8 + 0 * stride,
                                dst_stride, stride, width, 8, 5 - p->log2_count);
        }
    }

    if (y & 7) {  // height % 8 != 0
        if (y & 8)
            p->store_slice(dst + ((y - 8) & ~7) * dst_stride, p->temp + 8 + 8 * stride,
                           dst_stride, stride, width, y&7, 5 - p->log2_count);
        else
            p->store_slice2(dst + ((y - 8) & ~7) * dst_stride, p->temp + 8 + 0 * stride,
                            dst_stride, stride, width, y&7, 5 - p->log2_count);
    }
}