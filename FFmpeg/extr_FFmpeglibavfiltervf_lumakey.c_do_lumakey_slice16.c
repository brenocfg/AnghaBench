#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_7__ {TYPE_1__* priv; } ;
struct TYPE_6__ {int height; int const* linesize; int width; scalar_t__* data; } ;
struct TYPE_5__ {int softness; int white; int black; int max; } ;
typedef  TYPE_1__ LumakeyContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */

__attribute__((used)) static int do_lumakey_slice16(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    LumakeyContext *s = ctx->priv;
    AVFrame *frame = arg;
    const int slice_start = (frame->height * jobnr) / nb_jobs;
    const int slice_end = (frame->height * (jobnr + 1)) / nb_jobs;
    uint16_t *alpha = (uint16_t *)(frame->data[3] + slice_start * frame->linesize[3]);
    const uint16_t *luma = (const uint16_t *)(frame->data[0] + slice_start * frame->linesize[0]);
    const int so = s->softness;
    const int w = s->white;
    const int b = s->black;
    const int m = s->max;
    int x, y;

    for (y = slice_start; y < slice_end; y++) {
        for (x = 0; x < frame->width; x++) {
            if (luma[x] >= b && luma[x] <= w) {
                alpha[x] = 0;
            } else if (luma[x] > b - so && luma[x] < w + so) {
                if (luma[x] < b) {
                    alpha[x] = m - (luma[x] - b + so) * m / so;
                } else {
                    alpha[x] = (luma[x] - w) * m / so;
                }
            }
        }
        luma += frame->linesize[0] / 2;
        alpha += frame->linesize[3] / 2;
    }

    return 0;
}