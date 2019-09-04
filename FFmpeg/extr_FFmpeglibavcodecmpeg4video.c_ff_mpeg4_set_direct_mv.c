#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_7__ {int* mb_type; int** ref_index; } ;
struct TYPE_8__ {int mb_x; int mb_y; int mb_stride; int** field_select; int pp_field_time; int pb_field_time; int*** mv; int**** p_field_mv_table; void* mv_type; int /*<<< orphan*/  quarter_sample; TYPE_1__* avctx; scalar_t__ top_field_first; TYPE_2__ next_picture; } ;
struct TYPE_6__ {int workaround_bugs; } ;
typedef  TYPE_3__ MpegEncContext ;

/* Variables and functions */
 int FF_BUG_DIRECT_BLOCKSIZE ; 
 scalar_t__ IS_8X8 (int const) ; 
 scalar_t__ IS_INTERLACED (int const) ; 
 int MB_TYPE_16x16 ; 
 int MB_TYPE_16x8 ; 
 int MB_TYPE_8x8 ; 
 int MB_TYPE_DIRECT2 ; 
 int MB_TYPE_INTERLACED ; 
 int MB_TYPE_L0L1 ; 
 void* MV_TYPE_16X16 ; 
 void* MV_TYPE_8X8 ; 
 void* MV_TYPE_FIELD ; 
 int /*<<< orphan*/  ff_mpeg4_set_one_direct_mv (TYPE_3__*,int,int,int) ; 

int ff_mpeg4_set_direct_mv(MpegEncContext *s, int mx, int my)
{
    const int mb_index          = s->mb_x + s->mb_y * s->mb_stride;
    const int colocated_mb_type = s->next_picture.mb_type[mb_index];
    uint16_t time_pp;
    uint16_t time_pb;
    int i;

    // FIXME avoid divides
    // try special case with shifts for 1 and 3 B-frames?

    if (IS_8X8(colocated_mb_type)) {
        s->mv_type = MV_TYPE_8X8;
        for (i = 0; i < 4; i++)
            ff_mpeg4_set_one_direct_mv(s, mx, my, i);
        return MB_TYPE_DIRECT2 | MB_TYPE_8x8 | MB_TYPE_L0L1;
    } else if (IS_INTERLACED(colocated_mb_type)) {
        s->mv_type = MV_TYPE_FIELD;
        for (i = 0; i < 2; i++) {
            int field_select = s->next_picture.ref_index[0][4 * mb_index + 2 * i];
            s->field_select[0][i] = field_select;
            s->field_select[1][i] = i;
            if (s->top_field_first) {
                time_pp = s->pp_field_time - field_select + i;
                time_pb = s->pb_field_time - field_select + i;
            } else {
                time_pp = s->pp_field_time + field_select - i;
                time_pb = s->pb_field_time + field_select - i;
            }
            s->mv[0][i][0] = s->p_field_mv_table[i][0][mb_index][0] *
                             time_pb / time_pp + mx;
            s->mv[0][i][1] = s->p_field_mv_table[i][0][mb_index][1] *
                             time_pb / time_pp + my;
            s->mv[1][i][0] = mx ? s->mv[0][i][0] -
                                  s->p_field_mv_table[i][0][mb_index][0]
                                : s->p_field_mv_table[i][0][mb_index][0] *
                                  (time_pb - time_pp) / time_pp;
            s->mv[1][i][1] = my ? s->mv[0][i][1] -
                                  s->p_field_mv_table[i][0][mb_index][1]
                                : s->p_field_mv_table[i][0][mb_index][1] *
                                  (time_pb - time_pp) / time_pp;
        }
        return MB_TYPE_DIRECT2 | MB_TYPE_16x8 |
               MB_TYPE_L0L1    | MB_TYPE_INTERLACED;
    } else {
        ff_mpeg4_set_one_direct_mv(s, mx, my, 0);
        s->mv[0][1][0] =
        s->mv[0][2][0] =
        s->mv[0][3][0] = s->mv[0][0][0];
        s->mv[0][1][1] =
        s->mv[0][2][1] =
        s->mv[0][3][1] = s->mv[0][0][1];
        s->mv[1][1][0] =
        s->mv[1][2][0] =
        s->mv[1][3][0] = s->mv[1][0][0];
        s->mv[1][1][1] =
        s->mv[1][2][1] =
        s->mv[1][3][1] = s->mv[1][0][1];
        if ((s->avctx->workaround_bugs & FF_BUG_DIRECT_BLOCKSIZE) ||
            !s->quarter_sample)
            s->mv_type = MV_TYPE_16X16;
        else
            s->mv_type = MV_TYPE_8X8;
        // Note see prev line
        return MB_TYPE_DIRECT2 | MB_TYPE_16x16 | MB_TYPE_L0L1;
    }
}