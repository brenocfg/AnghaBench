#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_6__ {scalar_t__ flags; } ;
struct TYPE_5__ {TYPE_2__ me; } ;
typedef  TYPE_1__ MpegEncContext ;
typedef  TYPE_2__ MotionEstContext ;

/* Variables and functions */
 int epzs_motion_search_internal (TYPE_1__*,int*,int*,int**,int,int,int /*<<< orphan*/ **,int,scalar_t__,int,int) ; 

int ff_epzs_motion_search(MpegEncContext *s, int *mx_ptr, int *my_ptr,
                          int P[10][2], int src_index, int ref_index,
                          int16_t (*last_mv)[2], int ref_mv_scale,
                          int size, int h)
{
    MotionEstContext * const c= &s->me;
//FIXME convert other functions in the same way if faster
    if(c->flags==0 && h==16 && size==0){
        return epzs_motion_search_internal(s, mx_ptr, my_ptr, P, src_index, ref_index, last_mv, ref_mv_scale, 0, 0, 16);
//    case FLAG_QPEL:
//        return epzs_motion_search_internal(s, mx_ptr, my_ptr, P, src_index, ref_index, last_mv, ref_mv_scale, FLAG_QPEL);
    }else{
        return epzs_motion_search_internal(s, mx_ptr, my_ptr, P, src_index, ref_index, last_mv, ref_mv_scale, c->flags, size, h);
    }
}