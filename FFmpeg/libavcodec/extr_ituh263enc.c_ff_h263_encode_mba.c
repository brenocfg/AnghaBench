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
struct TYPE_3__ {int mb_num; int mb_x; int mb_width; int mb_y; int /*<<< orphan*/  pb; } ;
typedef  TYPE_1__ MpegEncContext ;

/* Variables and functions */
 int /*<<< orphan*/ * ff_mba_length ; 
 int* ff_mba_max ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void ff_h263_encode_mba(MpegEncContext *s)
{
    int i, mb_pos;

    for(i=0; i<6; i++){
        if(s->mb_num-1 <= ff_mba_max[i]) break;
    }
    mb_pos= s->mb_x + s->mb_width*s->mb_y;
    put_bits(&s->pb, ff_mba_length[i], mb_pos);
}