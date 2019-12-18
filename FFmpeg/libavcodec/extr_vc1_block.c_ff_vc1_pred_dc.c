#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int int16_t ;
struct TYPE_4__ {int /*<<< orphan*/ * qscale_table; } ;
struct TYPE_5__ {int mb_x; int mb_y; int mb_stride; int* y_dc_scale_table; int* block_wrap; int** dc_val; int* block_index; TYPE_1__ current_picture; } ;
typedef  TYPE_2__ MpegEncContext ;

/* Variables and functions */
 int FFABS (int /*<<< orphan*/ ) ; 
 scalar_t__ abs (int) ; 
 unsigned int* ff_vc1_dqscale ; 

__attribute__((used)) static inline int ff_vc1_pred_dc(MpegEncContext *s, int overlap, int pq, int n,
                              int a_avail, int c_avail,
                              int16_t **dc_val_ptr, int *dir_ptr)
{
    int a, b, c, wrap, pred;
    int16_t *dc_val;
    int mb_pos = s->mb_x + s->mb_y * s->mb_stride;
    int q1, q2 = 0;
    int dqscale_index;

    /* scale predictors if needed */
    q1 = FFABS(s->current_picture.qscale_table[mb_pos]);
    dqscale_index = s->y_dc_scale_table[q1] - 1;
    if (dqscale_index < 0)
        return 0;

    wrap = s->block_wrap[n];
    dc_val = s->dc_val[0] + s->block_index[n];

    /* B A
     * C X
     */
    c = dc_val[ - 1];
    b = dc_val[ - 1 - wrap];
    a = dc_val[ - wrap];

    if (c_avail && (n != 1 && n != 3)) {
        q2 = FFABS(s->current_picture.qscale_table[mb_pos - 1]);
        if (q2 && q2 != q1)
            c = (int)((unsigned)c * s->y_dc_scale_table[q2] * ff_vc1_dqscale[dqscale_index] + 0x20000) >> 18;
    }
    if (a_avail && (n != 2 && n != 3)) {
        q2 = FFABS(s->current_picture.qscale_table[mb_pos - s->mb_stride]);
        if (q2 && q2 != q1)
            a = (int)((unsigned)a * s->y_dc_scale_table[q2] * ff_vc1_dqscale[dqscale_index] + 0x20000) >> 18;
    }
    if (a_avail && c_avail && (n != 3)) {
        int off = mb_pos;
        if (n != 1)
            off--;
        if (n != 2)
            off -= s->mb_stride;
        q2 = FFABS(s->current_picture.qscale_table[off]);
        if (q2 && q2 != q1)
            b = (int)((unsigned)b * s->y_dc_scale_table[q2] * ff_vc1_dqscale[dqscale_index] + 0x20000) >> 18;
    }

    if (c_avail && (!a_avail || abs(a - b) <= abs(b - c))) {
        pred     = c;
        *dir_ptr = 1; // left
    } else if (a_avail) {
        pred     = a;
        *dir_ptr = 0; // top
    } else {
        pred     = 0;
        *dir_ptr = 1; // left
    }

    /* update predictor */
    *dc_val_ptr = &dc_val[0];
    return pred;
}