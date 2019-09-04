#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int* mb_type; scalar_t__*** motion_val; } ;
struct TYPE_9__ {int mb_x; int mb_y; int mb_stride; int* block_last_index; int mb_skipped; int mb_width; int /*<<< orphan*/  block; scalar_t__*** mv; TYPE_1__ current_picture; int /*<<< orphan*/  mv_type; int /*<<< orphan*/  mv_dir; scalar_t__ mb_intra; } ;
struct TYPE_10__ {int gob_number; int /*<<< orphan*/  mtype; TYPE_2__ s; } ;
typedef  TYPE_2__ MpegEncContext ;
typedef  TYPE_3__ H261Context ;

/* Variables and functions */
 int MB_TYPE_16x16 ; 
 int /*<<< orphan*/  MB_TYPE_H261_FIL ; 
 int MB_TYPE_L0 ; 
 int MB_TYPE_SKIP ; 
 int /*<<< orphan*/  MV_DIR_FORWARD ; 
 int /*<<< orphan*/  MV_TYPE_16X16 ; 
 int /*<<< orphan*/  ff_init_block_index (TYPE_2__* const) ; 
 int /*<<< orphan*/  ff_mpv_reconstruct_mb (TYPE_2__* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_update_block_index (TYPE_2__* const) ; 

__attribute__((used)) static int h261_decode_mb_skipped(H261Context *h, int mba1, int mba2)
{
    MpegEncContext *const s = &h->s;
    int i;

    s->mb_intra = 0;

    for (i = mba1; i < mba2; i++) {
        int j, xy;

        s->mb_x = ((h->gob_number - 1) % 2) * 11 + i % 11;
        s->mb_y = ((h->gob_number - 1) / 2) * 3 + i / 11;
        xy      = s->mb_x + s->mb_y * s->mb_stride;
        ff_init_block_index(s);
        ff_update_block_index(s);

        for (j = 0; j < 6; j++)
            s->block_last_index[j] = -1;

        s->mv_dir                      = MV_DIR_FORWARD;
        s->mv_type                     = MV_TYPE_16X16;
        s->current_picture.mb_type[xy] = MB_TYPE_SKIP | MB_TYPE_16x16 | MB_TYPE_L0;
        s->mv[0][0][0]                 = 0;
        s->mv[0][0][1]                 = 0;
        s->mb_skipped                  = 1;
        h->mtype                      &= ~MB_TYPE_H261_FIL;

        if (s->current_picture.motion_val[0]) {
            int b_stride = 2*s->mb_width + 1;
            int b_xy     = 2 * s->mb_x + (2 * s->mb_y) * b_stride;
            s->current_picture.motion_val[0][b_xy][0] = s->mv[0][0][0];
            s->current_picture.motion_val[0][b_xy][1] = s->mv[0][0][1];
        }

        ff_mpv_reconstruct_mb(s, s->block);
    }

    return 0;
}