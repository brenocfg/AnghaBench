#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int int16_t ;
struct TYPE_9__ {int*** motion_val; } ;
struct TYPE_8__ {int /*<<< orphan*/ *** motion_val; } ;
struct TYPE_11__ {int b8_stride; int* block_index; int*** mv; int mb_x; int mb_width; int mb_y; int mb_height; TYPE_3__ current_picture; int /*<<< orphan*/  gb; int /*<<< orphan*/  first_slice_line; int /*<<< orphan*/  quarter_sample; TYPE_2__ next_picture; int /*<<< orphan*/  avctx; TYPE_1__* next_picture_ptr; scalar_t__ mb_intra; } ;
struct TYPE_10__ {int range_x; int range_y; scalar_t__ profile; int /*<<< orphan*/  bfraction; int /*<<< orphan*/  field_mode; scalar_t__** mb_type; TYPE_5__ s; } ;
typedef  TYPE_4__ VC1Context ;
struct TYPE_7__ {scalar_t__ field_picture; } ;
typedef  TYPE_5__ MpegEncContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int BMV_TYPE_BACKWARD ; 
 int BMV_TYPE_FORWARD ; 
 int BMV_TYPE_INTERPOLATED ; 
 int FFABS (int) ; 
 scalar_t__ PROFILE_ADVANCED ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 void* av_clip (int,int,int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 
 int mid_pred (int,int,int) ; 
 void* scale_mv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void ff_vc1_pred_b_mv(VC1Context *v, int dmv_x[2], int dmv_y[2],
                      int direct, int mvtype)
{
    MpegEncContext *s = &v->s;
    int xy, wrap, off = 0;
    int16_t *A, *B, *C;
    int px, py;
    int sum;
    int r_x, r_y;
    const uint8_t *is_intra = v->mb_type[0];

    av_assert0(!v->field_mode);

    r_x = v->range_x;
    r_y = v->range_y;
    /* scale MV difference to be quad-pel */
    if (!s->quarter_sample) {
        dmv_x[0] *= 2;
        dmv_y[0] *= 2;
        dmv_x[1] *= 2;
        dmv_y[1] *= 2;
    }

    wrap = s->b8_stride;
    xy = s->block_index[0];

    if (s->mb_intra) {
        s->current_picture.motion_val[0][xy][0] =
        s->current_picture.motion_val[0][xy][1] =
        s->current_picture.motion_val[1][xy][0] =
        s->current_picture.motion_val[1][xy][1] = 0;
        return;
    }
        if (direct && s->next_picture_ptr->field_picture)
            av_log(s->avctx, AV_LOG_WARNING, "Mixed frame/field direct mode not supported\n");

        s->mv[0][0][0] = scale_mv(s->next_picture.motion_val[1][xy][0], v->bfraction, 0, s->quarter_sample);
        s->mv[0][0][1] = scale_mv(s->next_picture.motion_val[1][xy][1], v->bfraction, 0, s->quarter_sample);
        s->mv[1][0][0] = scale_mv(s->next_picture.motion_val[1][xy][0], v->bfraction, 1, s->quarter_sample);
        s->mv[1][0][1] = scale_mv(s->next_picture.motion_val[1][xy][1], v->bfraction, 1, s->quarter_sample);

        /* Pullback predicted motion vectors as specified in 8.4.5.4 */
        s->mv[0][0][0] = av_clip(s->mv[0][0][0], -60 - (s->mb_x << 6), (s->mb_width  << 6) - 4 - (s->mb_x << 6));
        s->mv[0][0][1] = av_clip(s->mv[0][0][1], -60 - (s->mb_y << 6), (s->mb_height << 6) - 4 - (s->mb_y << 6));
        s->mv[1][0][0] = av_clip(s->mv[1][0][0], -60 - (s->mb_x << 6), (s->mb_width  << 6) - 4 - (s->mb_x << 6));
        s->mv[1][0][1] = av_clip(s->mv[1][0][1], -60 - (s->mb_y << 6), (s->mb_height << 6) - 4 - (s->mb_y << 6));
    if (direct) {
        s->current_picture.motion_val[0][xy][0] = s->mv[0][0][0];
        s->current_picture.motion_val[0][xy][1] = s->mv[0][0][1];
        s->current_picture.motion_val[1][xy][0] = s->mv[1][0][0];
        s->current_picture.motion_val[1][xy][1] = s->mv[1][0][1];
        return;
    }

    if ((mvtype == BMV_TYPE_FORWARD) || (mvtype == BMV_TYPE_INTERPOLATED)) {
        C   = s->current_picture.motion_val[0][xy - 2];
        A   = s->current_picture.motion_val[0][xy - wrap * 2];
        off = (s->mb_x == (s->mb_width - 1)) ? -2 : 2;
        B   = s->current_picture.motion_val[0][xy - wrap * 2 + off];

        if (!s->mb_x) C[0] = C[1] = 0;
        if (!s->first_slice_line) { // predictor A is not out of bounds
            if (s->mb_width == 1) {
                px = A[0];
                py = A[1];
            } else {
                px = mid_pred(A[0], B[0], C[0]);
                py = mid_pred(A[1], B[1], C[1]);
            }
        } else if (s->mb_x) { // predictor C is not out of bounds
            px = C[0];
            py = C[1];
        } else {
            px = py = 0;
        }
        /* Pullback MV as specified in 8.3.5.3.4 */
        {
            int qx, qy, X, Y;
            int sh = v->profile < PROFILE_ADVANCED ? 5 : 6;
            int MV = 4 - (1 << sh);
            qx = (s->mb_x << sh);
            qy = (s->mb_y << sh);
            X  = (s->mb_width  << sh) - 4;
            Y  = (s->mb_height << sh) - 4;
            if (qx + px < MV) px = MV - qx;
            if (qy + py < MV) py = MV - qy;
            if (qx + px > X) px = X - qx;
            if (qy + py > Y) py = Y - qy;
        }
        /* Calculate hybrid prediction as specified in 8.3.5.3.5 */
        if (0 && !s->first_slice_line && s->mb_x) {
            if (is_intra[xy - wrap])
                sum = FFABS(px) + FFABS(py);
            else
                sum = FFABS(px - A[0]) + FFABS(py - A[1]);
            if (sum > 32) {
                if (get_bits1(&s->gb)) {
                    px = A[0];
                    py = A[1];
                } else {
                    px = C[0];
                    py = C[1];
                }
            } else {
                if (is_intra[xy - 2])
                    sum = FFABS(px) + FFABS(py);
                else
                    sum = FFABS(px - C[0]) + FFABS(py - C[1]);
                if (sum > 32) {
                    if (get_bits1(&s->gb)) {
                        px = A[0];
                        py = A[1];
                    } else {
                        px = C[0];
                        py = C[1];
                    }
                }
            }
        }
        /* store MV using signed modulus of MV range defined in 4.11 */
        s->mv[0][0][0] = ((px + dmv_x[0] + r_x) & ((r_x << 1) - 1)) - r_x;
        s->mv[0][0][1] = ((py + dmv_y[0] + r_y) & ((r_y << 1) - 1)) - r_y;
    }
    if ((mvtype == BMV_TYPE_BACKWARD) || (mvtype == BMV_TYPE_INTERPOLATED)) {
        C   = s->current_picture.motion_val[1][xy - 2];
        A   = s->current_picture.motion_val[1][xy - wrap * 2];
        off = (s->mb_x == (s->mb_width - 1)) ? -2 : 2;
        B   = s->current_picture.motion_val[1][xy - wrap * 2 + off];

        if (!s->mb_x)
            C[0] = C[1] = 0;
        if (!s->first_slice_line) { // predictor A is not out of bounds
            if (s->mb_width == 1) {
                px = A[0];
                py = A[1];
            } else {
                px = mid_pred(A[0], B[0], C[0]);
                py = mid_pred(A[1], B[1], C[1]);
            }
        } else if (s->mb_x) { // predictor C is not out of bounds
            px = C[0];
            py = C[1];
        } else {
            px = py = 0;
        }
        /* Pullback MV as specified in 8.3.5.3.4 */
        {
            int qx, qy, X, Y;
            int sh = v->profile < PROFILE_ADVANCED ? 5 : 6;
            int MV = 4 - (1 << sh);
            qx = (s->mb_x << sh);
            qy = (s->mb_y << sh);
            X  = (s->mb_width  << sh) - 4;
            Y  = (s->mb_height << sh) - 4;
            if (qx + px < MV) px = MV - qx;
            if (qy + py < MV) py = MV - qy;
            if (qx + px > X) px = X - qx;
            if (qy + py > Y) py = Y - qy;
        }
        /* Calculate hybrid prediction as specified in 8.3.5.3.5 */
        if (0 && !s->first_slice_line && s->mb_x) {
            if (is_intra[xy - wrap])
                sum = FFABS(px) + FFABS(py);
            else
                sum = FFABS(px - A[0]) + FFABS(py - A[1]);
            if (sum > 32) {
                if (get_bits1(&s->gb)) {
                    px = A[0];
                    py = A[1];
                } else {
                    px = C[0];
                    py = C[1];
                }
            } else {
                if (is_intra[xy - 2])
                    sum = FFABS(px) + FFABS(py);
                else
                    sum = FFABS(px - C[0]) + FFABS(py - C[1]);
                if (sum > 32) {
                    if (get_bits1(&s->gb)) {
                        px = A[0];
                        py = A[1];
                    } else {
                        px = C[0];
                        py = C[1];
                    }
                }
            }
        }
        /* store MV using signed modulus of MV range defined in 4.11 */

        s->mv[1][0][0] = ((px + dmv_x[1] + r_x) & ((r_x << 1) - 1)) - r_x;
        s->mv[1][0][1] = ((py + dmv_y[1] + r_y) & ((r_y << 1) - 1)) - r_y;
    }
    s->current_picture.motion_val[0][xy][0] = s->mv[0][0][0];
    s->current_picture.motion_val[0][xy][1] = s->mv[0][0][1];
    s->current_picture.motion_val[1][xy][0] = s->mv[1][0][0];
    s->current_picture.motion_val[1][xy][1] = s->mv[1][0][1];
}