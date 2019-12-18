#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  time_base; int /*<<< orphan*/  on_event; TYPE_1__* opaque; TYPE_2__* in; } ;
struct TYPE_13__ {TYPE_3__** inputs; TYPE_1__* priv; } ;
struct TYPE_12__ {scalar_t__ format; int /*<<< orphan*/  time_base; int /*<<< orphan*/  frame_rate; int /*<<< orphan*/  sample_aspect_ratio; int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_4__* src; } ;
struct TYPE_11__ {int sync; void* after; void* before; int /*<<< orphan*/  time_base; } ;
struct TYPE_10__ {TYPE_5__ fs; } ;
typedef  TYPE_1__ MidEqualizerContext ;
typedef  TYPE_2__ FFFrameSyncIn ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 void* EXT_INFINITY ; 
 void* EXT_STOP ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int ff_framesync_configure (TYPE_5__*) ; 
 int ff_framesync_init (TYPE_5__*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  process_frame ; 

__attribute__((used)) static int config_output(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    MidEqualizerContext *s = ctx->priv;
    AVFilterLink *in0 = ctx->inputs[0];
    AVFilterLink *in1 = ctx->inputs[1];
    FFFrameSyncIn *in;
    int ret;

    if (in0->format != in1->format) {
        av_log(ctx, AV_LOG_ERROR, "inputs must be of same pixel format\n");
        return AVERROR(EINVAL);
    }

    outlink->w = in0->w;
    outlink->h = in0->h;
    outlink->sample_aspect_ratio = in0->sample_aspect_ratio;
    outlink->frame_rate = in0->frame_rate;

    if ((ret = ff_framesync_init(&s->fs, ctx, 2)) < 0)
        return ret;

    in = s->fs.in;
    in[0].time_base = in0->time_base;
    in[1].time_base = in1->time_base;
    in[0].sync   = 1;
    in[0].before = EXT_STOP;
    in[0].after  = EXT_INFINITY;
    in[1].sync   = 1;
    in[1].before = EXT_STOP;
    in[1].after  = EXT_INFINITY;
    s->fs.opaque   = s;
    s->fs.on_event = process_frame;

    ret = ff_framesync_configure(&s->fs);
    outlink->time_base = s->fs.time_base;

    return ret;
}