#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;
typedef  struct TYPE_27__   TYPE_18__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  value ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_31__ {TYPE_1__* priv; TYPE_3__** outputs; } ;
struct TYPE_30__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_4__* dst; } ;
struct TYPE_29__ {int /*<<< orphan*/ * metadata; int /*<<< orphan*/ * linesize; int /*<<< orphan*/ * data; } ;
struct TYPE_27__ {int available; } ;
struct TYPE_28__ {int size; float* luminance; size_t available; float (* calc_avgy ) (TYPE_4__*,TYPE_2__*) ;int bypass; int nb_planes; int* planewidth; int depth; TYPE_18__ q; int /*<<< orphan*/ * planeheight; int /*<<< orphan*/  (* deflicker ) (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float) ;int /*<<< orphan*/  (* get_factor ) (TYPE_4__*,float*) ;int /*<<< orphan*/  eof; } ;
typedef  TYPE_1__ DeflickerContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_frame_copy_props (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 int /*<<< orphan*/  av_image_copy_plane (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_bufqueue_add (TYPE_4__*,TYPE_18__*,TYPE_2__*) ; 
 TYPE_2__* ff_bufqueue_get (TYPE_18__*) ; 
 TYPE_2__* ff_bufqueue_peek (TYPE_18__*,int /*<<< orphan*/ ) ; 
 int ff_filter_frame (TYPE_3__*,TYPE_2__*) ; 
 TYPE_2__* ff_get_video_buffer (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (float*,float*,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ *,int,char*,float) ; 
 float stub1 (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,float*) ; 
 int /*<<< orphan*/  stub3 (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float) ; 
 float stub4 (TYPE_4__*,TYPE_2__*) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *buf)
{
    AVFilterContext *ctx = inlink->dst;
    AVFilterLink *outlink = ctx->outputs[0];
    DeflickerContext *s = ctx->priv;
    AVDictionary **metadata;
    AVFrame *out, *in;
    float f;
    int y;

    if (s->q.available < s->size && !s->eof) {
        s->luminance[s->available] = s->calc_avgy(ctx, buf);
        ff_bufqueue_add(ctx, &s->q, buf);
        s->available++;
        return 0;
    }

    in = ff_bufqueue_peek(&s->q, 0);

    out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
    if (!out) {
        av_frame_free(&buf);
        return AVERROR(ENOMEM);
    }

    s->get_factor(ctx, &f);
    if (!s->bypass)
        s->deflicker(ctx, in->data[0], in->linesize[0], out->data[0], out->linesize[0],
                     outlink->w, outlink->h, f);
    for (y = 1 - s->bypass; y < s->nb_planes; y++) {
        av_image_copy_plane(out->data[y], out->linesize[y],
                            in->data[y], in->linesize[y],
                            s->planewidth[y] * (1 + (s->depth > 8)), s->planeheight[y]);
    }

    av_frame_copy_props(out, in);
    metadata = &out->metadata;
    if (metadata) {
        uint8_t value[128];

        snprintf(value, sizeof(value), "%f", s->luminance[0]);
        av_dict_set(metadata, "lavfi.deflicker.luminance", value, 0);

        snprintf(value, sizeof(value), "%f", s->luminance[0] * f);
        av_dict_set(metadata, "lavfi.deflicker.new_luminance", value, 0);

        snprintf(value, sizeof(value), "%f", f - 1.0f);
        av_dict_set(metadata, "lavfi.deflicker.relative_change", value, 0);
    }

    in = ff_bufqueue_get(&s->q);
    av_frame_free(&in);
    memmove(&s->luminance[0], &s->luminance[1], sizeof(*s->luminance) * (s->size - 1));
    s->luminance[s->available - 1] = s->calc_avgy(ctx, buf);
    ff_bufqueue_add(ctx, &s->q, buf);

    return ff_filter_frame(outlink, out);
}