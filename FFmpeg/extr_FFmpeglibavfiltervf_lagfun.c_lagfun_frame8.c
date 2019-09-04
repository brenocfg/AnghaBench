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
typedef  float uint8_t ;
struct TYPE_6__ {TYPE_3__* old; TYPE_3__* out; TYPE_3__* in; } ;
typedef  TYPE_1__ ThreadData ;
struct TYPE_9__ {TYPE_2__* priv; } ;
struct TYPE_8__ {float** data; int const* linesize; } ;
struct TYPE_7__ {float decay; int nb_planes; int* height; int planes; int* linesize; } ;
typedef  TYPE_2__ LagfunContext ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 float FFMAX (float const,float const) ; 
 int /*<<< orphan*/  av_image_copy_plane (float*,int const,float const*,int const,int,int const) ; 

__attribute__((used)) static int lagfun_frame8(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    LagfunContext *s = ctx->priv;
    const float decay = s->decay;
    ThreadData *td = arg;
    AVFrame *in = td->in;
    AVFrame *out = td->out;
    AVFrame *old = td->old;

    for (int p = 0; p < s->nb_planes; p++) {
        const int slice_start = (s->height[p] * jobnr) / nb_jobs;
        const int slice_end = (s->height[p] * (jobnr+1)) / nb_jobs;
        const uint8_t *src = in->data[p] + slice_start * in->linesize[p];
        const uint8_t *osrc = old->data[p] + slice_start * old->linesize[p];
        uint8_t *dst = out->data[p] + slice_start * out->linesize[p];

        if (!((1 << p) & s->planes)) {
            av_image_copy_plane(dst, out->linesize[p],
                                src, in->linesize[p],
                                s->linesize[p], slice_end - slice_start);
            continue;
        }

        for (int y = slice_start; y < slice_end; y++) {
            for (int x = 0; x < s->linesize[p]; x++)
                dst[x] = FFMAX(src[x], osrc[x] * decay);

            src += in->linesize[p];
            osrc += old->linesize[p];
            dst += out->linesize[p];
        }
    }

    return 0;
}