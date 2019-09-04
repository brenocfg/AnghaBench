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
struct TYPE_3__ {int linesize; int x_min; int mb_size; int x_max; int y_min; int y_max; scalar_t__ pred_y; scalar_t__ pred_x; scalar_t__* data_cur; scalar_t__* data_ref; } ;
typedef  TYPE_1__ AVMotionEstContext ;

/* Variables and functions */
 int COST_PRED_SCALE ; 
 int FFABS (scalar_t__) ; 
 int av_clip (int,int,int) ; 

__attribute__((used)) static uint64_t get_sad_ob(AVMotionEstContext *me_ctx, int x, int y, int x_mv, int y_mv)
{
    uint8_t *data_ref = me_ctx->data_ref;
    uint8_t *data_cur = me_ctx->data_cur;
    int linesize = me_ctx->linesize;
    int x_min = me_ctx->x_min + me_ctx->mb_size / 2;
    int x_max = me_ctx->x_max - me_ctx->mb_size / 2;
    int y_min = me_ctx->y_min + me_ctx->mb_size / 2;
    int y_max = me_ctx->y_max - me_ctx->mb_size / 2;
    int mv_x = x_mv - x;
    int mv_y = y_mv - y;
    int i, j;
    uint64_t sad = 0;

    x = av_clip(x, x_min, x_max);
    y = av_clip(y, y_min, y_max);
    x_mv = av_clip(x_mv, x_min, x_max);
    y_mv = av_clip(y_mv, y_min, y_max);

    for (j = -me_ctx->mb_size / 2; j < me_ctx->mb_size * 3 / 2; j++)
        for (i = -me_ctx->mb_size / 2; i < me_ctx->mb_size * 3 / 2; i++)
            sad += FFABS(data_ref[x_mv + i + (y_mv + j) * linesize] - data_cur[x + i + (y + j) * linesize]);

    return sad + (FFABS(mv_x - me_ctx->pred_x) + FFABS(mv_y - me_ctx->pred_y)) * COST_PRED_SCALE;
}