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
struct TYPE_6__ {int pre_pass; int /*<<< orphan*/  dia_size; } ;
struct TYPE_7__ {int first_slice_line; scalar_t__ mb_y; scalar_t__ end_mb_y; scalar_t__ start_mb_y; scalar_t__ mb_x; scalar_t__ mb_width; TYPE_2__ me; TYPE_1__* avctx; } ;
struct TYPE_5__ {int /*<<< orphan*/  pre_dia_size; } ;
typedef  TYPE_3__ MpegEncContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  ff_pre_estimate_p_frame_motion (TYPE_3__*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int pre_estimate_motion_thread(AVCodecContext *c, void *arg){
    MpegEncContext *s= *(void**)arg;


    s->me.pre_pass=1;
    s->me.dia_size= s->avctx->pre_dia_size;
    s->first_slice_line=1;
    for(s->mb_y= s->end_mb_y-1; s->mb_y >= s->start_mb_y; s->mb_y--) {
        for(s->mb_x=s->mb_width-1; s->mb_x >=0 ;s->mb_x--) {
            ff_pre_estimate_p_frame_motion(s, s->mb_x, s->mb_y);
        }
        s->first_slice_line=0;
    }

    s->me.pre_pass=0;

    return 0;
}