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
struct TYPE_7__ {int /*<<< orphan*/  dia_size; } ;
struct TYPE_9__ {int first_slice_line; scalar_t__ mb_y; scalar_t__ start_mb_y; scalar_t__ end_mb_y; scalar_t__ mb_x; scalar_t__ mb_width; int* block_index; scalar_t__ pict_type; TYPE_2__* avctx; TYPE_1__ me; } ;
struct TYPE_8__ {int /*<<< orphan*/  dia_size; } ;
typedef  TYPE_3__ MpegEncContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 scalar_t__ AV_PICTURE_TYPE_B ; 
 int /*<<< orphan*/  ff_check_alignment () ; 
 int /*<<< orphan*/  ff_estimate_b_frame_motion (TYPE_3__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ff_estimate_p_frame_motion (TYPE_3__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ff_init_block_index (TYPE_3__*) ; 

__attribute__((used)) static int estimate_motion_thread(AVCodecContext *c, void *arg){
    MpegEncContext *s= *(void**)arg;

    ff_check_alignment();

    s->me.dia_size= s->avctx->dia_size;
    s->first_slice_line=1;
    for(s->mb_y= s->start_mb_y; s->mb_y < s->end_mb_y; s->mb_y++) {
        s->mb_x=0; //for block init below
        ff_init_block_index(s);
        for(s->mb_x=0; s->mb_x < s->mb_width; s->mb_x++) {
            s->block_index[0]+=2;
            s->block_index[1]+=2;
            s->block_index[2]+=2;
            s->block_index[3]+=2;

            /* compute motion vector & mb_type and store in context */
            if(s->pict_type==AV_PICTURE_TYPE_B)
                ff_estimate_b_frame_motion(s, s->mb_x, s->mb_y);
            else
                ff_estimate_p_frame_motion(s, s->mb_x, s->mb_y);
        }
        s->first_slice_line=0;
    }
    return 0;
}