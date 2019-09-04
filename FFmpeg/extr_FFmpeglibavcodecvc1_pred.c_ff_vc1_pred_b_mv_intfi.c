#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void**** motion_val; } ;
struct TYPE_8__ {scalar_t__* mb_type; int /*<<< orphan*/ *** motion_val; } ;
struct TYPE_10__ {int mb_x; int mb_y; int mb_stride; size_t* block_index; void**** mv; TYPE_1__ current_picture; int /*<<< orphan*/  quarter_sample; TYPE_2__ next_picture; } ;
struct TYPE_9__ {scalar_t__ bmvtype; int mb_off; size_t blocks_off; int** mv_f_next; int* ref_field_type; int cur_field_type; int** mv_f; int /*<<< orphan*/ * mb_type; int /*<<< orphan*/  range_y; int /*<<< orphan*/  range_x; int /*<<< orphan*/  bfraction; TYPE_4__ s; } ;
typedef  TYPE_3__ VC1Context ;
typedef  TYPE_4__ MpegEncContext ;

/* Variables and functions */
 scalar_t__ BMV_TYPE_BACKWARD ; 
 scalar_t__ BMV_TYPE_DIRECT ; 
 scalar_t__ BMV_TYPE_INTERPOLATED ; 
 scalar_t__ MB_TYPE_INTRA ; 
 int /*<<< orphan*/  ff_vc1_pred_mv (TYPE_3__*,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 void* scale_mv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void ff_vc1_pred_b_mv_intfi(VC1Context *v, int n, int *dmv_x, int *dmv_y,
                            int mv1, int *pred_flag)
{
    int dir = (v->bmvtype == BMV_TYPE_BACKWARD) ? 1 : 0;
    MpegEncContext *s = &v->s;
    int mb_pos = s->mb_x + s->mb_y * s->mb_stride;

    if (v->bmvtype == BMV_TYPE_DIRECT) {
        int total_opp, k, f;
        if (s->next_picture.mb_type[mb_pos + v->mb_off] != MB_TYPE_INTRA) {
            s->mv[0][0][0] = scale_mv(s->next_picture.motion_val[1][s->block_index[0] + v->blocks_off][0],
                                      v->bfraction, 0, s->quarter_sample);
            s->mv[0][0][1] = scale_mv(s->next_picture.motion_val[1][s->block_index[0] + v->blocks_off][1],
                                      v->bfraction, 0, s->quarter_sample);
            s->mv[1][0][0] = scale_mv(s->next_picture.motion_val[1][s->block_index[0] + v->blocks_off][0],
                                      v->bfraction, 1, s->quarter_sample);
            s->mv[1][0][1] = scale_mv(s->next_picture.motion_val[1][s->block_index[0] + v->blocks_off][1],
                                      v->bfraction, 1, s->quarter_sample);

            total_opp = v->mv_f_next[0][s->block_index[0] + v->blocks_off]
                      + v->mv_f_next[0][s->block_index[1] + v->blocks_off]
                      + v->mv_f_next[0][s->block_index[2] + v->blocks_off]
                      + v->mv_f_next[0][s->block_index[3] + v->blocks_off];
            f = (total_opp > 2) ? 1 : 0;
        } else {
            s->mv[0][0][0] = s->mv[0][0][1] = 0;
            s->mv[1][0][0] = s->mv[1][0][1] = 0;
            f = 0;
        }
        v->ref_field_type[0] = v->ref_field_type[1] = v->cur_field_type ^ f;
        for (k = 0; k < 4; k++) {
            s->current_picture.motion_val[0][s->block_index[k] + v->blocks_off][0] = s->mv[0][0][0];
            s->current_picture.motion_val[0][s->block_index[k] + v->blocks_off][1] = s->mv[0][0][1];
            s->current_picture.motion_val[1][s->block_index[k] + v->blocks_off][0] = s->mv[1][0][0];
            s->current_picture.motion_val[1][s->block_index[k] + v->blocks_off][1] = s->mv[1][0][1];
            v->mv_f[0][s->block_index[k] + v->blocks_off] = f;
            v->mv_f[1][s->block_index[k] + v->blocks_off] = f;
        }
        return;
    }
    if (v->bmvtype == BMV_TYPE_INTERPOLATED) {
        ff_vc1_pred_mv(v, 0, dmv_x[0], dmv_y[0],   1, v->range_x, v->range_y, v->mb_type[0], pred_flag[0], 0);
        ff_vc1_pred_mv(v, 0, dmv_x[1], dmv_y[1],   1, v->range_x, v->range_y, v->mb_type[0], pred_flag[1], 1);
        return;
    }
    if (dir) { // backward
        ff_vc1_pred_mv(v, n, dmv_x[1], dmv_y[1], mv1, v->range_x, v->range_y, v->mb_type[0], pred_flag[1], 1);
        if (n == 3 || mv1) {
            ff_vc1_pred_mv(v, 0, dmv_x[0], dmv_y[0],   1, v->range_x, v->range_y, v->mb_type[0], 0, 0);
        }
    } else { // forward
        ff_vc1_pred_mv(v, n, dmv_x[0], dmv_y[0], mv1, v->range_x, v->range_y, v->mb_type[0], pred_flag[0], 0);
        if (n == 3 || mv1) {
            ff_vc1_pred_mv(v, 0, dmv_x[1], dmv_y[1],   1, v->range_x, v->range_y, v->mb_type[0], 0, 1);
        }
    }
}