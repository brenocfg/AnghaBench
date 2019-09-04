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
typedef  int uint8_t ;
struct TYPE_7__ {TYPE_1__* priv; } ;
struct TYPE_6__ {int** data; int* linesize; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_5__ {int factor; int /*<<< orphan*/  vsub; int /*<<< orphan*/  hsub; } ;
typedef  TYPE_1__ FadeContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int AV_CEIL_RSHIFT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FFMIN (int const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int filter_slice_chroma(AVFilterContext *ctx, void *arg, int jobnr,
                               int nb_jobs)
{
    FadeContext *s = ctx->priv;
    AVFrame *frame = arg;
    int i, j, plane;
    const int width = AV_CEIL_RSHIFT(frame->width, s->hsub);
    const int height= AV_CEIL_RSHIFT(frame->height, s->vsub);
    int slice_start = (height *  jobnr   ) / nb_jobs;
    int slice_end   = FFMIN(((height * (jobnr+1)) / nb_jobs), frame->height);

    for (plane = 1; plane < 3; plane++) {
        for (i = slice_start; i < slice_end; i++) {
            uint8_t *p = frame->data[plane] + i * frame->linesize[plane];
            for (j = 0; j < width; j++) {
                /* 8421367 = ((128 << 1) + 1) << 15. It is an integer
                 * representation of 128.5. The .5 is for rounding
                 * purposes. */
                *p = ((*p - 128) * s->factor + 8421367) >> 16;
                p++;
            }
        }
    }

    return 0;
}