#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ total_bits; TYPE_1__* avctx; } ;
struct TYPE_6__ {int den; scalar_t__ num; } ;
struct TYPE_5__ {int bit_rate; int ticks_per_frame; double frame_number; TYPE_2__ time_base; } ;
typedef  TYPE_3__ FlashSV2Context ;

/* Variables and functions */
 scalar_t__ use15_7_threshold ; 

__attribute__((used)) static int optimum_use15_7(FlashSV2Context * s)
{
#ifndef FLASHSV2_DUMB
    double ideal = ((double)(s->avctx->bit_rate * s->avctx->time_base.den * s->avctx->ticks_per_frame)) /
        ((double) s->avctx->time_base.num) * s->avctx->frame_number;
    if (ideal + use15_7_threshold < s->total_bits) {
        return 1;
    } else {
        return 0;
    }
#else
    return s->avctx->global_quality == 0;
#endif
}