#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_11__ ;

/* Type definitions */
struct TYPE_23__ {TYPE_6__** inputs; TYPE_6__** outputs; } ;
struct TYPE_22__ {int h; int /*<<< orphan*/  w; int /*<<< orphan*/  format; int /*<<< orphan*/  sample_aspect_ratio; int /*<<< orphan*/  time_base; } ;
struct TYPE_21__ {int* linesize; scalar_t__* data; int /*<<< orphan*/  sample_aspect_ratio; int /*<<< orphan*/  pts; } ;
struct TYPE_20__ {TYPE_3__* opaque; TYPE_7__* parent; } ;
struct TYPE_16__ {int /*<<< orphan*/  time_base; int /*<<< orphan*/  pts; } ;
struct TYPE_19__ {int nb_inputs; int nb_planes; TYPE_2__* items; scalar_t__ is_horizontal; scalar_t__ is_vertical; TYPE_1__* desc; TYPE_11__ fs; TYPE_5__** frames; } ;
struct TYPE_18__ {int* y; int* linesize; int* height; scalar_t__* x; } ;
struct TYPE_17__ {int /*<<< orphan*/  log2_chroma_h; } ;
typedef  TYPE_2__ StackItem ;
typedef  TYPE_3__ StackContext ;
typedef  TYPE_4__ FFFrameSync ;
typedef  TYPE_5__ AVFrame ;
typedef  TYPE_6__ AVFilterLink ;
typedef  TYPE_7__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_CEIL_RSHIFT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_frame_free (TYPE_5__**) ; 
 int /*<<< orphan*/  av_image_copy_plane (scalar_t__,int,scalar_t__,int,int,int) ; 
 int av_image_fill_linesizes (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_rescale_q (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ff_filter_frame (TYPE_6__*,TYPE_5__*) ; 
 int ff_framesync_get_frame (TYPE_11__*,int,TYPE_5__**,int /*<<< orphan*/ ) ; 
 TYPE_5__* ff_get_video_buffer (TYPE_6__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int process_frame(FFFrameSync *fs)
{
    AVFilterContext *ctx = fs->parent;
    AVFilterLink *outlink = ctx->outputs[0];
    StackContext *s = fs->opaque;
    AVFrame **in = s->frames;
    AVFrame *out;
    int i, p, ret, offset[4] = { 0 };

    for (i = 0; i < s->nb_inputs; i++) {
        if ((ret = ff_framesync_get_frame(&s->fs, i, &in[i], 0)) < 0)
            return ret;
    }

    out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
    if (!out)
        return AVERROR(ENOMEM);
    out->pts = av_rescale_q(s->fs.pts, s->fs.time_base, outlink->time_base);
    out->sample_aspect_ratio = outlink->sample_aspect_ratio;

    for (i = 0; i < s->nb_inputs; i++) {
        AVFilterLink *inlink = ctx->inputs[i];
        int linesize[4];
        int height[4];

        if (s->is_horizontal || s->is_vertical) {
            if ((ret = av_image_fill_linesizes(linesize, inlink->format, inlink->w)) < 0) {
                av_frame_free(&out);
                return ret;
            }

            height[1] = height[2] = AV_CEIL_RSHIFT(inlink->h, s->desc->log2_chroma_h);
            height[0] = height[3] = inlink->h;
        }

        for (p = 0; p < s->nb_planes; p++) {
            if (s->is_vertical) {
                av_image_copy_plane(out->data[p] + offset[p] * out->linesize[p],
                                    out->linesize[p],
                                    in[i]->data[p],
                                    in[i]->linesize[p],
                                    linesize[p], height[p]);
                offset[p] += height[p];
            } else if (s->is_horizontal) {
                av_image_copy_plane(out->data[p] + offset[p],
                                    out->linesize[p],
                                    in[i]->data[p],
                                    in[i]->linesize[p],
                                    linesize[p], height[p]);
                offset[p] += linesize[p];
            } else {
                StackItem *item = &s->items[i];

                av_image_copy_plane(out->data[p] + out->linesize[p] * item->y[p] + item->x[p],
                                    out->linesize[p],
                                    in[i]->data[p],
                                    in[i]->linesize[p],
                                    item->linesize[p], item->height[p]);
            }
        }
    }

    return ff_filter_frame(outlink, out);
}