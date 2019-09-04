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
struct TYPE_7__ {TYPE_1__* priv; } ;
struct TYPE_6__ {int /*<<< orphan*/  frame_rate; int /*<<< orphan*/  format; TYPE_3__* dst; } ;
struct TYPE_5__ {scalar_t__ stop_duration; void* pad_stop; scalar_t__ start_duration; void* pad_start; int /*<<< orphan*/  rgba_color; int /*<<< orphan*/  color; int /*<<< orphan*/  draw; } ;
typedef  TYPE_1__ TPadContext ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_TIME_BASE_Q ; 
 int /*<<< orphan*/  av_inv_q (int /*<<< orphan*/ ) ; 
 void* av_rescale_q (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_draw_color (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_draw_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    AVFilterContext *ctx = inlink->dst;
    TPadContext *s = ctx->priv;

    ff_draw_init(&s->draw, inlink->format, 0);
    ff_draw_color(&s->draw, &s->color, s->rgba_color);

    if (s->start_duration)
        s->pad_start = av_rescale_q(s->start_duration, inlink->frame_rate, av_inv_q(AV_TIME_BASE_Q));
    if (s->stop_duration)
        s->pad_stop = av_rescale_q(s->stop_duration, inlink->frame_rate, av_inv_q(AV_TIME_BASE_Q));

    return 0;
}