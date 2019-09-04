#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_10__ {int* filter_pos; int filter_size; int xInc; int /*<<< orphan*/ * filter; } ;
struct TYPE_9__ {int alpha; int /*<<< orphan*/ * process; TYPE_1__* dst; TYPE_1__* src; TYPE_3__* instance; } ;
struct TYPE_8__ {int /*<<< orphan*/  fmt; } ;
typedef  TYPE_1__ SwsSlice ;
typedef  TYPE_2__ SwsFilterDescriptor ;
typedef  TYPE_3__ FilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_3__* av_malloc (int) ; 
 int /*<<< orphan*/  chr_h_scale ; 
 scalar_t__ isALPHA (int /*<<< orphan*/ ) ; 

int ff_init_desc_chscale(SwsFilterDescriptor *desc, SwsSlice *src, SwsSlice *dst, uint16_t *filter, int * filter_pos, int filter_size, int xInc)
{
    FilterContext *li = av_malloc(sizeof(FilterContext));
    if (!li)
        return AVERROR(ENOMEM);

    li->filter = filter;
    li->filter_pos = filter_pos;
    li->filter_size = filter_size;
    li->xInc = xInc;

    desc->instance = li;

    desc->alpha = isALPHA(src->fmt) && isALPHA(dst->fmt);
    desc->src = src;
    desc->dst = dst;

    desc->process = &chr_h_scale;

    return 0;
}