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
struct TYPE_6__ {TYPE_3__* out; TYPE_3__* mask; TYPE_3__* overlay; TYPE_3__* base; } ;
typedef  TYPE_1__ ThreadData ;
struct TYPE_9__ {TYPE_2__* priv; } ;
struct TYPE_8__ {int const* linesize; scalar_t__* data; } ;
struct TYPE_7__ {int nb_planes; int* height; int planes; int /*<<< orphan*/  depth; int /*<<< orphan*/  half; int /*<<< orphan*/ * width; int /*<<< orphan*/  (* maskedmerge ) (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int const,int const,int const,int const,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * linesize; } ;
typedef  TYPE_2__ MaskedMergeContext ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_image_copy_plane (scalar_t__,int const,scalar_t__,int const,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int const,int const,int const,int const,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int filter_slice(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    MaskedMergeContext *s = ctx->priv;
    ThreadData *td = arg;
    AVFrame *base = td->base;
    AVFrame *overlay = td->overlay;
    AVFrame *mask = td->mask;
    AVFrame *out = td->out;
    int p;

    for (p = 0; p < s->nb_planes; p++) {
        const int h = s->height[p];
        const int slice_start = (h * jobnr) / nb_jobs;
        const int slice_end = (h * (jobnr+1)) / nb_jobs;

        if (!((1 << p) & s->planes)) {
            av_image_copy_plane(out->data[p] + slice_start * out->linesize[p],
                                out->linesize[p],
                                base->data[p] + slice_start * base->linesize[p],
                                base->linesize[p],
                                s->linesize[p], slice_end - slice_start);
            continue;
        }

        s->maskedmerge(base->data[p] + slice_start * base->linesize[p],
                       overlay->data[p] + slice_start * overlay->linesize[p],
                       mask->data[p] + slice_start * mask->linesize[p],
                       out->data[p] + slice_start * out->linesize[p],
                       base->linesize[p], overlay->linesize[p],
                       mask->linesize[p], out->linesize[p],
                       s->width[p], slice_end - slice_start,
                       s->half, s->depth);
    }

    return 0;
}