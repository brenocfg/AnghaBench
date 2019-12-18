#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_20__ {int xInc; int /*<<< orphan*/  filter_size; int /*<<< orphan*/  filter_pos; int /*<<< orphan*/  filter; } ;
struct TYPE_19__ {int /*<<< orphan*/  (* hyScale ) (TYPE_6__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* hyscale_fast ) (TYPE_6__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int) ;int /*<<< orphan*/  (* lumConvertRange ) (int /*<<< orphan*/ *,int) ;} ;
struct TYPE_18__ {TYPE_4__* dst; TYPE_2__* src; scalar_t__ alpha; TYPE_7__* instance; } ;
struct TYPE_17__ {int width; TYPE_3__* plane; } ;
struct TYPE_16__ {int sliceY; int sliceH; int /*<<< orphan*/ ** line; } ;
struct TYPE_15__ {int width; TYPE_1__* plane; } ;
struct TYPE_14__ {int sliceY; int /*<<< orphan*/ ** line; } ;
typedef  TYPE_5__ SwsFilterDescriptor ;
typedef  TYPE_6__ SwsContext ;
typedef  TYPE_7__ FilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_6__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_6__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub4 (TYPE_6__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  stub5 (TYPE_6__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lum_h_scale(SwsContext *c, SwsFilterDescriptor *desc, int sliceY, int sliceH)
{
    FilterContext *instance = desc->instance;
    int srcW = desc->src->width;
    int dstW = desc->dst->width;
    int xInc = instance->xInc;

    int i;
    for (i = 0; i < sliceH; ++i) {
        uint8_t ** src = desc->src->plane[0].line;
        uint8_t ** dst = desc->dst->plane[0].line;
        int src_pos = sliceY+i - desc->src->plane[0].sliceY;
        int dst_pos = sliceY+i - desc->dst->plane[0].sliceY;


        if (c->hyscale_fast) {
            c->hyscale_fast(c, (int16_t*)dst[dst_pos], dstW, src[src_pos], srcW, xInc);
        } else {
            c->hyScale(c, (int16_t*)dst[dst_pos], dstW, (const uint8_t *)src[src_pos], instance->filter,
                       instance->filter_pos, instance->filter_size);
        }

        if (c->lumConvertRange)
            c->lumConvertRange((int16_t*)dst[dst_pos], dstW);

        desc->dst->plane[0].sliceH += 1;

        if (desc->alpha) {
            src = desc->src->plane[3].line;
            dst = desc->dst->plane[3].line;

            src_pos = sliceY+i - desc->src->plane[3].sliceY;
            dst_pos = sliceY+i - desc->dst->plane[3].sliceY;

            desc->dst->plane[3].sliceH += 1;

            if (c->hyscale_fast) {
                c->hyscale_fast(c, (int16_t*)dst[dst_pos], dstW, src[src_pos], srcW, xInc);
            } else {
                c->hyScale(c, (int16_t*)dst[dst_pos], dstW, (const uint8_t *)src[src_pos], instance->filter,
                            instance->filter_pos, instance->filter_size);
            }
        }
    }

    return sliceH;
}