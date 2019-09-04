#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_13__ ;

/* Type definitions */
struct TYPE_26__ {scalar_t__ is_disabled; TYPE_4__** outputs; } ;
struct TYPE_25__ {int /*<<< orphan*/  time_base; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct TYPE_24__ {int /*<<< orphan*/  pts; } ;
struct TYPE_23__ {TYPE_1__* opaque; TYPE_5__* parent; } ;
struct TYPE_21__ {int /*<<< orphan*/  time_base; int /*<<< orphan*/  pts; } ;
struct TYPE_22__ {TYPE_13__ fs; int /*<<< orphan*/  (* lut2 ) (TYPE_1__*,TYPE_3__*,TYPE_3__*,TYPE_3__*) ;} ;
typedef  TYPE_1__ LUT2Context ;
typedef  TYPE_2__ FFFrameSync ;
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
 int ff_framesync_get_frame (TYPE_13__*,int,TYPE_3__**,int /*<<< orphan*/ ) ; 
 TYPE_3__* ff_get_video_buffer (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,TYPE_3__*,TYPE_3__*,TYPE_3__*) ; 

__attribute__((used)) static int process_frame(FFFrameSync *fs)
{
    AVFilterContext *ctx = fs->parent;
    LUT2Context *s = fs->opaque;
    AVFilterLink *outlink = ctx->outputs[0];
    AVFrame *out, *srcx = NULL, *srcy = NULL;
    int ret;

    if ((ret = ff_framesync_get_frame(&s->fs, 0, &srcx, 0)) < 0 ||
        (ret = ff_framesync_get_frame(&s->fs, 1, &srcy, 0)) < 0)
        return ret;

    if (ctx->is_disabled || !srcy) {
        out = av_frame_clone(srcx);
        if (!out)
            return AVERROR(ENOMEM);
    } else {
        out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
        if (!out)
            return AVERROR(ENOMEM);
        av_frame_copy_props(out, srcx);

        s->lut2(s, out, srcx, srcy);
    }

    out->pts = av_rescale_q(s->fs.pts, s->fs.time_base, outlink->time_base);

    return ff_filter_frame(outlink, out);
}