#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_6__ {TYPE_2__* out; TYPE_2__* in; } ;
typedef  TYPE_1__ ThreadData ;
struct TYPE_8__ {int /*<<< orphan*/ * priv; } ;
struct TYPE_7__ {int width; int height; int* linesize; scalar_t__** data; } ;
typedef  int /*<<< orphan*/  SignalstatsContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int VREP_START ; 
 scalar_t__ abs (scalar_t__ const) ; 
 int /*<<< orphan*/  burn_frame8 (int /*<<< orphan*/  const*,TYPE_2__*,int,int) ; 

__attribute__((used)) static int filter8_vrep(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    ThreadData *td = arg;
    const SignalstatsContext *s = ctx->priv;
    const AVFrame *in = td->in;
    AVFrame *out = td->out;
    const int w = in->width;
    const int h = in->height;
    const int slice_start = (h *  jobnr   ) / nb_jobs;
    const int slice_end   = (h * (jobnr+1)) / nb_jobs;
    const uint8_t *p = in->data[0];
    const int lw = in->linesize[0];
    int x, y, score = 0;

    for (y = slice_start; y < slice_end; y++) {
        const int y2lw = (y - VREP_START) * lw;
        const int ylw  =  y               * lw;
        int filt, totdiff = 0;

        if (y < VREP_START)
            continue;

        for (x = 0; x < w; x++)
            totdiff += abs(p[y2lw + x] - p[ylw + x]);
        filt = totdiff < w;

        score += filt;
        if (filt && out)
            for (x = 0; x < w; x++)
                burn_frame8(s, out, x, y);
    }
    return score * w;
}