#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int ptrdiff_t ;
struct TYPE_13__ {TYPE_4__* dst; TYPE_3__* f2; TYPE_2__* f1; TYPE_1__* src; } ;
typedef  TYPE_5__ ThreadData ;
struct TYPE_15__ {TYPE_6__* priv; } ;
struct TYPE_14__ {int nb_planes; int* planewidth; int* planeheight; int planes; int /*<<< orphan*/  (* maskedminmax ) (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int const) ;int /*<<< orphan*/ * linesize; } ;
struct TYPE_12__ {int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_11__ {int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_10__ {int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_9__ {int* linesize; int /*<<< orphan*/ ** data; } ;
typedef  TYPE_6__ MaskedMinMaxContext ;
typedef  TYPE_7__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_image_copy_plane (int /*<<< orphan*/ *,int const,int /*<<< orphan*/  const*,int const,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int const) ; 

__attribute__((used)) static int maskedminmax_slice(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    MaskedMinMaxContext *s = ctx->priv;
    ThreadData *td = arg;

    for (int p = 0; p < s->nb_planes; p++) {
        const ptrdiff_t src_linesize = td->src->linesize[p];
        const ptrdiff_t f1_linesize = td->f1->linesize[p];
        const ptrdiff_t f2_linesize = td->f2->linesize[p];
        const ptrdiff_t dst_linesize = td->dst->linesize[p];
        const int w = s->planewidth[p];
        const int h = s->planeheight[p];
        const int slice_start = (h * jobnr) / nb_jobs;
        const int slice_end = (h * (jobnr+1)) / nb_jobs;
        const uint8_t *src = td->src->data[p] + slice_start * src_linesize;
        const uint8_t *f1 = td->f1->data[p] + slice_start * f1_linesize;
        const uint8_t *f2 = td->f2->data[p] + slice_start * f2_linesize;
        uint8_t *dst = td->dst->data[p] + slice_start * dst_linesize;

        if (!((1 << p) & s->planes)) {
            av_image_copy_plane(dst, dst_linesize, src, src_linesize,
                                s->linesize[p], slice_end - slice_start);
            continue;
        }

        for (int y = slice_start; y < slice_end; y++) {
            s->maskedminmax(src, dst, f1, f2, w);

            dst += dst_linesize;
            src += src_linesize;
            f1  += f1_linesize;
            f2  += f2_linesize;
        }
    }

    return 0;
}