#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_8__ {TYPE_3__* out; TYPE_3__* in; } ;
typedef  TYPE_1__ ThreadData ;
struct TYPE_11__ {TYPE_2__* priv; } ;
struct TYPE_10__ {int width; int height; int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_9__ {int depth; int vsub; int hsub; } ;
typedef  TYPE_2__ SignalstatsContext ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  burn_frame16 (TYPE_2__ const*,TYPE_3__*,int,int) ; 

__attribute__((used)) static int filter16_brng(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    ThreadData *td = arg;
    const SignalstatsContext *s = ctx->priv;
    const AVFrame *in = td->in;
    AVFrame *out = td->out;
    const int mult = 1 << (s->depth - 8);
    const int w = in->width;
    const int h = in->height;
    const int slice_start = (h *  jobnr   ) / nb_jobs;
    const int slice_end   = (h * (jobnr+1)) / nb_jobs;
    int x, y, score = 0;

    for (y = slice_start; y < slice_end; y++) {
        const int yc = y >> s->vsub;
        const uint16_t *pluma    = (uint16_t *)&in->data[0][y  * in->linesize[0]];
        const uint16_t *pchromau = (uint16_t *)&in->data[1][yc * in->linesize[1]];
        const uint16_t *pchromav = (uint16_t *)&in->data[2][yc * in->linesize[2]];

        for (x = 0; x < w; x++) {
            const int xc = x >> s->hsub;
            const int luma    = pluma[x];
            const int chromau = pchromau[xc];
            const int chromav = pchromav[xc];
            const int filt = luma    < 16 * mult || luma    > 235 * mult ||
                chromau < 16 * mult || chromau > 240 * mult ||
                chromav < 16 * mult || chromav > 240 * mult;
            score += filt;
            if (out && filt)
                burn_frame16(s, out, x, y);
        }
    }
    return score;
}