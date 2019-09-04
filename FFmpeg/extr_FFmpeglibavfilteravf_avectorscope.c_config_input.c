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
struct TYPE_6__ {scalar_t__ sample_rate; TYPE_3__* dst; } ;
struct TYPE_5__ {int /*<<< orphan*/  frame_rate; int /*<<< orphan*/  nb_samples; } ;
typedef  TYPE_1__ AudioVectorScopeContext ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  FFMAX (int,double) ; 
 double av_q2d (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    AVFilterContext *ctx = inlink->dst;
    AudioVectorScopeContext *s = ctx->priv;

    s->nb_samples = FFMAX(1, ((double)inlink->sample_rate / av_q2d(s->frame_rate)) + 0.5);

    return 0;
}