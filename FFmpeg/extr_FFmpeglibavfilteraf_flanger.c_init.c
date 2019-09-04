#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* priv; } ;
struct TYPE_4__ {int feedback_gain; int delay_gain; int channel_phase; int delay_min; int delay_depth; int in_gain; } ;
typedef  TYPE_1__ FlangerContext ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int fabs (int) ; 

__attribute__((used)) static int init(AVFilterContext *ctx)
{
    FlangerContext *s = ctx->priv;

    s->feedback_gain /= 100;
    s->delay_gain    /= 100;
    s->channel_phase /= 100;
    s->delay_min     /= 1000;
    s->delay_depth   /= 1000;
    s->in_gain        = 1 / (1 + s->delay_gain);
    s->delay_gain    /= 1 + s->delay_gain;
    s->delay_gain    *= 1 - fabs(s->feedback_gain);

    return 0;
}