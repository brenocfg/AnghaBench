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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {TYPE_3__* in; TYPE_3__* out; } ;
typedef  TYPE_1__ ThreadData ;
struct TYPE_9__ {TYPE_2__* priv; } ;
struct TYPE_8__ {int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_7__ {int nb_planes; int bpc; int* threshold; int* planeheight; int* planewidth; int /*<<< orphan*/  max; int /*<<< orphan*/  coordinates; int /*<<< orphan*/  (* filter ) (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int const,int /*<<< orphan*/  const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ NContext ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_image_copy_plane (int /*<<< orphan*/ *,int const,int /*<<< orphan*/  const*,int const,int const,int const) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int const,int /*<<< orphan*/  const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int const,int const,int /*<<< orphan*/  const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int const,int /*<<< orphan*/  const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int filter_slice(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    NContext *s = ctx->priv;
    ThreadData *td = arg;
    AVFrame *out = td->out;
    AVFrame *in = td->in;
    int plane, y;

    for (plane = 0; plane < s->nb_planes; plane++) {
        const int bpc = s->bpc;
        const int threshold = s->threshold[plane];
        const int stride = in->linesize[plane];
        const int dstride = out->linesize[plane];
        const int height = s->planeheight[plane];
        const int width  = s->planewidth[plane];
        const int slice_start = (height * jobnr) / nb_jobs;
        const int slice_end = (height * (jobnr+1)) / nb_jobs;
        const uint8_t *src = (const uint8_t *)in->data[plane] + slice_start * stride;
        uint8_t *dst = out->data[plane] + slice_start * dstride;

        if (!threshold) {
            av_image_copy_plane(dst, dstride, src, stride, width * bpc, slice_end - slice_start);
            continue;
        }

        for (y = slice_start; y < slice_end; y++) {
            const int nh = y > 0;
            const int ph = y < height - 1;
            const uint8_t *coordinates[] = { src - nh * stride, src + 1 * bpc - nh * stride, src + 2 * bpc - nh * stride,
                                             src,                                            src + 2 * bpc,
                                             src + ph * stride, src + 1 * bpc + ph * stride, src + 2 * bpc + ph * stride};

            const uint8_t *coordinateslb[] = { src + 1 * bpc - nh * stride, src - nh * stride, src + 1 * bpc - nh * stride,
                                               src + 1 * bpc,                                  src + 1 * bpc,
                                               src + 1 * bpc + ph * stride, src + ph * stride, src + 1 * bpc + ph * stride};

            const uint8_t *coordinatesrb[] = { src + (width - 2) * bpc - nh * stride, src + (width - 1) * bpc - nh * stride, src + (width - 2) * bpc - nh * stride,
                                               src + (width - 2) * bpc,                                                      src + (width - 2) * bpc,
                                               src + (width - 2) * bpc + ph * stride, src + (width - 1) * bpc + ph * stride, src + (width - 2) * bpc + ph * stride};

            s->filter(dst,                         src,                     1,         threshold, coordinateslb, s->coordinates, s->max);
            if (width > 1) {
                s->filter(dst          + 1  * bpc, src          + 1  * bpc, width - 2, threshold, coordinates,   s->coordinates, s->max);
                s->filter(dst + (width - 1) * bpc, src + (width - 1) * bpc, 1,         threshold, coordinatesrb, s->coordinates, s->max);
            }

            src += stride;
            dst += dstride;
        }
    }

    return 0;
}