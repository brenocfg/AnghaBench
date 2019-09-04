#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {TYPE_4__** in; TYPE_4__* out; } ;
typedef  TYPE_2__ ThreadData ;
struct TYPE_24__ {TYPE_1__* internal; TYPE_3__* priv; TYPE_5__** outputs; } ;
struct TYPE_23__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_6__* dst; } ;
struct TYPE_22__ {int /*<<< orphan*/  pts; } ;
struct TYPE_21__ {size_t nb_frames; size_t nb_inputs; int /*<<< orphan*/ * height; TYPE_4__** frames; } ;
struct TYPE_19__ {int /*<<< orphan*/  (* execute ) (TYPE_6__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__ AmplifyContext ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVFilterLink ;
typedef  TYPE_6__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FFMIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amplify_frame ; 
 int /*<<< orphan*/  av_frame_free (TYPE_4__**) ; 
 int ff_filter_frame (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ff_filter_get_nb_threads (TYPE_6__*) ; 
 TYPE_4__* ff_get_video_buffer (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (TYPE_4__**,TYPE_4__**,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx = inlink->dst;
    AVFilterLink *outlink = ctx->outputs[0];
    AmplifyContext *s = ctx->priv;
    ThreadData td;
    AVFrame *out;

    if (s->nb_frames < s->nb_inputs) {
        s->frames[s->nb_frames] = in;
        s->nb_frames++;
        return 0;
    } else {
        av_frame_free(&s->frames[0]);
        memmove(&s->frames[0], &s->frames[1], sizeof(*s->frames) * (s->nb_inputs - 1));
        s->frames[s->nb_inputs - 1] = in;
    }

    out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
    if (!out)
        return AVERROR(ENOMEM);
    out->pts = s->frames[0]->pts;

    td.out = out;
    td.in = s->frames;
    ctx->internal->execute(ctx, amplify_frame, &td, NULL, FFMIN(s->height[1], ff_filter_get_nb_threads(ctx)));

    return ff_filter_frame(outlink, out);
}