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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_20__ {int plane; TYPE_4__* out; TYPE_4__* in; } ;
typedef  TYPE_2__ ThreadData ;
struct TYPE_24__ {TYPE_1__* internal; TYPE_3__* priv; TYPE_5__** outputs; } ;
struct TYPE_23__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_6__* dst; } ;
struct TYPE_22__ {int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_21__ {int nb_planes; scalar_t__* mode; int /*<<< orphan*/ * planewidth; int /*<<< orphan*/ * planeheight; } ;
struct TYPE_19__ {int /*<<< orphan*/  (* execute ) (TYPE_6__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__ RemoveGrainContext ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVFilterLink ;
typedef  TYPE_6__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FFMIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_frame_copy_props (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_4__**) ; 
 int /*<<< orphan*/  av_image_copy_plane (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ff_filter_frame (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ff_filter_get_nb_threads (TYPE_6__*) ; 
 TYPE_4__* ff_get_video_buffer (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filter_slice ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx = inlink->dst;
    AVFilterLink *outlink = ctx->outputs[0];
    RemoveGrainContext *s = ctx->priv;
    ThreadData td;
    AVFrame *out;
    int i;

    out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
    if (!out) {
        av_frame_free(&in);
        return AVERROR(ENOMEM);
    }
    av_frame_copy_props(out, in);

    for (i = 0; i < s->nb_planes; i++) {
        uint8_t *dst = out->data[i];
        uint8_t *src = in->data[i];

        if (s->mode[i] == 0) {
            av_image_copy_plane(dst, out->linesize[i],
                                src, in->linesize[i],
                                s->planewidth[i], s->planeheight[i]);
            continue;
        }

        memcpy(dst, src, s->planewidth[i]);

        td.in = in; td.out = out; td.plane = i;
        ctx->internal->execute(ctx, filter_slice, &td, NULL,
                               FFMIN(s->planeheight[i], ff_filter_get_nb_threads(ctx)));

        src = in->data[i] + (s->planeheight[i] - 1) * in->linesize[i];
        dst = out->data[i] + (s->planeheight[i] - 1) * out->linesize[i];
        memcpy(dst, src, s->planewidth[i]);
    }

    av_frame_free(&in);
    return ff_filter_frame(outlink, out);
}