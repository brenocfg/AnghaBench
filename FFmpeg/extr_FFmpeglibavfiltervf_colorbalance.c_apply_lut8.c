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
typedef  int uint8_t ;
struct TYPE_7__ {TYPE_3__* out; TYPE_3__* in; } ;
typedef  TYPE_1__ ThreadData ;
struct TYPE_11__ {TYPE_4__** outputs; TYPE_2__* priv; } ;
struct TYPE_10__ {int const w; } ;
struct TYPE_9__ {int height; int** data; int const* linesize; } ;
struct TYPE_8__ {int* rgba_map; int step; int** lut; } ;
typedef  TYPE_2__ ColorBalanceContext ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFilterLink ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 size_t A ; 
 size_t B ; 
 size_t G ; 
 size_t R ; 

__attribute__((used)) static int apply_lut8(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    ColorBalanceContext *s = ctx->priv;
    ThreadData *td = arg;
    AVFrame *in = td->in;
    AVFrame *out = td->out;
    AVFilterLink *outlink = ctx->outputs[0];
    const int slice_start = (out->height * jobnr) / nb_jobs;
    const int slice_end = (out->height * (jobnr+1)) / nb_jobs;
    const uint8_t *srcrow = in->data[0] + slice_start * in->linesize[0];
    const uint8_t roffset = s->rgba_map[R];
    const uint8_t goffset = s->rgba_map[G];
    const uint8_t boffset = s->rgba_map[B];
    const uint8_t aoffset = s->rgba_map[A];
    const int step = s->step;
    uint8_t *dstrow;
    int i, j;

    dstrow = out->data[0] + slice_start * out->linesize[0];
    for (i = slice_start; i < slice_end; i++) {
        const uint8_t *src = srcrow;
        uint8_t *dst = dstrow;

        for (j = 0; j < outlink->w * step; j += step) {
            dst[j + roffset] = s->lut[R][src[j + roffset]];
            dst[j + goffset] = s->lut[G][src[j + goffset]];
            dst[j + boffset] = s->lut[B][src[j + boffset]];
            if (in != out && step == 4)
                dst[j + aoffset] = src[j + aoffset];
        }

        srcrow += in->linesize[0];
        dstrow += out->linesize[0];
    }

    return 0;
}