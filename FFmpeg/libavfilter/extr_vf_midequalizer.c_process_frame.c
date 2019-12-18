#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {int /*<<< orphan*/  time_base; int /*<<< orphan*/  pts; } ;
struct TYPE_21__ {scalar_t__ is_disabled; TYPE_4__** outputs; } ;
struct TYPE_20__ {int /*<<< orphan*/  time_base; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct TYPE_19__ {int /*<<< orphan*/  pts; int /*<<< orphan*/ * linesize; int /*<<< orphan*/ * data; } ;
struct TYPE_18__ {TYPE_1__* opaque; TYPE_5__* parent; } ;
struct TYPE_17__ {int nb_planes; int planes; int** width; int histogram_size; TYPE_9__ fs; int /*<<< orphan*/  cchange; int /*<<< orphan*/ * histogram; int /*<<< orphan*/ ** height; int /*<<< orphan*/  (* midequalizer ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;
typedef  TYPE_1__ MidEqualizerContext ;
typedef  TYPE_2__ FFFrameSync ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFilterLink ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_3__* av_frame_clone (TYPE_3__*) ; 
 int /*<<< orphan*/  av_frame_copy_props (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  av_image_copy_plane (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_rescale_q (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ff_filter_frame (TYPE_4__*,TYPE_3__*) ; 
 int ff_framesync_get_frame (TYPE_9__*,int,TYPE_3__**,int /*<<< orphan*/ ) ; 
 TYPE_3__* ff_get_video_buffer (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int process_frame(FFFrameSync *fs)
{
    AVFilterContext *ctx = fs->parent;
    MidEqualizerContext *s = fs->opaque;
    AVFilterLink *outlink = ctx->outputs[0];
    AVFrame *out, *in0, *in1;
    int ret;

    if ((ret = ff_framesync_get_frame(&s->fs, 0, &in0, 0)) < 0 ||
        (ret = ff_framesync_get_frame(&s->fs, 1, &in1, 0)) < 0)
        return ret;

    if (ctx->is_disabled) {
        out = av_frame_clone(in0);
        if (!out)
            return AVERROR(ENOMEM);
    } else {
        int p;

        out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
        if (!out)
            return AVERROR(ENOMEM);
        av_frame_copy_props(out, in0);

        for (p = 0; p < s->nb_planes; p++) {
            if (!((1 << p) & s->planes)) {
                av_image_copy_plane(out->data[p], out->linesize[p], in0->data[p], in0->linesize[p],
                                    s->width[0][p] * (1 + (s->histogram_size > 256)), s->height[0][p]);
                continue;
            }

            s->midequalizer(in0->data[p], in1->data[p],
                            out->data[p],
                            in0->linesize[p], in1->linesize[p],
                            out->linesize[p],
                            s->width[0][p], s->height[0][p],
                            s->width[1][p], s->height[1][p],
                            s->histogram[0], s->histogram[1],
                            s->cchange, s->histogram_size);
        }
    }
    out->pts = av_rescale_q(s->fs.pts, s->fs.time_base, outlink->time_base);

    return ff_filter_frame(outlink, out);
}