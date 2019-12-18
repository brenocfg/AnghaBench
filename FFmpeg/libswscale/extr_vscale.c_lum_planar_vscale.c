#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  (* yuv2planarX_fn ) (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;
typedef  int /*<<< orphan*/  (* yuv2planar1_fn ) (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_14__ {int filter_size; scalar_t__ pfn; scalar_t__ isMMX; int /*<<< orphan*/ ** filter; int /*<<< orphan*/ * filter_pos; } ;
typedef  TYPE_5__ VScalerContext ;
struct TYPE_16__ {int /*<<< orphan*/  lumDither8; } ;
struct TYPE_15__ {TYPE_4__* dst; TYPE_2__* src; scalar_t__ alpha; TYPE_5__* instance; } ;
struct TYPE_13__ {int width; TYPE_3__* plane; } ;
struct TYPE_12__ {int sliceY; int /*<<< orphan*/ ** line; } ;
struct TYPE_11__ {TYPE_1__* plane; } ;
struct TYPE_10__ {int sliceY; int /*<<< orphan*/ ** line; } ;
typedef  TYPE_6__ SwsFilterDescriptor ;
typedef  TYPE_7__ SwsContext ;

/* Variables and functions */
 int FFMAX (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lum_planar_vscale(SwsContext *c, SwsFilterDescriptor *desc, int sliceY, int sliceH)
{
    VScalerContext *inst = desc->instance;
    int dstW = desc->dst->width;

    int first = FFMAX(1-inst->filter_size, inst->filter_pos[sliceY]);
    int sp = first - desc->src->plane[0].sliceY;
    int dp = sliceY - desc->dst->plane[0].sliceY;
    uint8_t **src = desc->src->plane[0].line + sp;
    uint8_t **dst = desc->dst->plane[0].line + dp;
    uint16_t *filter = inst->filter[0] + (inst->isMMX ? 0 : sliceY * inst->filter_size);

    if (inst->filter_size == 1)
        ((yuv2planar1_fn)inst->pfn)((const int16_t*)src[0], dst[0], dstW, c->lumDither8, 0);
    else
        ((yuv2planarX_fn)inst->pfn)(filter, inst->filter_size, (const int16_t**)src, dst[0], dstW, c->lumDither8, 0);

    if (desc->alpha) {
        int sp = first - desc->src->plane[3].sliceY;
        int dp = sliceY - desc->dst->plane[3].sliceY;
        uint8_t **src = desc->src->plane[3].line + sp;
        uint8_t **dst = desc->dst->plane[3].line + dp;
        uint16_t *filter = inst->filter[1] + (inst->isMMX ? 0 : sliceY * inst->filter_size);

        if (inst->filter_size == 1)
            ((yuv2planar1_fn)inst->pfn)((const int16_t*)src[0], dst[0], dstW, c->lumDither8, 0);
        else
            ((yuv2planarX_fn)inst->pfn)(filter, inst->filter_size, (const int16_t**)src, dst[0], dstW, c->lumDither8, 0);
    }

    return 1;
}