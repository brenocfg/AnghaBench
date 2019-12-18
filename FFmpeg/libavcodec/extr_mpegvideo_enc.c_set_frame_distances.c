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
struct TYPE_11__ {int time; scalar_t__ pict_type; scalar_t__ pb_time; scalar_t__ pp_time; scalar_t__ last_non_b_time; scalar_t__ picture_number; TYPE_4__* avctx; TYPE_2__* current_picture_ptr; } ;
struct TYPE_9__ {int num; } ;
struct TYPE_10__ {TYPE_3__ time_base; } ;
struct TYPE_8__ {TYPE_1__* f; } ;
struct TYPE_7__ {int pts; } ;
typedef  TYPE_5__ MpegEncContext ;

/* Variables and functions */
 int AV_NOPTS_VALUE ; 
 scalar_t__ AV_PICTURE_TYPE_B ; 
 int /*<<< orphan*/  av_assert1 (int) ; 

__attribute__((used)) static void set_frame_distances(MpegEncContext * s){
    av_assert1(s->current_picture_ptr->f->pts != AV_NOPTS_VALUE);
    s->time = s->current_picture_ptr->f->pts * s->avctx->time_base.num;

    if(s->pict_type==AV_PICTURE_TYPE_B){
        s->pb_time= s->pp_time - (s->last_non_b_time - s->time);
        av_assert1(s->pb_time > 0 && s->pb_time < s->pp_time);
    }else{
        s->pp_time= s->time - s->last_non_b_time;
        s->last_non_b_time= s->time;
        av_assert1(s->picture_number==0 || s->pp_time > 0);
    }
}