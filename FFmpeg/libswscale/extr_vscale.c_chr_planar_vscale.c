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
typedef  int /*<<< orphan*/  (* yuv2planarX_fn ) (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ;
typedef  int /*<<< orphan*/  (* yuv2planar1_fn ) (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ;
typedef  int /*<<< orphan*/  (* yuv2interleavedX_fn ) (TYPE_5__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int) ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_17__ {int filter_size; scalar_t__ isMMX; scalar_t__ pfn; int /*<<< orphan*/ ** filter; int /*<<< orphan*/ * filter_pos; } ;
typedef  TYPE_6__ VScalerContext ;
struct TYPE_18__ {TYPE_4__* dst; TYPE_2__* src; TYPE_6__* instance; } ;
struct TYPE_16__ {int uv_offx2; int /*<<< orphan*/  chrDither8; scalar_t__ yuv2nv12cX; } ;
struct TYPE_15__ {int v_chr_sub_sample; TYPE_3__* plane; int /*<<< orphan*/  h_chr_sub_sample; int /*<<< orphan*/  width; } ;
struct TYPE_14__ {int sliceY; int /*<<< orphan*/ ** line; } ;
struct TYPE_13__ {TYPE_1__* plane; } ;
struct TYPE_12__ {int sliceY; int /*<<< orphan*/ ** line; } ;
typedef  TYPE_7__ SwsFilterDescriptor ;
typedef  TYPE_5__ SwsContext ;

/* Variables and functions */
 int AV_CEIL_RSHIFT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FFMAX (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int chr_planar_vscale(SwsContext *c, SwsFilterDescriptor *desc, int sliceY, int sliceH)
{
    const int chrSkipMask = (1 << desc->dst->v_chr_sub_sample) - 1;
    if (sliceY & chrSkipMask)
        return 0;
    else {
        VScalerContext *inst = desc->instance;
        int dstW = AV_CEIL_RSHIFT(desc->dst->width, desc->dst->h_chr_sub_sample);
        int chrSliceY = sliceY >> desc->dst->v_chr_sub_sample;

        int first = FFMAX(1-inst->filter_size, inst->filter_pos[chrSliceY]);
        int sp1 = first - desc->src->plane[1].sliceY;
        int sp2 = first - desc->src->plane[2].sliceY;
        int dp1 = chrSliceY - desc->dst->plane[1].sliceY;
        int dp2 = chrSliceY - desc->dst->plane[2].sliceY;
        uint8_t **src1 = desc->src->plane[1].line + sp1;
        uint8_t **src2 = desc->src->plane[2].line + sp2;
        uint8_t **dst1 = desc->dst->plane[1].line + dp1;
        uint8_t **dst2 = desc->dst->plane[2].line + dp2;
        uint16_t *filter = inst->filter[0] + (inst->isMMX ? 0 : chrSliceY * inst->filter_size);

        if (c->yuv2nv12cX) {
            ((yuv2interleavedX_fn)inst->pfn)(c, filter, inst->filter_size, (const int16_t**)src1, (const int16_t**)src2, dst1[0], dstW);
        } else if (inst->filter_size == 1) {
            ((yuv2planar1_fn)inst->pfn)((const int16_t*)src1[0], dst1[0], dstW, c->chrDither8, 0);
            ((yuv2planar1_fn)inst->pfn)((const int16_t*)src2[0], dst2[0], dstW, c->chrDither8, 3);
        } else {
            ((yuv2planarX_fn)inst->pfn)(filter, inst->filter_size, (const int16_t**)src1, dst1[0], dstW, c->chrDither8, 0);
            ((yuv2planarX_fn)inst->pfn)(filter, inst->filter_size, (const int16_t**)src2, dst2[0], dstW, c->chrDither8, inst->isMMX ? (c->uv_offx2 >> 1) : 3);
        }
    }

    return 1;
}