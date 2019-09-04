#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_19__ {int xInc; int /*<<< orphan*/  filter_size; int /*<<< orphan*/  filter_pos; int /*<<< orphan*/  filter; } ;
struct TYPE_18__ {int /*<<< orphan*/  (* chrConvertRange ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  (* hcScale ) (TYPE_6__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* hcscale_fast ) (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ;} ;
struct TYPE_17__ {TYPE_4__* dst; TYPE_2__* src; TYPE_7__* instance; } ;
struct TYPE_16__ {TYPE_3__* plane; int /*<<< orphan*/  h_chr_sub_sample; int /*<<< orphan*/  width; } ;
struct TYPE_15__ {int sliceY; int sliceH; int /*<<< orphan*/ ** line; } ;
struct TYPE_14__ {TYPE_1__* plane; int /*<<< orphan*/  h_chr_sub_sample; int /*<<< orphan*/  width; } ;
struct TYPE_13__ {int sliceY; int /*<<< orphan*/ ** line; } ;
typedef  TYPE_5__ SwsFilterDescriptor ;
typedef  TYPE_6__ SwsContext ;
typedef  TYPE_7__ FilterContext ;

/* Variables and functions */
 int AV_CEIL_RSHIFT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_6__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_6__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int chr_h_scale(SwsContext *c, SwsFilterDescriptor *desc, int sliceY, int sliceH)
{
    FilterContext *instance = desc->instance;
    int srcW = AV_CEIL_RSHIFT(desc->src->width, desc->src->h_chr_sub_sample);
    int dstW = AV_CEIL_RSHIFT(desc->dst->width, desc->dst->h_chr_sub_sample);
    int xInc = instance->xInc;

    uint8_t ** src1 = desc->src->plane[1].line;
    uint8_t ** dst1 = desc->dst->plane[1].line;
    uint8_t ** src2 = desc->src->plane[2].line;
    uint8_t ** dst2 = desc->dst->plane[2].line;

    int src_pos1 = sliceY - desc->src->plane[1].sliceY;
    int dst_pos1 = sliceY - desc->dst->plane[1].sliceY;

    int src_pos2 = sliceY - desc->src->plane[2].sliceY;
    int dst_pos2 = sliceY - desc->dst->plane[2].sliceY;

    int i;
    for (i = 0; i < sliceH; ++i) {
        if (c->hcscale_fast) {
            c->hcscale_fast(c, (uint16_t*)dst1[dst_pos1+i], (uint16_t*)dst2[dst_pos2+i], dstW, src1[src_pos1+i], src2[src_pos2+i], srcW, xInc);
        } else {
            c->hcScale(c, (uint16_t*)dst1[dst_pos1+i], dstW, src1[src_pos1+i], instance->filter, instance->filter_pos, instance->filter_size);
            c->hcScale(c, (uint16_t*)dst2[dst_pos2+i], dstW, src2[src_pos2+i], instance->filter, instance->filter_pos, instance->filter_size);
        }

        if (c->chrConvertRange)
            c->chrConvertRange((uint16_t*)dst1[dst_pos1+i], (uint16_t*)dst2[dst_pos2+i], dstW);

        desc->dst->plane[1].sliceH += 1;
        desc->dst->plane[2].sliceH += 1;
    }
    return sliceH;
}