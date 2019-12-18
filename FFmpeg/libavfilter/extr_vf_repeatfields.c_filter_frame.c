#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {TYPE_1__* priv; TYPE_3__** outputs; } ;
struct TYPE_18__ {TYPE_4__* dst; } ;
struct TYPE_17__ {int* linesize; scalar_t__* data; int /*<<< orphan*/  pts; int /*<<< orphan*/  repeat_pict; scalar_t__ top_field_first; } ;
struct TYPE_16__ {int state; int nb_planes; int* planeheight; int /*<<< orphan*/ * linesize; TYPE_2__* frame; } ;
typedef  TYPE_1__ RepeatFieldsContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_2__* av_frame_clone (TYPE_2__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 int /*<<< orphan*/  av_frame_make_writable (TYPE_2__*) ; 
 int /*<<< orphan*/  av_image_copy_plane (scalar_t__,int,scalar_t__,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int ff_filter_frame (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  update_pts (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in) {
    AVFilterContext *ctx = inlink->dst;
    AVFilterLink *outlink = inlink->dst->outputs[0];
    RepeatFieldsContext *s = ctx->priv;
    AVFrame *out;
    int ret, i;
    int state = s->state;

    if (!s->frame) {
        s->frame = av_frame_clone(in);
        if (!s->frame)
            return AVERROR(ENOMEM);
        s->frame->pts = AV_NOPTS_VALUE;
    }

    out = s->frame;

    if ((state == 0 && !in->top_field_first) ||
        (state == 1 &&  in->top_field_first)) {
        av_log(ctx, AV_LOG_WARNING, "Unexpected field flags: "
                                    "state=%d top_field_first=%d repeat_first_field=%d\n",
                                    state, in->top_field_first, in->repeat_pict);
        state ^= 1;
    }

    if (state == 0) {
        AVFrame *new;

        new = av_frame_clone(in);
        if (!new)
            return AVERROR(ENOMEM);

        ret = ff_filter_frame(outlink, new);

        if (in->repeat_pict) {
            av_frame_make_writable(out);
            update_pts(outlink, out, in->pts, 2);
            for (i = 0; i < s->nb_planes; i++) {
                av_image_copy_plane(out->data[i], out->linesize[i] * 2,
                                    in->data[i], in->linesize[i] * 2,
                                    s->linesize[i], s->planeheight[i] / 2);
            }
            state = 1;
        }
    } else {
        for (i = 0; i < s->nb_planes; i++) {
            av_frame_make_writable(out);
            av_image_copy_plane(out->data[i] + out->linesize[i], out->linesize[i] * 2,
                                in->data[i] + in->linesize[i], in->linesize[i] * 2,
                                s->linesize[i], s->planeheight[i] / 2);
        }

        ret = ff_filter_frame(outlink, av_frame_clone(out));

        if (in->repeat_pict) {
            AVFrame *new;

            new = av_frame_clone(in);
            if (!new)
                return AVERROR(ENOMEM);

            ret = ff_filter_frame(outlink, new);
            state = 0;
        } else {
            av_frame_make_writable(out);
            update_pts(outlink, out, in->pts, 1);
            for (i = 0; i < s->nb_planes; i++) {
                av_image_copy_plane(out->data[i], out->linesize[i] * 2,
                                    in->data[i], in->linesize[i] * 2,
                                    s->linesize[i], s->planeheight[i] / 2);
            }
        }
    }

    s->state = state;

    av_frame_free(&in);
    return ret;
}