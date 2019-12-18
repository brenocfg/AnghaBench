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
typedef  int int16_t ;
struct TYPE_5__ {int*** motion_val; } ;
struct TYPE_7__ {int b8_stride; int* block_index; scalar_t__ first_slice_line; int /*<<< orphan*/  gb; int /*<<< orphan*/  mspel; scalar_t__ mb_x; TYPE_1__ current_picture; } ;
struct TYPE_6__ {scalar_t__ top_left_mv_flag; TYPE_3__ s; } ;
typedef  TYPE_2__ Wmv2Context ;
typedef  TYPE_3__ MpegEncContext ;

/* Variables and functions */
 int /*<<< orphan*/  FFABS (int) ; 
 int FFMAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int mid_pred (int,int,int) ; 

__attribute__((used)) static int16_t *wmv2_pred_motion(Wmv2Context *w, int *px, int *py)
{
    MpegEncContext *const s = &w->s;
    int xy, wrap, diff, type;
    int16_t *A, *B, *C, *mot_val;

    wrap    = s->b8_stride;
    xy      = s->block_index[0];

    mot_val = s->current_picture.motion_val[0][xy];

    A       = s->current_picture.motion_val[0][xy     - 1];
    B       = s->current_picture.motion_val[0][xy     - wrap];
    C       = s->current_picture.motion_val[0][xy + 2 - wrap];

    if (s->mb_x && !s->first_slice_line && !s->mspel && w->top_left_mv_flag)
        diff = FFMAX(FFABS(A[0] - B[0]), FFABS(A[1] - B[1]));
    else
        diff = 0;

    if (diff >= 8)
        type = get_bits1(&s->gb);
    else
        type = 2;

    if (type == 0) {
        *px = A[0];
        *py = A[1];
    } else if (type == 1) {
        *px = B[0];
        *py = B[1];
    } else {
        /* special case for first (slice) line */
        if (s->first_slice_line) {
            *px = A[0];
            *py = A[1];
        } else {
            *px = mid_pred(A[0], B[0], C[0]);
            *py = mid_pred(A[1], B[1], C[1]);
        }
    }

    return mot_val;
}