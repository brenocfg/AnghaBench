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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int*** motion_val; } ;
struct TYPE_7__ {int b8_stride; int* block_index; int*** mv; size_t mb_x; size_t mb_stride; int mb_width; TYPE_1__ current_picture; scalar_t__ first_slice_line; scalar_t__ mb_intra; } ;
struct TYPE_6__ {scalar_t__* blk_mv_type; scalar_t__* is_intra; scalar_t__** luma_mv; TYPE_3__ s; } ;
typedef  TYPE_2__ VC1Context ;
typedef  TYPE_3__ MpegEncContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert1 (int) ; 
 int mid_pred (int,int,int) ; 

void ff_vc1_pred_mv_intfr(VC1Context *v, int n, int dmv_x, int dmv_y,
                          int mvn, int r_x, int r_y, uint8_t* is_intra, int dir)
{
    MpegEncContext *s = &v->s;
    int xy, wrap, off = 0;
    int A[2], B[2], C[2];
    int px = 0, py = 0;
    int a_valid = 0, b_valid = 0, c_valid = 0;
    int field_a, field_b, field_c; // 0: same, 1: opposite
    int total_valid, num_samefield, num_oppfield;
    int pos_c, pos_b, n_adj;

    wrap = s->b8_stride;
    xy = s->block_index[n];

    if (s->mb_intra) {
        s->mv[0][n][0] = s->current_picture.motion_val[0][xy][0] = 0;
        s->mv[0][n][1] = s->current_picture.motion_val[0][xy][1] = 0;
        s->current_picture.motion_val[1][xy][0] = 0;
        s->current_picture.motion_val[1][xy][1] = 0;
        if (mvn == 1) { /* duplicate motion data for 1-MV block */
            s->current_picture.motion_val[0][xy + 1][0]        = 0;
            s->current_picture.motion_val[0][xy + 1][1]        = 0;
            s->current_picture.motion_val[0][xy + wrap][0]     = 0;
            s->current_picture.motion_val[0][xy + wrap][1]     = 0;
            s->current_picture.motion_val[0][xy + wrap + 1][0] = 0;
            s->current_picture.motion_val[0][xy + wrap + 1][1] = 0;
            v->luma_mv[s->mb_x][0] = v->luma_mv[s->mb_x][1] = 0;
            s->current_picture.motion_val[1][xy + 1][0]        = 0;
            s->current_picture.motion_val[1][xy + 1][1]        = 0;
            s->current_picture.motion_val[1][xy + wrap][0]     = 0;
            s->current_picture.motion_val[1][xy + wrap][1]     = 0;
            s->current_picture.motion_val[1][xy + wrap + 1][0] = 0;
            s->current_picture.motion_val[1][xy + wrap + 1][1] = 0;
        }
        return;
    }

    off = ((n == 0) || (n == 1)) ? 1 : -1;
    /* predict A */
    if (s->mb_x || (n == 1) || (n == 3)) {
        if ((v->blk_mv_type[xy]) // current block (MB) has a field MV
            || (!v->blk_mv_type[xy] && !v->blk_mv_type[xy - 1])) { // or both have frame MV
            A[0] = s->current_picture.motion_val[dir][xy - 1][0];
            A[1] = s->current_picture.motion_val[dir][xy - 1][1];
            a_valid = 1;
        } else { // current block has frame mv and cand. has field MV (so average)
            A[0] = (s->current_picture.motion_val[dir][xy - 1][0]
                    + s->current_picture.motion_val[dir][xy - 1 + off * wrap][0] + 1) >> 1;
            A[1] = (s->current_picture.motion_val[dir][xy - 1][1]
                    + s->current_picture.motion_val[dir][xy - 1 + off * wrap][1] + 1) >> 1;
            a_valid = 1;
        }
        if (!(n & 1) && v->is_intra[s->mb_x - 1]) {
            a_valid = 0;
            A[0] = A[1] = 0;
        }
    } else
        A[0] = A[1] = 0;
    /* Predict B and C */
    B[0] = B[1] = C[0] = C[1] = 0;
    if (n == 0 || n == 1 || v->blk_mv_type[xy]) {
        if (!s->first_slice_line) {
            if (!v->is_intra[s->mb_x - s->mb_stride]) {
                b_valid = 1;
                n_adj   = n | 2;
                pos_b   = s->block_index[n_adj] - 2 * wrap;
                if (v->blk_mv_type[pos_b] && v->blk_mv_type[xy]) {
                    n_adj = (n & 2) | (n & 1);
                }
                B[0] = s->current_picture.motion_val[dir][s->block_index[n_adj] - 2 * wrap][0];
                B[1] = s->current_picture.motion_val[dir][s->block_index[n_adj] - 2 * wrap][1];
                if (v->blk_mv_type[pos_b] && !v->blk_mv_type[xy]) {
                    B[0] = (B[0] + s->current_picture.motion_val[dir][s->block_index[n_adj ^ 2] - 2 * wrap][0] + 1) >> 1;
                    B[1] = (B[1] + s->current_picture.motion_val[dir][s->block_index[n_adj ^ 2] - 2 * wrap][1] + 1) >> 1;
                }
            }
            if (s->mb_width > 1) {
                if (!v->is_intra[s->mb_x - s->mb_stride + 1]) {
                    c_valid = 1;
                    n_adj   = 2;
                    pos_c   = s->block_index[2] - 2 * wrap + 2;
                    if (v->blk_mv_type[pos_c] && v->blk_mv_type[xy]) {
                        n_adj = n & 2;
                    }
                    C[0] = s->current_picture.motion_val[dir][s->block_index[n_adj] - 2 * wrap + 2][0];
                    C[1] = s->current_picture.motion_val[dir][s->block_index[n_adj] - 2 * wrap + 2][1];
                    if (v->blk_mv_type[pos_c] && !v->blk_mv_type[xy]) {
                        C[0] = (1 + C[0] + (s->current_picture.motion_val[dir][s->block_index[n_adj ^ 2] - 2 * wrap + 2][0])) >> 1;
                        C[1] = (1 + C[1] + (s->current_picture.motion_val[dir][s->block_index[n_adj ^ 2] - 2 * wrap + 2][1])) >> 1;
                    }
                    if (s->mb_x == s->mb_width - 1) {
                        if (!v->is_intra[s->mb_x - s->mb_stride - 1]) {
                            c_valid = 1;
                            n_adj   = 3;
                            pos_c   = s->block_index[3] - 2 * wrap - 2;
                            if (v->blk_mv_type[pos_c] && v->blk_mv_type[xy]) {
                                n_adj = n | 1;
                            }
                            C[0] = s->current_picture.motion_val[dir][s->block_index[n_adj] - 2 * wrap - 2][0];
                            C[1] = s->current_picture.motion_val[dir][s->block_index[n_adj] - 2 * wrap - 2][1];
                            if (v->blk_mv_type[pos_c] && !v->blk_mv_type[xy]) {
                                C[0] = (1 + C[0] + s->current_picture.motion_val[dir][s->block_index[1] - 2 * wrap - 2][0]) >> 1;
                                C[1] = (1 + C[1] + s->current_picture.motion_val[dir][s->block_index[1] - 2 * wrap - 2][1]) >> 1;
                            }
                        } else
                            c_valid = 0;
                    }
                }
            }
        }
    } else {
        pos_b   = s->block_index[1];
        b_valid = 1;
        B[0]    = s->current_picture.motion_val[dir][pos_b][0];
        B[1]    = s->current_picture.motion_val[dir][pos_b][1];
        pos_c   = s->block_index[0];
        c_valid = 1;
        C[0]    = s->current_picture.motion_val[dir][pos_c][0];
        C[1]    = s->current_picture.motion_val[dir][pos_c][1];
    }

    total_valid = a_valid + b_valid + c_valid;
    // check if predictor A is out of bounds
    if (!s->mb_x && !(n == 1 || n == 3)) {
        A[0] = A[1] = 0;
    }
    // check if predictor B is out of bounds
    if ((s->first_slice_line && v->blk_mv_type[xy]) || (s->first_slice_line && !(n & 2))) {
        B[0] = B[1] = C[0] = C[1] = 0;
    }
    if (!v->blk_mv_type[xy]) {
        if (s->mb_width == 1) {
            px = B[0];
            py = B[1];
        } else {
            if (total_valid >= 2) {
                px = mid_pred(A[0], B[0], C[0]);
                py = mid_pred(A[1], B[1], C[1]);
            } else if (total_valid) {
                if      (a_valid) { px = A[0]; py = A[1]; }
                else if (b_valid) { px = B[0]; py = B[1]; }
                else              { px = C[0]; py = C[1]; }
            }
        }
    } else {
        if (a_valid)
            field_a = (A[1] & 4) ? 1 : 0;
        else
            field_a = 0;
        if (b_valid)
            field_b = (B[1] & 4) ? 1 : 0;
        else
            field_b = 0;
        if (c_valid)
            field_c = (C[1] & 4) ? 1 : 0;
        else
            field_c = 0;

        num_oppfield  = field_a + field_b + field_c;
        num_samefield = total_valid - num_oppfield;
        if (total_valid == 3) {
            if ((num_samefield == 3) || (num_oppfield == 3)) {
                px = mid_pred(A[0], B[0], C[0]);
                py = mid_pred(A[1], B[1], C[1]);
            } else if (num_samefield >= num_oppfield) {
                /* take one MV from same field set depending on priority
                the check for B may not be necessary */
                px = !field_a ? A[0] : B[0];
                py = !field_a ? A[1] : B[1];
            } else {
                px =  field_a ? A[0] : B[0];
                py =  field_a ? A[1] : B[1];
            }
        } else if (total_valid == 2) {
            if (num_samefield >= num_oppfield) {
                if (!field_a && a_valid) {
                    px = A[0];
                    py = A[1];
                } else if (!field_b && b_valid) {
                    px = B[0];
                    py = B[1];
                } else /*if (c_valid)*/ {
                    av_assert1(c_valid);
                    px = C[0];
                    py = C[1];
                }
            } else {
                if (field_a && a_valid) {
                    px = A[0];
                    py = A[1];
                } else /*if (field_b && b_valid)*/ {
                    av_assert1(field_b && b_valid);
                    px = B[0];
                    py = B[1];
                }
            }
        } else if (total_valid == 1) {
            px = (a_valid) ? A[0] : ((b_valid) ? B[0] : C[0]);
            py = (a_valid) ? A[1] : ((b_valid) ? B[1] : C[1]);
        }
    }

    /* store MV using signed modulus of MV range defined in 4.11 */
    s->mv[dir][n][0] = s->current_picture.motion_val[dir][xy][0] = ((px + dmv_x + r_x) & ((r_x << 1) - 1)) - r_x;
    s->mv[dir][n][1] = s->current_picture.motion_val[dir][xy][1] = ((py + dmv_y + r_y) & ((r_y << 1) - 1)) - r_y;
    if (mvn == 1) { /* duplicate motion data for 1-MV block */
        s->current_picture.motion_val[dir][xy +    1    ][0] = s->current_picture.motion_val[dir][xy][0];
        s->current_picture.motion_val[dir][xy +    1    ][1] = s->current_picture.motion_val[dir][xy][1];
        s->current_picture.motion_val[dir][xy + wrap    ][0] = s->current_picture.motion_val[dir][xy][0];
        s->current_picture.motion_val[dir][xy + wrap    ][1] = s->current_picture.motion_val[dir][xy][1];
        s->current_picture.motion_val[dir][xy + wrap + 1][0] = s->current_picture.motion_val[dir][xy][0];
        s->current_picture.motion_val[dir][xy + wrap + 1][1] = s->current_picture.motion_val[dir][xy][1];
    } else if (mvn == 2) { /* duplicate motion data for 2-Field MV block */
        s->current_picture.motion_val[dir][xy + 1][0] = s->current_picture.motion_val[dir][xy][0];
        s->current_picture.motion_val[dir][xy + 1][1] = s->current_picture.motion_val[dir][xy][1];
        s->mv[dir][n + 1][0] = s->mv[dir][n][0];
        s->mv[dir][n + 1][1] = s->mv[dir][n][1];
    }
}