#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int ptrdiff_t ;
struct TYPE_15__ {TYPE_4__* d; TYPE_3__* m; TYPE_2__* o; TYPE_1__* b; } ;
typedef  TYPE_6__ ThreadData ;
struct TYPE_17__ {TYPE_7__* priv; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* maskedclamp ) (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int const,int const,int const) ;} ;
struct TYPE_16__ {int nb_planes; int* width; int* height; int undershoot; int overshoot; int planes; TYPE_5__ dsp; int /*<<< orphan*/ * linesize; } ;
struct TYPE_13__ {int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_12__ {int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_11__ {int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_10__ {int* linesize; int /*<<< orphan*/ ** data; } ;
typedef  TYPE_7__ MaskedClampContext ;
typedef  TYPE_8__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_image_copy_plane (int /*<<< orphan*/ *,int const,int /*<<< orphan*/  const*,int const,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int const,int const,int const) ; 

__attribute__((used)) static int maskedclamp_slice(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    MaskedClampContext *s = ctx->priv;
    ThreadData *td = arg;
    int p;

    for (p = 0; p < s->nb_planes; p++) {
        const ptrdiff_t blinesize = td->b->linesize[p];
        const ptrdiff_t brightlinesize = td->m->linesize[p];
        const ptrdiff_t darklinesize = td->o->linesize[p];
        const ptrdiff_t dlinesize = td->d->linesize[p];
        const int w = s->width[p];
        const int h = s->height[p];
        const int slice_start = (h * jobnr) / nb_jobs;
        const int slice_end = (h * (jobnr+1)) / nb_jobs;
        const uint8_t *bsrc = td->b->data[p] + slice_start * blinesize;
        const uint8_t *darksrc = td->o->data[p] + slice_start * darklinesize;
        const uint8_t *brightsrc = td->m->data[p] + slice_start * brightlinesize;
        uint8_t *dst = td->d->data[p] + slice_start * dlinesize;
        const int undershoot = s->undershoot;
        const int overshoot = s->overshoot;
        int y;

        if (!((1 << p) & s->planes)) {
            av_image_copy_plane(dst, dlinesize, bsrc, blinesize,
                                s->linesize[p], slice_end - slice_start);
            continue;
        }

        for (y = slice_start; y < slice_end; y++) {
            s->dsp.maskedclamp(bsrc, dst, darksrc, brightsrc, w, undershoot, overshoot);

            dst  += dlinesize;
            bsrc += blinesize;
            darksrc += darklinesize;
            brightsrc += brightlinesize;
        }
    }

    return 0;
}