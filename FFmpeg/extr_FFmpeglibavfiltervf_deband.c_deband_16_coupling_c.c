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
typedef  int uint16_t ;
struct TYPE_6__ {TYPE_3__* out; TYPE_3__* in; } ;
typedef  TYPE_1__ ThreadData ;
struct TYPE_9__ {TYPE_2__* priv; } ;
struct TYPE_8__ {int* linesize; scalar_t__* data; } ;
struct TYPE_7__ {int* planeheight; int* planewidth; int* x_pos; int* y_pos; int nb_components; int* thr; scalar_t__ blur; } ;
typedef  TYPE_2__ DebandContext ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int const FFABS (int const) ; 
 int const av_clip (int,int /*<<< orphan*/ ,int const) ; 
 int get_avg (int const,int const,int const,int const) ; 

__attribute__((used)) static int deband_16_coupling_c(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    DebandContext *s = ctx->priv;
    ThreadData *td = arg;
    AVFrame *in = td->in;
    AVFrame *out = td->out;
    const int start = (s->planeheight[0] *  jobnr   ) / nb_jobs;
    const int end   = (s->planeheight[0] * (jobnr+1)) / nb_jobs;
    int x, y, p, z;

    for (y = start; y < end; y++) {
        const int pos = y * s->planewidth[0];

        for (x = 0; x < s->planewidth[0]; x++) {
            const int x_pos = s->x_pos[pos + x];
            const int y_pos = s->y_pos[pos + x];
            int avg[4], cmp[4] = { 0 }, src[4];

            for (p = 0; p < s->nb_components; p++) {
                const uint16_t *src_ptr = (const uint16_t *)in->data[p];
                const int src_linesize = in->linesize[p] / 2;
                const int thr = s->thr[p];
                const int w = s->planewidth[p] - 1;
                const int h = s->planeheight[p] - 1;
                const int ref0 = src_ptr[av_clip(y +  y_pos, 0, h) * src_linesize + av_clip(x +  x_pos, 0, w)];
                const int ref1 = src_ptr[av_clip(y + -y_pos, 0, h) * src_linesize + av_clip(x +  x_pos, 0, w)];
                const int ref2 = src_ptr[av_clip(y + -y_pos, 0, h) * src_linesize + av_clip(x + -x_pos, 0, w)];
                const int ref3 = src_ptr[av_clip(y +  y_pos, 0, h) * src_linesize + av_clip(x + -x_pos, 0, w)];
                const int src0 = src_ptr[y * src_linesize + x];

                src[p] = src0;
                avg[p] = get_avg(ref0, ref1, ref2, ref3);

                if (s->blur) {
                    cmp[p] = FFABS(src0 - avg[p]) < thr;
                } else {
                    cmp[p] = (FFABS(src0 - ref0) < thr) &&
                             (FFABS(src0 - ref1) < thr) &&
                             (FFABS(src0 - ref2) < thr) &&
                             (FFABS(src0 - ref3) < thr);
                }
            }

            for (z = 0; z < s->nb_components; z++)
                if (!cmp[z])
                    break;
            if (z == s->nb_components) {
                for (p = 0; p < s->nb_components; p++) {
                    const int dst_linesize = out->linesize[p] / 2;
                    uint16_t *dst = (uint16_t *)out->data[p] + y * dst_linesize + x;

                    dst[0] = avg[p];
                }
            } else {
                for (p = 0; p < s->nb_components; p++) {
                    const int dst_linesize = out->linesize[p] / 2;
                    uint16_t *dst = (uint16_t *)out->data[p] + y * dst_linesize + x;

                    dst[0] = src[p];
                }
            }
        }
    }

    return 0;
}