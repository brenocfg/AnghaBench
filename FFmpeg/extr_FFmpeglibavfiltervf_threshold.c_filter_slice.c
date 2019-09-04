#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int nb_planes; int* height; int planes; int* width; int bpc; int /*<<< orphan*/  (* threshold ) (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int const,int const,int const,int const,int const,int,int const) ;} ;
typedef  TYPE_1__ ThresholdContext ;
struct TYPE_7__ {TYPE_3__* out; TYPE_3__* in; TYPE_3__* threshold; TYPE_3__* max; TYPE_3__* min; } ;
typedef  TYPE_2__ ThreadData ;
struct TYPE_9__ {TYPE_1__* priv; } ;
struct TYPE_8__ {int const* linesize; scalar_t__* data; } ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_image_copy_plane (scalar_t__,int const,scalar_t__,int const,int,int const) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int const,int const,int const,int const,int const,int,int const) ; 

__attribute__((used)) static int filter_slice(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    ThresholdContext *s = ctx->priv;
    ThreadData *td = arg;
    AVFrame *min = td->min;
    AVFrame *max = td->max;
    AVFrame *threshold = td->threshold;
    AVFrame *in = td->in;
    AVFrame *out = td->out;

    for (int p = 0; p < s->nb_planes; p++) {
        const int h = s->height[p];
        const int slice_start = (h * jobnr) / nb_jobs;
        const int slice_end = (h * (jobnr+1)) / nb_jobs;

        if (!(s->planes & (1 << p))) {
            av_image_copy_plane(out->data[p] + slice_start * out->linesize[p],
                                out->linesize[p],
                                in->data[p] + slice_start * in->linesize[p],
                                in->linesize[p],
                                s->width[p] * s->bpc,
                                slice_end - slice_start);
            continue;
        }
        s->threshold(in->data[p] + slice_start * in->linesize[p],
                     threshold->data[p] + slice_start * threshold->linesize[p],
                     min->data[p] + slice_start * min->linesize[p],
                     max->data[p] + slice_start * max->linesize[p],
                     out->data[p] + slice_start * out->linesize[p],
                     in->linesize[p], threshold->linesize[p],
                     min->linesize[p], max->linesize[p],
                     out->linesize[p],
                     s->width[p], slice_end - slice_start);
    }

    return 0;
}