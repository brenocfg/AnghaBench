#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_13__ ;

/* Type definitions */
struct TYPE_24__ {TYPE_5__* mask; TYPE_5__* overlay; TYPE_5__* base; TYPE_5__* out; } ;
typedef  TYPE_2__ ThreadData ;
struct TYPE_29__ {TYPE_1__* internal; scalar_t__ is_disabled; TYPE_6__** outputs; } ;
struct TYPE_28__ {int /*<<< orphan*/  time_base; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct TYPE_27__ {int /*<<< orphan*/  pts; } ;
struct TYPE_26__ {TYPE_3__* opaque; TYPE_7__* parent; } ;
struct TYPE_22__ {int /*<<< orphan*/  time_base; int /*<<< orphan*/  pts; } ;
struct TYPE_25__ {TYPE_13__ fs; int /*<<< orphan*/ * height; } ;
struct TYPE_23__ {int /*<<< orphan*/  (* execute ) (TYPE_7__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__ MaskedMergeContext ;
typedef  TYPE_4__ FFFrameSync ;
typedef  TYPE_5__ AVFrame ;
typedef  TYPE_6__ AVFilterLink ;
typedef  TYPE_7__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FFMIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* av_frame_clone (TYPE_5__*) ; 
 int /*<<< orphan*/  av_frame_copy_props (TYPE_5__*,TYPE_5__*) ; 
 int /*<<< orphan*/  av_rescale_q (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ff_filter_frame (TYPE_6__*,TYPE_5__*) ; 
 int /*<<< orphan*/  ff_filter_get_nb_threads (TYPE_7__*) ; 
 int ff_framesync_get_frame (TYPE_13__*,int,TYPE_5__**,int /*<<< orphan*/ ) ; 
 TYPE_5__* ff_get_video_buffer (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filter_slice ; 
 int /*<<< orphan*/  stub1 (TYPE_7__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int process_frame(FFFrameSync *fs)
{
    AVFilterContext *ctx = fs->parent;
    MaskedMergeContext *s = fs->opaque;
    AVFilterLink *outlink = ctx->outputs[0];
    AVFrame *out, *base, *overlay, *mask;
    ThreadData td;
    int ret;

    if ((ret = ff_framesync_get_frame(&s->fs, 0, &base,    0)) < 0 ||
        (ret = ff_framesync_get_frame(&s->fs, 1, &overlay, 0)) < 0 ||
        (ret = ff_framesync_get_frame(&s->fs, 2, &mask,    0)) < 0)
        return ret;

    if (ctx->is_disabled) {
        out = av_frame_clone(base);
        if (!out)
            return AVERROR(ENOMEM);
    } else {
        out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
        if (!out)
            return AVERROR(ENOMEM);
        av_frame_copy_props(out, base);

        td.out = out;
        td.base = base;
        td.overlay = overlay;
        td.mask = mask;
        ctx->internal->execute(ctx, filter_slice, &td, NULL,
                               FFMIN(s->height[2], ff_filter_get_nb_threads(ctx)));
    }
    out->pts = av_rescale_q(s->fs.pts, s->fs.time_base, outlink->time_base);

    return ff_filter_frame(outlink, out);
}