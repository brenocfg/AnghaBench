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
struct TYPE_5__ {TYPE_1__** inputs; } ;
struct TYPE_4__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  sample_aspect_ratio; int /*<<< orphan*/  frame_rate; int /*<<< orphan*/  time_base; TYPE_2__* src; } ;
typedef  TYPE_1__ AVFilterLink ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */

__attribute__((used)) static int config_output(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    AVFilterLink *inlink = ctx->inputs[0];

    outlink->time_base = inlink->time_base;
    outlink->frame_rate = inlink->frame_rate;
    outlink->sample_aspect_ratio = inlink->sample_aspect_ratio;
    outlink->w = inlink->w;
    outlink->h = inlink->h;

    return 0;
}