#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_3__ {int linesize; int mb_size; scalar_t__ pred_y; scalar_t__ pred_x; scalar_t__ y_max; scalar_t__ y_min; scalar_t__ x_max; scalar_t__ x_min; scalar_t__* data_ref; scalar_t__* data_cur; } ;
typedef  TYPE_1__ AVMotionEstContext ;

/* Variables and functions */
 int COST_PRED_SCALE ; 
 int FFABS (scalar_t__) ; 
 scalar_t__ FFMIN (scalar_t__,scalar_t__) ; 
 int av_clip (int,scalar_t__,scalar_t__) ; 

__attribute__((used)) static uint64_t get_sbad(AVMotionEstContext *me_ctx, int x, int y, int x_mv, int y_mv)
{
    uint8_t *data_cur = me_ctx->data_cur;
    uint8_t *data_next = me_ctx->data_ref;
    int linesize = me_ctx->linesize;
    int mv_x1 = x_mv - x;
    int mv_y1 = y_mv - y;
    int mv_x, mv_y, i, j;
    uint64_t sbad = 0;

    x = av_clip(x, me_ctx->x_min, me_ctx->x_max);
    y = av_clip(y, me_ctx->y_min, me_ctx->y_max);
    mv_x = av_clip(x_mv - x, -FFMIN(x - me_ctx->x_min, me_ctx->x_max - x), FFMIN(x - me_ctx->x_min, me_ctx->x_max - x));
    mv_y = av_clip(y_mv - y, -FFMIN(y - me_ctx->y_min, me_ctx->y_max - y), FFMIN(y - me_ctx->y_min, me_ctx->y_max - y));

    data_cur += (y + mv_y) * linesize;
    data_next += (y - mv_y) * linesize;

    for (j = 0; j < me_ctx->mb_size; j++)
        for (i = 0; i < me_ctx->mb_size; i++)
            sbad += FFABS(data_cur[x + mv_x + i + j * linesize] - data_next[x - mv_x + i + j * linesize]);

    return sbad + (FFABS(mv_x1 - me_ctx->pred_x) + FFABS(mv_y1 - me_ctx->pred_y)) * COST_PRED_SCALE;
}