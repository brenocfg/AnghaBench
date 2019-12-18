#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {double den; } ;
struct TYPE_7__ {double bit_rate; double ticks_per_frame; TYPE_1__ time_base; } ;
struct TYPE_6__ {double total_bits; TYPE_4__* avctx; } ;
typedef  TYPE_2__ FlashSV2Context ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,int) ; 
 double color15_7_factor ; 
 int pow (double,int) ; 

__attribute__((used)) static int optimum_dist(FlashSV2Context * s)
{
#ifndef FLASHSV2_DUMB
    double ideal =
        s->avctx->bit_rate * s->avctx->time_base.den *
        s->avctx->ticks_per_frame;
    int dist = pow((s->total_bits / ideal) * color15_7_factor, 3);
    av_log(s->avctx, AV_LOG_DEBUG, "dist: %d\n", dist);
    return dist;
#else
    return 15;
#endif
}