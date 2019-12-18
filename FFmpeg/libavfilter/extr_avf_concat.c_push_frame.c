#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct concat_in {int nb_frames; scalar_t__ pts; } ;
struct TYPE_12__ {unsigned int nb_outputs; TYPE_3__** outputs; TYPE_3__** inputs; TYPE_1__* priv; } ;
struct TYPE_11__ {int /*<<< orphan*/  time_base; scalar_t__ sample_rate; } ;
struct TYPE_10__ {scalar_t__ pts; scalar_t__ nb_samples; } ;
struct TYPE_9__ {scalar_t__ delta_ts; struct concat_in* in; } ;
typedef  TYPE_1__ ConcatContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_make_q (int,scalar_t__) ; 
 scalar_t__ av_rescale (scalar_t__,int,int) ; 
 scalar_t__ av_rescale_q (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ff_filter_frame (TYPE_3__*,TYPE_2__*) ; 

__attribute__((used)) static int push_frame(AVFilterContext *ctx, unsigned in_no, AVFrame *buf)
{
    ConcatContext *cat = ctx->priv;
    unsigned out_no = in_no % ctx->nb_outputs;
    AVFilterLink * inlink = ctx-> inputs[ in_no];
    AVFilterLink *outlink = ctx->outputs[out_no];
    struct concat_in *in = &cat->in[in_no];

    buf->pts = av_rescale_q(buf->pts, inlink->time_base, outlink->time_base);
    in->pts = buf->pts;
    in->nb_frames++;
    /* add duration to input PTS */
    if (inlink->sample_rate)
        /* use number of audio samples */
        in->pts += av_rescale_q(buf->nb_samples,
                                av_make_q(1, inlink->sample_rate),
                                outlink->time_base);
    else if (in->nb_frames >= 2)
        /* use mean duration */
        in->pts = av_rescale(in->pts, in->nb_frames, in->nb_frames - 1);

    buf->pts += cat->delta_ts;
    return ff_filter_frame(outlink, buf);
}