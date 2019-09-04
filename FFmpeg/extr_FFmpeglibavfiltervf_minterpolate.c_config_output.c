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
struct TYPE_7__ {int /*<<< orphan*/  time_base; int /*<<< orphan*/  frame_rate; TYPE_1__* src; } ;
struct TYPE_6__ {int /*<<< orphan*/  frame_rate; } ;
struct TYPE_5__ {TYPE_2__* priv; } ;
typedef  TYPE_2__ MIContext ;
typedef  TYPE_3__ AVFilterLink ;

/* Variables and functions */
 int /*<<< orphan*/  av_inv_q (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_output(AVFilterLink *outlink)
{
    MIContext *mi_ctx = outlink->src->priv;

    outlink->frame_rate = mi_ctx->frame_rate;
    outlink->time_base  = av_inv_q(mi_ctx->frame_rate);

    return 0;
}