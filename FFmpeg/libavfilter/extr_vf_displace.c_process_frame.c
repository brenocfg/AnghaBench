#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_14__ ;

/* Type definitions */
struct TYPE_27__ {scalar_t__ is_disabled; TYPE_4__** outputs; } ;
struct TYPE_26__ {int /*<<< orphan*/  time_base; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct TYPE_25__ {int /*<<< orphan*/  pts; } ;
struct TYPE_22__ {int /*<<< orphan*/  time_base; int /*<<< orphan*/  pts; } ;
struct TYPE_24__ {TYPE_14__ fs; int /*<<< orphan*/  (* displace ) (TYPE_2__*,TYPE_3__*,TYPE_3__*,TYPE_3__*,TYPE_3__*) ;} ;
struct TYPE_23__ {TYPE_2__* opaque; TYPE_5__* parent; } ;
typedef  TYPE_1__ FFFrameSync ;
typedef  TYPE_2__ DisplaceContext ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFilterLink ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_3__* av_frame_clone (TYPE_3__*) ; 
 int /*<<< orphan*/  av_frame_copy_props (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  av_rescale_q (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ff_filter_frame (TYPE_4__*,TYPE_3__*) ; 
 int ff_framesync_get_frame (TYPE_14__*,int,TYPE_3__**,int /*<<< orphan*/ ) ; 
 TYPE_3__* ff_get_video_buffer (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,TYPE_3__*,TYPE_3__*,TYPE_3__*,TYPE_3__*) ; 

__attribute__((used)) static int process_frame(FFFrameSync *fs)
{
    AVFilterContext *ctx = fs->parent;
    DisplaceContext *s = fs->opaque;
    AVFilterLink *outlink = ctx->outputs[0];
    AVFrame *out, *in, *xpic, *ypic;
    int ret;

    if ((ret = ff_framesync_get_frame(&s->fs, 0, &in,   0)) < 0 ||
        (ret = ff_framesync_get_frame(&s->fs, 1, &xpic, 0)) < 0 ||
        (ret = ff_framesync_get_frame(&s->fs, 2, &ypic, 0)) < 0)
        return ret;

    if (ctx->is_disabled) {
        out = av_frame_clone(in);
        if (!out)
            return AVERROR(ENOMEM);
    } else {
        out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
        if (!out)
            return AVERROR(ENOMEM);
        av_frame_copy_props(out, in);

        s->displace(s, in, xpic, ypic, out);
    }
    out->pts = av_rescale_q(s->fs.pts, s->fs.time_base, outlink->time_base);

    return ff_filter_frame(outlink, out);
}