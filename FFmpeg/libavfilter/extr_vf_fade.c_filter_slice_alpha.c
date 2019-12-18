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
struct TYPE_6__ {int height; int** data; int* linesize; int width; } ;
struct TYPE_5__ {int is_packed_rgb; int* rgba_map; int black_level; int factor; int black_level_scaled; } ;
typedef  TYPE_1__ FadeContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 size_t A ; 

__attribute__((used)) static int filter_slice_alpha(AVFilterContext *ctx, void *arg, int jobnr,
                              int nb_jobs)
{
    FadeContext *s = ctx->priv;
    AVFrame *frame = arg;
    int plane = s->is_packed_rgb ? 0 : A;
    int slice_start = (frame->height *  jobnr   ) / nb_jobs;
    int slice_end   = (frame->height * (jobnr+1)) / nb_jobs;
    int i, j;

    for (i = slice_start; i < slice_end; i++) {
        uint8_t *p = frame->data[plane] + i * frame->linesize[plane] + s->is_packed_rgb*s->rgba_map[A];
        int step = s->is_packed_rgb ? 4 : 1;
        for (j = 0; j < frame->width; j++) {
            /* s->factor is using 16 lower-order bits for decimal
             * places. 32768 = 1 << 15, it is an integer representation
             * of 0.5 and is for rounding. */
            *p = ((*p - s->black_level) * s->factor + s->black_level_scaled) >> 16;
            p += step;
        }
    }

    return 0;
}