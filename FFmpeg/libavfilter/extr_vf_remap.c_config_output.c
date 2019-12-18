#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  time_base; int /*<<< orphan*/  on_event; TYPE_2__* opaque; TYPE_3__* in; } ;
struct TYPE_15__ {TYPE_1__* input_pads; TYPE_4__** inputs; TYPE_2__* priv; } ;
struct TYPE_14__ {scalar_t__ w; scalar_t__ h; int /*<<< orphan*/  time_base; int /*<<< orphan*/  frame_rate; int /*<<< orphan*/  sample_aspect_ratio; TYPE_5__* src; } ;
struct TYPE_13__ {int sync; void* after; void* before; int /*<<< orphan*/  time_base; } ;
struct TYPE_12__ {TYPE_6__ fs; } ;
struct TYPE_11__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ RemapContext ;
typedef  TYPE_3__ FFFrameSyncIn ;
typedef  TYPE_4__ AVFilterLink ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 void* EXT_INFINITY ; 
 void* EXT_NULL ; 
 void* EXT_STOP ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int ff_framesync_configure (TYPE_6__*) ; 
 int ff_framesync_init (TYPE_6__*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  process_frame ; 

__attribute__((used)) static int config_output(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    RemapContext *s = ctx->priv;
    AVFilterLink *srclink = ctx->inputs[0];
    AVFilterLink *xlink = ctx->inputs[1];
    AVFilterLink *ylink = ctx->inputs[2];
    FFFrameSyncIn *in;
    int ret;

    if (xlink->w != ylink->w || xlink->h != ylink->h) {
        av_log(ctx, AV_LOG_ERROR, "Second input link %s parameters "
               "(size %dx%d) do not match the corresponding "
               "third input link %s parameters (%dx%d)\n",
               ctx->input_pads[1].name, xlink->w, xlink->h,
               ctx->input_pads[2].name, ylink->w, ylink->h);
        return AVERROR(EINVAL);
    }

    outlink->w = xlink->w;
    outlink->h = xlink->h;
    outlink->sample_aspect_ratio = srclink->sample_aspect_ratio;
    outlink->frame_rate = srclink->frame_rate;

    ret = ff_framesync_init(&s->fs, ctx, 3);
    if (ret < 0)
        return ret;

    in = s->fs.in;
    in[0].time_base = srclink->time_base;
    in[1].time_base = xlink->time_base;
    in[2].time_base = ylink->time_base;
    in[0].sync   = 2;
    in[0].before = EXT_STOP;
    in[0].after  = EXT_STOP;
    in[1].sync   = 1;
    in[1].before = EXT_NULL;
    in[1].after  = EXT_INFINITY;
    in[2].sync   = 1;
    in[2].before = EXT_NULL;
    in[2].after  = EXT_INFINITY;
    s->fs.opaque   = s;
    s->fs.on_event = process_frame;

    ret = ff_framesync_configure(&s->fs);
    outlink->time_base = s->fs.time_base;

    return ret;
}