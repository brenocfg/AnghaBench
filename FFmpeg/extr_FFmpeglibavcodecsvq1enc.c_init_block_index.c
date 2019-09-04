#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* block_index; int b8_stride; int mb_y; int mb_x; int mb_stride; int mb_height; } ;
typedef  TYPE_1__ MpegEncContext ;

/* Variables and functions */

__attribute__((used)) static void init_block_index(MpegEncContext *s){
    s->block_index[0]= s->b8_stride*(s->mb_y*2    )     + s->mb_x*2;
    s->block_index[1]= s->b8_stride*(s->mb_y*2    ) + 1 + s->mb_x*2;
    s->block_index[2]= s->b8_stride*(s->mb_y*2 + 1)     + s->mb_x*2;
    s->block_index[3]= s->b8_stride*(s->mb_y*2 + 1) + 1 + s->mb_x*2;
    s->block_index[4]= s->mb_stride*(s->mb_y + 1)                + s->b8_stride*s->mb_height*2 + s->mb_x;
    s->block_index[5]= s->mb_stride*(s->mb_y + s->mb_height + 2) + s->b8_stride*s->mb_height*2 + s->mb_x;
}