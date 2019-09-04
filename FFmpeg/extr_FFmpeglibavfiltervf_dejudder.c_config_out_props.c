#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__** inputs; TYPE_1__* priv; } ;
struct TYPE_7__ {void* frame_rate; void* time_base; TYPE_3__* src; } ;
struct TYPE_6__ {int cycle; } ;
typedef  TYPE_1__ DejudderContext ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  av_make_q (int,int) ; 
 void* av_mul_q (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_out_props(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    DejudderContext *s = ctx->priv;
    AVFilterLink *inlink = outlink->src->inputs[0];

    outlink->time_base = av_mul_q(inlink->time_base, av_make_q(1, 2 * s->cycle));
    outlink->frame_rate = av_mul_q(inlink->frame_rate, av_make_q(2 * s->cycle, 1));

    av_log(ctx, AV_LOG_VERBOSE, "cycle:%d\n", s->cycle);

    return 0;
}