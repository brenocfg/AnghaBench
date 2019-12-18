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
struct TYPE_19__ {int plane; int /*<<< orphan*/  ref_linesize; int /*<<< orphan*/  ref; int /*<<< orphan*/  src_linesize; int /*<<< orphan*/  src; } ;
typedef  TYPE_2__ ThreadData ;
struct TYPE_23__ {TYPE_1__* internal; scalar_t__ is_disabled; TYPE_5__** outputs; TYPE_3__* priv; } ;
struct TYPE_22__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct TYPE_21__ {int /*<<< orphan*/ * linesize; int /*<<< orphan*/ * data; } ;
struct TYPE_20__ {int nb_planes; int* planeheight; int block_size; int planes; int /*<<< orphan*/  (* do_output ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int const) ;int /*<<< orphan*/ * planewidth; int /*<<< orphan*/  nb_threads; } ;
struct TYPE_18__ {int /*<<< orphan*/  (* execute ) (TYPE_6__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int const) ;} ;
typedef  TYPE_3__ BM3DContext ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVFilterLink ;
typedef  TYPE_6__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFMAX (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FFMIN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_frame_copy_props (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  av_image_copy_plane (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_4__* ff_get_video_buffer (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filter_slice ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int const) ; 

__attribute__((used)) static int filter_frame(AVFilterContext *ctx, AVFrame **out, AVFrame *in, AVFrame *ref)
{
    BM3DContext *s = ctx->priv;
    AVFilterLink *outlink = ctx->outputs[0];
    int p;

    *out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
    if (!*out)
        return AVERROR(ENOMEM);
    av_frame_copy_props(*out, in);

    for (p = 0; p < s->nb_planes; p++) {
        const int nb_jobs = FFMAX(1, FFMIN(s->nb_threads, s->planeheight[p] / s->block_size));
        ThreadData td;

        if (!((1 << p) & s->planes) || ctx->is_disabled) {
            av_image_copy_plane((*out)->data[p], (*out)->linesize[p],
                                in->data[p], in->linesize[p],
                                s->planewidth[p], s->planeheight[p]);
            continue;
        }

        td.src = in->data[p];
        td.src_linesize = in->linesize[p];
        td.ref = ref->data[p];
        td.ref_linesize = ref->linesize[p];
        td.plane = p;
        ctx->internal->execute(ctx, filter_slice, &td, NULL, nb_jobs);

        s->do_output(s, (*out)->data[p], (*out)->linesize[p], p, nb_jobs);
    }

    return 0;
}