#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  (* yuv2anyX_fn ) (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int,int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int,int /*<<< orphan*/  const**,int /*<<< orphan*/ **,int,int) ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_17__ {int filter_size; scalar_t__ pfn; int /*<<< orphan*/ * filter_pos; int /*<<< orphan*/ ** filter; } ;
typedef  TYPE_6__ VScalerContext ;
struct TYPE_18__ {TYPE_4__* dst; scalar_t__ alpha; TYPE_2__* src; TYPE_6__* instance; } ;
struct TYPE_16__ {int /*<<< orphan*/  yuv2packed2; int /*<<< orphan*/  yuv2packed1; } ;
struct TYPE_15__ {int width; int v_chr_sub_sample; TYPE_3__* plane; } ;
struct TYPE_14__ {int sliceY; int /*<<< orphan*/ ** line; } ;
struct TYPE_13__ {TYPE_1__* plane; } ;
struct TYPE_12__ {int sliceY; int /*<<< orphan*/ ** line; } ;
typedef  TYPE_7__ SwsFilterDescriptor ;
typedef  TYPE_5__ SwsContext ;

/* Variables and functions */
 int FFMAX (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_assert1 (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int,int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int,int /*<<< orphan*/  const**,int /*<<< orphan*/ **,int,int) ; 

__attribute__((used)) static int any_vscale(SwsContext *c, SwsFilterDescriptor *desc, int sliceY, int sliceH)
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
    int dp0 = sliceY - desc->dst->plane[0].sliceY;
    int dp1 = chrSliceY - desc->dst->plane[1].sliceY;
    int dp2 = chrSliceY - desc->dst->plane[2].sliceY;
    int dp3 = sliceY - desc->dst->plane[3].sliceY;

    uint8_t **src0 = desc->src->plane[0].line + sp0;
    uint8_t **src1 = desc->src->plane[1].line + sp1;
    uint8_t **src2 = desc->src->plane[2].line + sp2;
    uint8_t **src3 = desc->alpha ? desc->src->plane[3].line + sp3 : NULL;
    uint8_t *dst[4] = { desc->dst->plane[0].line[dp0],
                        desc->dst->plane[1].line[dp1],
                        desc->dst->plane[2].line[dp2],
                        desc->alpha ? desc->dst->plane[3].line[dp3] : NULL };

    av_assert1(!c->yuv2packed1 && !c->yuv2packed2);
    ((yuv2anyX_fn)inst->pfn)(c, lum_filter + sliceY * lum_fsize,
             (const int16_t**)src0, lum_fsize, chr_filter + sliceY * chr_fsize,
             (const int16_t**)src1, (const int16_t**)src2, chr_fsize, (const int16_t**)src3, dst, dstW, sliceY);

    return 1;

}