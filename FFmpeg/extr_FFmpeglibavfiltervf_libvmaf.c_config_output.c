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
struct TYPE_7__ {int /*<<< orphan*/  frame_rate; int /*<<< orphan*/  sample_aspect_ratio; int /*<<< orphan*/  time_base; int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_3__* src; } ;
struct TYPE_6__ {int /*<<< orphan*/  fs; } ;
typedef  TYPE_1__ LIBVMAFContext ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int ff_framesync_configure (int /*<<< orphan*/ *) ; 
 int ff_framesync_init_dualinput (int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static int config_output(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    LIBVMAFContext *s = ctx->priv;
    AVFilterLink *mainlink = ctx->inputs[0];
    int ret;

    ret = ff_framesync_init_dualinput(&s->fs, ctx);
    if (ret < 0)
        return ret;
    outlink->w = mainlink->w;
    outlink->h = mainlink->h;
    outlink->time_base = mainlink->time_base;
    outlink->sample_aspect_ratio = mainlink->sample_aspect_ratio;
    outlink->frame_rate = mainlink->frame_rate;
    if ((ret = ff_framesync_configure(&s->fs)) < 0)
        return ret;

    return 0;
}