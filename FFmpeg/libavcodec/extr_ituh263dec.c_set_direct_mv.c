#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int* mb_type; TYPE_1__* f; } ;
struct TYPE_9__ {int mb_x; int mb_y; int mb_stride; scalar_t__ codec_tag; void* mv_type; int /*<<< orphan*/ *** mv; TYPE_2__ last_picture; TYPE_2__ next_picture; } ;
struct TYPE_7__ {scalar_t__ pict_type; } ;
typedef  TYPE_2__ Picture ;
typedef  TYPE_3__ MpegEncContext ;

/* Variables and functions */
 scalar_t__ AV_PICTURE_TYPE_I ; 
 scalar_t__ AV_RL32 (char*) ; 
 scalar_t__ IS_8X8 (int) ; 
 int MB_TYPE_16x16 ; 
 int MB_TYPE_8x8 ; 
 int MB_TYPE_DIRECT2 ; 
 int MB_TYPE_L0L1 ; 
 void* MV_TYPE_8X8 ; 
 int /*<<< orphan*/  set_one_direct_mv (TYPE_3__*,TYPE_2__*,int) ; 

__attribute__((used)) static int set_direct_mv(MpegEncContext *s)
{
    const int mb_index = s->mb_x + s->mb_y * s->mb_stride;
    Picture *p = &s->next_picture;
    int colocated_mb_type = p->mb_type[mb_index];
    int i;

    if (s->codec_tag == AV_RL32("U263") && p->f->pict_type == AV_PICTURE_TYPE_I) {
        p = &s->last_picture;
        colocated_mb_type = p->mb_type[mb_index];
    }

    if (IS_8X8(colocated_mb_type)) {
        s->mv_type = MV_TYPE_8X8;
        for (i = 0; i < 4; i++)
            set_one_direct_mv(s, p, i);
        return MB_TYPE_DIRECT2 | MB_TYPE_8x8 | MB_TYPE_L0L1;
    } else {
        set_one_direct_mv(s, p, 0);
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
        s->mv_type = MV_TYPE_8X8;
        // Note see prev line
        return MB_TYPE_DIRECT2 | MB_TYPE_16x16 | MB_TYPE_L0L1;
    }
}