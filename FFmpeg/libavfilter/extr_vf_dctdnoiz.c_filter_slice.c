#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {float* src; float* dst; } ;
typedef  TYPE_1__ ThreadData ;
struct TYPE_8__ {TYPE_2__* priv; } ;
struct TYPE_7__ {int pr_width; int pr_height; int const bsize; int p_linesize; float* weights; float** slices; int step; int /*<<< orphan*/  (* filter_freq_func ) (TYPE_2__*,float const*,int const,float*,int const,int) ;} ;
typedef  TYPE_2__ DCTdnoizContext ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int FFMAX (int const,int /*<<< orphan*/ ) ; 
 int FFMIN (int const,int const) ; 
 int /*<<< orphan*/  memset (float*,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,float const*,int const,float*,int const,int) ; 

__attribute__((used)) static int filter_slice(AVFilterContext *ctx,
                        void *arg, int jobnr, int nb_jobs)
{
    int x, y;
    DCTdnoizContext *s = ctx->priv;
    const ThreadData *td = arg;
    const int w = s->pr_width;
    const int h = s->pr_height;
    const int slice_start = (h *  jobnr   ) / nb_jobs;
    const int slice_end   = (h * (jobnr+1)) / nb_jobs;
    const int slice_start_ctx = FFMAX(slice_start - s->bsize + 1, 0);
    const int slice_end_ctx   = FFMIN(slice_end, h - s->bsize + 1);
    const int slice_h = slice_end_ctx - slice_start_ctx;
    const int src_linesize   = s->p_linesize;
    const int dst_linesize   = s->p_linesize;
    const int slice_linesize = s->p_linesize;
    float *dst;
    const float *src = td->src + slice_start_ctx * src_linesize;
    const float *weights = s->weights + slice_start * dst_linesize;
    float *slice = s->slices[jobnr];

    // reset block sums
    memset(slice, 0, (slice_h + s->bsize - 1) * dst_linesize * sizeof(*slice));

    // block dct sums
    for (y = 0; y < slice_h; y += s->step) {
        for (x = 0; x < w - s->bsize + 1; x += s->step)
            s->filter_freq_func(s, src + x, src_linesize,
                                slice + x, slice_linesize,
                                jobnr);
        src += s->step * src_linesize;
        slice += s->step * slice_linesize;
    }

    // average blocks
    slice = s->slices[jobnr] + (slice_start - slice_start_ctx) * slice_linesize;
    dst = td->dst + slice_start * dst_linesize;
    for (y = slice_start; y < slice_end; y++) {
        for (x = 0; x < w; x++)
            dst[x] = slice[x] * weights[x];
        slice += slice_linesize;
        dst += dst_linesize;
        weights += dst_linesize;
    }

    return 0;
}