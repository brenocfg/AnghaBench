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
struct TYPE_4__ {int*** motion_val; } ;
struct TYPE_5__ {int mb_x; int mb_y; int mb_stride; int** p_mv_table; int* block_index; TYPE_1__ current_picture; scalar_t__ b8_stride; } ;
typedef  TYPE_2__ MpegEncContext ;

/* Variables and functions */

__attribute__((used)) static inline void set_p_mv_tables(MpegEncContext * s, int mx, int my, int mv4)
{
    const int xy= s->mb_x + s->mb_y*s->mb_stride;

    s->p_mv_table[xy][0] = mx;
    s->p_mv_table[xy][1] = my;

    /* has already been set to the 4 MV if 4MV is done */
    if(mv4){
        int mot_xy= s->block_index[0];

        s->current_picture.motion_val[0][mot_xy    ][0] = mx;
        s->current_picture.motion_val[0][mot_xy    ][1] = my;
        s->current_picture.motion_val[0][mot_xy + 1][0] = mx;
        s->current_picture.motion_val[0][mot_xy + 1][1] = my;

        mot_xy += s->b8_stride;
        s->current_picture.motion_val[0][mot_xy    ][0] = mx;
        s->current_picture.motion_val[0][mot_xy    ][1] = my;
        s->current_picture.motion_val[0][mot_xy + 1][0] = mx;
        s->current_picture.motion_val[0][mot_xy + 1][1] = my;
    }
}