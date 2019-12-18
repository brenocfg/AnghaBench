#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int first_field; int nb_planes; TYPE_2__* prev; scalar_t__ double_weave; int /*<<< orphan*/ * planeheight; int /*<<< orphan*/ * linesize; } ;
typedef  TYPE_1__ WeaveContext ;
struct TYPE_17__ {TYPE_3__** outputs; TYPE_1__* priv; } ;
struct TYPE_16__ {int frame_count_out; int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_4__* dst; } ;
struct TYPE_15__ {int* linesize; int pts; int interlaced_frame; int top_field_first; scalar_t__* data; } ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_frame_copy_props (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 int /*<<< orphan*/  av_image_copy_plane (scalar_t__,int,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ff_filter_frame (TYPE_3__*,TYPE_2__*) ; 
 TYPE_2__* ff_get_video_buffer (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx = inlink->dst;
    WeaveContext *s = ctx->priv;
    AVFilterLink *outlink = ctx->outputs[0];
    AVFrame *out;
    int i;
    int weave;
    int field1, field2;

    if (!s->prev) {
        s->prev = in;
        return 0;
    }

    out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
    if (!out) {
        av_frame_free(&in);
        av_frame_free(&s->prev);
        return AVERROR(ENOMEM);
    }
    av_frame_copy_props(out, in);

    weave = (s->double_weave && !(inlink->frame_count_out & 1));
    field1 = weave ? s->first_field : (!s->first_field);
    field2 = weave ? (!s->first_field) : s->first_field;
    for (i = 0; i < s->nb_planes; i++) {
        av_image_copy_plane(out->data[i] + out->linesize[i] * field1,
                            out->linesize[i] * 2,
                            in->data[i], in->linesize[i],
                            s->linesize[i], s->planeheight[i]);
        av_image_copy_plane(out->data[i] + out->linesize[i] * field2,
                            out->linesize[i] * 2,
                            s->prev->data[i], s->prev->linesize[i],
                            s->linesize[i], s->planeheight[i]);
    }

    out->pts = s->double_weave ? s->prev->pts : in->pts / 2;
    out->interlaced_frame = 1;
    out->top_field_first = !s->first_field;

    if (!s->double_weave)
        av_frame_free(&in);
    av_frame_free(&s->prev);
    if (s->double_weave)
        s->prev = in;
    return ff_filter_frame(outlink, out);
}