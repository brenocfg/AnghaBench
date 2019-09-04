#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {TYPE_4__* old; TYPE_4__* in; TYPE_4__* out; } ;
typedef  TYPE_2__ ThreadData ;
struct TYPE_23__ {TYPE_1__* internal; TYPE_3__* priv; TYPE_5__** outputs; } ;
struct TYPE_22__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_6__* dst; } ;
struct TYPE_21__ {int /*<<< orphan*/  pts; } ;
struct TYPE_20__ {TYPE_4__* old; int /*<<< orphan*/ * height; int /*<<< orphan*/  lagfun; } ;
struct TYPE_18__ {int /*<<< orphan*/  (* execute ) (TYPE_6__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__ LagfunContext ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVFilterLink ;
typedef  TYPE_6__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FFMIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* av_frame_clone (TYPE_4__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_4__**) ; 
 int ff_filter_frame (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ff_filter_get_nb_threads (TYPE_6__*) ; 
 TYPE_4__* ff_get_video_buffer (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx = inlink->dst;
    AVFilterLink *outlink = ctx->outputs[0];
    LagfunContext *s = ctx->priv;
    ThreadData td;
    AVFrame *out;

    if (!s->old) {
        s->old = av_frame_clone(in);
        return ff_filter_frame(outlink, in);
    }

    out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
    if (!out) {
        av_frame_free(&in);
        return AVERROR(ENOMEM);
    }
    out->pts = in->pts;

    td.out = out;
    td.in = in;
    td.old = s->old;
    ctx->internal->execute(ctx, s->lagfun, &td, NULL, FFMIN(s->height[1], ff_filter_get_nb_threads(ctx)));

    av_frame_free(&s->old);
    av_frame_free(&in);
    s->old = av_frame_clone(out);
    return ff_filter_frame(outlink, out);
}