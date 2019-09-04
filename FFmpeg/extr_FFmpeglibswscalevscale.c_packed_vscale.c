#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  (* yuv2packed2_fn ) (TYPE_5__*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int,int,int,int) ;
typedef  int /*<<< orphan*/  (* yuv2packed1_fn ) (TYPE_5__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int,int,int) ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_22__ {int filter_size; int** filter; int /*<<< orphan*/  (* yuv2packedX ) (TYPE_5__*,int*,int /*<<< orphan*/  const**,int,int*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int,int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int,int) ;scalar_t__ pfn; int /*<<< orphan*/ * filter_pos; } ;
typedef  TYPE_7__ VScalerContext ;
struct TYPE_23__ {scalar_t__ alpha; TYPE_4__* dst; TYPE_2__* src; TYPE_7__* instance; } ;
struct TYPE_21__ {int* lumMmxFilter; int* chrMmxFilter; int warned_unuseable_bilinear; scalar_t__ yuv2packed2; scalar_t__ yuv2packed1; } ;
struct TYPE_20__ {int width; int v_chr_sub_sample; TYPE_3__* plane; } ;
struct TYPE_19__ {int sliceY; int /*<<< orphan*/ ** line; } ;
struct TYPE_18__ {TYPE_1__* plane; } ;
struct TYPE_17__ {int sliceY; int /*<<< orphan*/ ** line; } ;
typedef  TYPE_8__ SwsFilterDescriptor ;
typedef  TYPE_5__ SwsContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int FFMAX (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_5__*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  stub4 (TYPE_5__*,int*,int /*<<< orphan*/  const**,int,int*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int,int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int packed_vscale(SwsContext *c, SwsFilterDescriptor *desc, int sliceY, int sliceH)
{
    VScalerContext *inst = desc->instance;
    int dstW = desc->dst->width;
    int chrSliceY = sliceY >> desc->dst->v_chr_sub_sample;

    int lum_fsize = inst[0].filter_size;
    int chr_fsize = inst[1].filter_size;
    uint16_t *lum_filter = inst[0].filter[0];
    uint16_t *chr_filter = inst[1].filter[0];

    int firstLum = FFMAX(1-lum_fsize, inst[0].filter_pos[   sliceY]);
    int firstChr = FFMAX(1-chr_fsize, inst[1].filter_pos[chrSliceY]);

    int sp0 = firstLum - desc->src->plane[0].sliceY;
    int sp1 = firstChr - desc->src->plane[1].sliceY;
    int sp2 = firstChr - desc->src->plane[2].sliceY;
    int sp3 = firstLum - desc->src->plane[3].sliceY;
    int dp = sliceY - desc->dst->plane[0].sliceY;
    uint8_t **src0 = desc->src->plane[0].line + sp0;
    uint8_t **src1 = desc->src->plane[1].line + sp1;
    uint8_t **src2 = desc->src->plane[2].line + sp2;
    uint8_t **src3 = desc->alpha ? desc->src->plane[3].line + sp3 : NULL;
    uint8_t **dst = desc->dst->plane[0].line + dp;


    if (c->yuv2packed1 && lum_fsize == 1 && chr_fsize == 1) { // unscaled RGB
        ((yuv2packed1_fn)inst->pfn)(c, (const int16_t*)*src0, (const int16_t**)src1, (const int16_t**)src2,
                                    (const int16_t*)(desc->alpha ? *src3 : NULL),  *dst, dstW, 0, sliceY);
    } else if (c->yuv2packed1 && lum_fsize == 1 && chr_fsize == 2 &&
               chr_filter[2 * chrSliceY + 1] + chr_filter[2 * chrSliceY] == 4096 &&
               chr_filter[2 * chrSliceY + 1] <= 4096U) { // unscaled RGB
        int chrAlpha = chr_filter[2 * chrSliceY + 1];
        ((yuv2packed1_fn)inst->pfn)(c, (const int16_t*)*src0, (const int16_t**)src1, (const int16_t**)src2,
                                    (const int16_t*)(desc->alpha ? *src3 : NULL),  *dst, dstW, chrAlpha, sliceY);
    } else if (c->yuv2packed2 && lum_fsize == 2 && chr_fsize == 2 &&
               lum_filter[2 * sliceY + 1] + lum_filter[2 * sliceY] == 4096 &&
               lum_filter[2 * sliceY + 1] <= 4096U &&
               chr_filter[2 * chrSliceY + 1] + chr_filter[2 * chrSliceY] == 4096 &&
               chr_filter[2 * chrSliceY + 1] <= 4096U
    ) { // bilinear upscale RGB
        int lumAlpha = lum_filter[2 * sliceY + 1];
        int chrAlpha = chr_filter[2 * chrSliceY + 1];
        c->lumMmxFilter[2] =
        c->lumMmxFilter[3] = lum_filter[2 * sliceY]    * 0x10001;
        c->chrMmxFilter[2] =
        c->chrMmxFilter[3] = chr_filter[2 * chrSliceY] * 0x10001;
        ((yuv2packed2_fn)inst->pfn)(c, (const int16_t**)src0, (const int16_t**)src1, (const int16_t**)src2, (const int16_t**)src3,
                    *dst, dstW, lumAlpha, chrAlpha, sliceY);
    } else { // general RGB
        if ((c->yuv2packed1 && lum_fsize == 1 && chr_fsize == 2) ||
            (c->yuv2packed2 && lum_fsize == 2 && chr_fsize == 2)) {
            if (!c->warned_unuseable_bilinear)
                av_log(c, AV_LOG_INFO, "Optimized 2 tap filter code cannot be used\n");
            c->warned_unuseable_bilinear = 1;
        }

        inst->yuv2packedX(c, lum_filter + sliceY * lum_fsize,
                    (const int16_t**)src0, lum_fsize, chr_filter + chrSliceY * chr_fsize,
                    (const int16_t**)src1, (const int16_t**)src2, chr_fsize, (const int16_t**)src3, *dst, dstW, sliceY);
    }
    return 1;
}