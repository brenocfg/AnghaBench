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
typedef  size_t uint16_t ;
struct TYPE_6__ {TYPE_3__* out; TYPE_3__* in; } ;
typedef  TYPE_1__ ThreadData ;
struct TYPE_9__ {TYPE_2__* priv; } ;
struct TYPE_8__ {int height; int const* linesize; int width; scalar_t__* data; } ;
struct TYPE_7__ {size_t** lut; } ;
typedef  TYPE_2__ ColorBalanceContext ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 size_t B ; 
 size_t G ; 
 size_t R ; 

__attribute__((used)) static int apply_lut16_p(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    ColorBalanceContext *s = ctx->priv;
    ThreadData *td = arg;
    AVFrame *in = td->in;
    AVFrame *out = td->out;
    const int slice_start = (out->height * jobnr) / nb_jobs;
    const int slice_end = (out->height * (jobnr+1)) / nb_jobs;
    const uint16_t *srcg = (const uint16_t *)in->data[0] + slice_start * in->linesize[0] / 2;
    const uint16_t *srcb = (const uint16_t *)in->data[1] + slice_start * in->linesize[1] / 2;
    const uint16_t *srcr = (const uint16_t *)in->data[2] + slice_start * in->linesize[2] / 2;
    const uint16_t *srca = (const uint16_t *)in->data[3] + slice_start * in->linesize[3] / 2;
    uint16_t *dstg = (uint16_t *)out->data[0] + slice_start * out->linesize[0] / 2;
    uint16_t *dstb = (uint16_t *)out->data[1] + slice_start * out->linesize[1] / 2;
    uint16_t *dstr = (uint16_t *)out->data[2] + slice_start * out->linesize[2] / 2;
    uint16_t *dsta = (uint16_t *)out->data[3] + slice_start * out->linesize[3] / 2;
    int i, j;

    for (i = slice_start; i < slice_end; i++) {
        for (j = 0; j < out->width; j++) {
            dstg[j] = s->lut[G][srcg[j]];
            dstb[j] = s->lut[B][srcb[j]];
            dstr[j] = s->lut[R][srcr[j]];
            if (in != out && out->linesize[3])
                dsta[j] = srca[j];
        }

        srcg += in->linesize[0] / 2;
        srcb += in->linesize[1] / 2;
        srcr += in->linesize[2] / 2;
        srca += in->linesize[3] / 2;
        dstg += out->linesize[0] / 2;
        dstb += out->linesize[1] / 2;
        dstr += out->linesize[2] / 2;
        dsta += out->linesize[3] / 2;
    }

    return 0;
}