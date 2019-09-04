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
typedef  size_t uint8_t ;
typedef  size_t uint16_t ;
struct TYPE_6__ {TYPE_3__* out; TYPE_3__* in; } ;
typedef  TYPE_1__ ThreadData ;
struct TYPE_9__ {TYPE_2__* priv; } ;
struct TYPE_8__ {int height; size_t** data; int* linesize; int width; } ;
struct TYPE_7__ {int step; size_t* rgba_map; size_t** graph; scalar_t__ is_16bit; } ;
typedef  TYPE_2__ CurvesContext ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 size_t A ; 
 size_t B ; 
 size_t G ; 
 size_t R ; 

__attribute__((used)) static int filter_slice_planar(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    int x, y;
    const CurvesContext *curves = ctx->priv;
    const ThreadData *td = arg;
    const AVFrame *in  = td->in;
    const AVFrame *out = td->out;
    const int direct = out == in;
    const int step = curves->step;
    const uint8_t r = curves->rgba_map[R];
    const uint8_t g = curves->rgba_map[G];
    const uint8_t b = curves->rgba_map[B];
    const uint8_t a = curves->rgba_map[A];
    const int slice_start = (in->height *  jobnr   ) / nb_jobs;
    const int slice_end   = (in->height * (jobnr+1)) / nb_jobs;

    if (curves->is_16bit) {
        for (y = slice_start; y < slice_end; y++) {
            uint16_t       *dstrp = (      uint16_t *)(out->data[r] + y * out->linesize[r]);
            uint16_t       *dstgp = (      uint16_t *)(out->data[g] + y * out->linesize[g]);
            uint16_t       *dstbp = (      uint16_t *)(out->data[b] + y * out->linesize[b]);
            uint16_t       *dstap = (      uint16_t *)(out->data[a] + y * out->linesize[a]);
            const uint16_t *srcrp = (const uint16_t *)(in ->data[r] + y *  in->linesize[r]);
            const uint16_t *srcgp = (const uint16_t *)(in ->data[g] + y *  in->linesize[g]);
            const uint16_t *srcbp = (const uint16_t *)(in ->data[b] + y *  in->linesize[b]);
            const uint16_t *srcap = (const uint16_t *)(in ->data[a] + y *  in->linesize[a]);

            for (x = 0; x < in->width; x++) {
                dstrp[x] = curves->graph[R][srcrp[x]];
                dstgp[x] = curves->graph[G][srcgp[x]];
                dstbp[x] = curves->graph[B][srcbp[x]];
                if (!direct && step == 4)
                    dstap[x] = srcap[x];
            }
        }
    } else {
        uint8_t       *dstr = out->data[r] + slice_start * out->linesize[r];
        uint8_t       *dstg = out->data[g] + slice_start * out->linesize[g];
        uint8_t       *dstb = out->data[b] + slice_start * out->linesize[b];
        uint8_t       *dsta = out->data[a] + slice_start * out->linesize[a];
        const uint8_t *srcr =  in->data[r] + slice_start *  in->linesize[r];
        const uint8_t *srcg =  in->data[g] + slice_start *  in->linesize[g];
        const uint8_t *srcb =  in->data[b] + slice_start *  in->linesize[b];
        const uint8_t *srca =  in->data[a] + slice_start *  in->linesize[a];

        for (y = slice_start; y < slice_end; y++) {
            for (x = 0; x < in->width; x++) {
                dstr[x] = curves->graph[R][srcr[x]];
                dstg[x] = curves->graph[G][srcg[x]];
                dstb[x] = curves->graph[B][srcb[x]];
                if (!direct && step == 4)
                    dsta[x] = srca[x];
            }
            dstr += out->linesize[r];
            dstg += out->linesize[g];
            dstb += out->linesize[b];
            dsta += out->linesize[a];
            srcr += in ->linesize[r];
            srcg += in ->linesize[g];
            srcb += in ->linesize[b];
            srca += in ->linesize[a];
        }
    }
    return 0;
}