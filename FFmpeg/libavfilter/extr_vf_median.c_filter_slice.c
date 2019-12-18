#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_3__* out; TYPE_3__* in; } ;
typedef  TYPE_1__ ThreadData ;
struct TYPE_10__ {TYPE_2__* priv; } ;
struct TYPE_9__ {int const* linesize; scalar_t__* data; } ;
struct TYPE_8__ {int nb_planes; int* planeheight; int* planewidth; int planes; int depth; int /*<<< orphan*/  (* filter_plane ) (TYPE_4__*,scalar_t__,int const,scalar_t__,int const,int const,int const,int const,int const,int) ;} ;
typedef  TYPE_2__ MedianContext ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_image_copy_plane (scalar_t__,int const,scalar_t__,int const,int const,int const) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,scalar_t__,int const,scalar_t__,int const,int const,int const,int const,int const,int) ; 

__attribute__((used)) static int filter_slice(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    MedianContext *s = ctx->priv;
    ThreadData *td = arg;
    AVFrame *in = td->in;
    AVFrame *out = td->out;

    for (int plane = 0; plane < s->nb_planes; plane++) {
        const int h = s->planeheight[plane];
        const int w = s->planewidth[plane];
        const int slice_h_start = (h * jobnr) / nb_jobs;
        const int slice_h_end = (h * (jobnr+1)) / nb_jobs;

        if (!(s->planes & (1 << plane))) {
            av_image_copy_plane(out->data[plane] + slice_h_start * out->linesize[plane],
                                out->linesize[plane],
                                in->data[plane] + slice_h_start * in->linesize[plane],
                                in->linesize[plane],
                                w * ((s->depth + 7) / 8),
                                slice_h_end - slice_h_start);
            continue;
        }

        s->filter_plane(ctx, in->data[plane],
                        in->linesize[plane],
                        out->data[plane] + slice_h_start * out->linesize[plane],
                        out->linesize[plane], w, h,
                        slice_h_start, slice_h_end, jobnr);
    }

    return 0;
}