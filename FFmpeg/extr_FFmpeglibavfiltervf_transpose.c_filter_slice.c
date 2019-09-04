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
struct TYPE_7__ {int /*<<< orphan*/  (* transpose_block ) (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int,int) ;int /*<<< orphan*/  (* transpose_8x8 ) (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ;} ;
typedef  TYPE_1__ TransVtable ;
struct TYPE_8__ {int planes; int hsub; int vsub; int* pixsteps; int dir; TYPE_1__* vtables; } ;
typedef  TYPE_2__ TransContext ;
struct TYPE_9__ {TYPE_4__* in; TYPE_4__* out; } ;
typedef  TYPE_3__ ThreadData ;
struct TYPE_11__ {TYPE_2__* priv; } ;
struct TYPE_10__ {int* linesize; int /*<<< orphan*/ ** data; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int AV_CEIL_RSHIFT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int,int) ; 

__attribute__((used)) static int filter_slice(AVFilterContext *ctx, void *arg, int jobnr,
                        int nb_jobs)
{
    TransContext *s = ctx->priv;
    ThreadData *td = arg;
    AVFrame *out = td->out;
    AVFrame *in = td->in;
    int plane;

    for (plane = 0; plane < s->planes; plane++) {
        int hsub    = plane == 1 || plane == 2 ? s->hsub : 0;
        int vsub    = plane == 1 || plane == 2 ? s->vsub : 0;
        int pixstep = s->pixsteps[plane];
        int inh     = AV_CEIL_RSHIFT(in->height, vsub);
        int outw    = AV_CEIL_RSHIFT(out->width,  hsub);
        int outh    = AV_CEIL_RSHIFT(out->height, vsub);
        int start   = (outh *  jobnr   ) / nb_jobs;
        int end     = (outh * (jobnr+1)) / nb_jobs;
        uint8_t *dst, *src;
        int dstlinesize, srclinesize;
        int x, y;
        TransVtable *v = &s->vtables[plane];

        dstlinesize = out->linesize[plane];
        dst         = out->data[plane] + start * dstlinesize;
        src         = in->data[plane];
        srclinesize = in->linesize[plane];

        if (s->dir & 1) {
            src         += in->linesize[plane] * (inh - 1);
            srclinesize *= -1;
        }

        if (s->dir & 2) {
            dst          = out->data[plane] + dstlinesize * (outh - start - 1);
            dstlinesize *= -1;
        }

        for (y = start; y < end - 7; y += 8) {
            for (x = 0; x < outw - 7; x += 8) {
                v->transpose_8x8(src + x * srclinesize + y * pixstep,
                                 srclinesize,
                                 dst + (y - start) * dstlinesize + x * pixstep,
                                 dstlinesize);
            }
            if (outw - x > 0 && end - y > 0)
                v->transpose_block(src + x * srclinesize + y * pixstep,
                                   srclinesize,
                                   dst + (y - start) * dstlinesize + x * pixstep,
                                   dstlinesize, outw - x, end - y);
        }

        if (end - y > 0)
            v->transpose_block(src + 0 * srclinesize + y * pixstep,
                               srclinesize,
                               dst + (y - start) * dstlinesize + 0 * pixstep,
                               dstlinesize, outw, end - y);
    }

    return 0;
}