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
struct TYPE_5__ {int w; int h; int /*<<< orphan*/  time_base; int /*<<< orphan*/  sample_aspect_ratio; TYPE_1__* src; int /*<<< orphan*/ * dst; } ;
struct TYPE_4__ {TYPE_2__** inputs; } ;
typedef  TYPE_2__ AVFilterLink ;
typedef  int /*<<< orphan*/  AVFilterContext ;

/* Variables and functions */
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static int config_props(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->dst;
    AVFilterLink *inlink = outlink->src->inputs[0];

    if (inlink->w % 2 || inlink->h % 2) {
        av_log(ctx, AV_LOG_ERROR, "Invalid odd size (%dx%d)\n",
               inlink->w, inlink->h);
        return AVERROR_PATCHWELCOME;
    }

    outlink->w = inlink->w;
    outlink->h = inlink->h;
    outlink->sample_aspect_ratio = inlink->sample_aspect_ratio;
    outlink->time_base = inlink->time_base;

    return 0;
}