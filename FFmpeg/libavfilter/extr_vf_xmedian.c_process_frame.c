#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_13__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  time_base; int /*<<< orphan*/  pts; } ;
struct TYPE_20__ {int nb_inputs; int /*<<< orphan*/ * height; int /*<<< orphan*/  median_frames; TYPE_13__ fs; TYPE_5__** frames; } ;
typedef  TYPE_2__ XMedianContext ;
struct TYPE_21__ {TYPE_5__* out; TYPE_5__** in; } ;
typedef  TYPE_3__ ThreadData ;
struct TYPE_25__ {TYPE_1__* internal; TYPE_6__** outputs; } ;
struct TYPE_24__ {int /*<<< orphan*/  time_base; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct TYPE_23__ {int /*<<< orphan*/  pts; } ;
struct TYPE_22__ {TYPE_2__* opaque; TYPE_7__* parent; } ;
struct TYPE_19__ {int /*<<< orphan*/  (* execute ) (TYPE_7__*,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_4__ FFFrameSync ;
typedef  TYPE_5__ AVFrame ;
typedef  TYPE_6__ AVFilterLink ;
typedef  TYPE_7__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FFMIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_rescale_q (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ff_filter_frame (TYPE_6__*,TYPE_5__*) ; 
 int /*<<< orphan*/  ff_filter_get_nb_threads (TYPE_7__*) ; 
 int ff_framesync_get_frame (TYPE_13__*,int,TYPE_5__**,int /*<<< orphan*/ ) ; 
 TYPE_5__* ff_get_video_buffer (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_7__*,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int process_frame(FFFrameSync *fs)
{
    AVFilterContext *ctx = fs->parent;
    AVFilterLink *outlink = ctx->outputs[0];
    XMedianContext *s = fs->opaque;
    AVFrame **in = s->frames;
    AVFrame *out;
    ThreadData td;
    int i, ret;

    for (i = 0; i < s->nb_inputs; i++) {
        if ((ret = ff_framesync_get_frame(&s->fs, i, &in[i], 0)) < 0)
            return ret;
    }

    out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
    if (!out)
        return AVERROR(ENOMEM);
    out->pts = av_rescale_q(s->fs.pts, s->fs.time_base, outlink->time_base);

    td.in = in;
    td.out = out;
    ctx->internal->execute(ctx, s->median_frames, &td, NULL, FFMIN(s->height[1], ff_filter_get_nb_threads(ctx)));

    return ff_filter_frame(outlink, out);
}