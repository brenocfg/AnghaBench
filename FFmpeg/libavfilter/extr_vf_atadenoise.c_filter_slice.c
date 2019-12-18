#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {TYPE_3__* out; TYPE_3__* in; } ;
typedef  TYPE_2__ ThreadData ;
struct TYPE_7__ {int /*<<< orphan*/  (* filter_row ) (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int const,int const,int const,int const,int const) ;} ;
struct TYPE_11__ {int size; int mid; int nb_planes; int* planeheight; int* planewidth; int* thra; int* thrb; int planes; TYPE_1__ dsp; scalar_t__* linesize; scalar_t__* data; } ;
struct TYPE_10__ {TYPE_5__* priv; } ;
struct TYPE_9__ {int const* linesize; int /*<<< orphan*/ ** data; } ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFilterContext ;
typedef  TYPE_5__ ATADenoiseContext ;

/* Variables and functions */
 int SIZE ; 
 int /*<<< orphan*/  av_image_copy_plane (int /*<<< orphan*/ *,int const,int /*<<< orphan*/  const*,int const,int const,int const) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int const,int const,int const,int const,int const) ; 

__attribute__((used)) static int filter_slice(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    ATADenoiseContext *s = ctx->priv;
    ThreadData *td = arg;
    AVFrame *in = td->in;
    AVFrame *out = td->out;
    const int size = s->size;
    const int mid = s->mid;
    int p, y, i;

    for (p = 0; p < s->nb_planes; p++) {
        const int h = s->planeheight[p];
        const int w = s->planewidth[p];
        const int slice_start = (h * jobnr) / nb_jobs;
        const int slice_end = (h * (jobnr+1)) / nb_jobs;
        const uint8_t *src = in->data[p] + slice_start * in->linesize[p];
        uint8_t *dst = out->data[p] + slice_start * out->linesize[p];
        const int thra = s->thra[p];
        const int thrb = s->thrb[p];
        const uint8_t **data = (const uint8_t **)s->data[p];
        const int *linesize = (const int *)s->linesize[p];
        const uint8_t *srcf[SIZE];

        if (!((1 << p) & s->planes)) {
            av_image_copy_plane(dst, out->linesize[p], src, in->linesize[p],
                                w, slice_end - slice_start);
            continue;
        }

        for (i = 0; i < size; i++)
            srcf[i] = data[i] + slice_start * linesize[i];

        for (y = slice_start; y < slice_end; y++) {
            s->dsp.filter_row(src, dst, srcf, w, mid, size, thra, thrb);

            dst += out->linesize[p];
            src += in->linesize[p];

            for (i = 0; i < size; i++)
                srcf[i] += linesize[i];
        }
    }

    return 0;
}