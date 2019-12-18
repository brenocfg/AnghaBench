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
struct TYPE_7__ {int mb_x; int mb_y; int b8_stride; int mb_stride; scalar_t__ first_slice_line; TYPE_1__* current_picture_ptr; } ;
struct TYPE_6__ {int* deblock_coefs; scalar_t__ rv30; TYPE_3__ s; } ;
struct TYPE_5__ {int /*<<< orphan*/ ** motion_val; } ;
typedef  TYPE_2__ RV34DecContext ;
typedef  TYPE_3__ MpegEncContext ;

/* Variables and functions */
 int /*<<< orphan*/ ** int16_t (int /*<<< orphan*/ ) ; 
 scalar_t__ is_mv_diff_gt_3 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * motion_val ; 

__attribute__((used)) static int rv34_set_deblock_coef(RV34DecContext *r)
{
    MpegEncContext *s = &r->s;
    int hmvmask = 0, vmvmask = 0, i, j;
    int midx = s->mb_x * 2 + s->mb_y * 2 * s->b8_stride;
    int16_t (*motion_val)[2] = &s->current_picture_ptr->motion_val[0][midx];
    for(j = 0; j < 16; j += 8){
        for(i = 0; i < 2; i++){
            if(is_mv_diff_gt_3(motion_val + i, 1))
                vmvmask |= 0x11 << (j + i*2);
            if((j || s->mb_y) && is_mv_diff_gt_3(motion_val + i, s->b8_stride))
                hmvmask |= 0x03 << (j + i*2);
        }
        motion_val += s->b8_stride;
    }
    if(s->first_slice_line)
        hmvmask &= ~0x000F;
    if(!s->mb_x)
        vmvmask &= ~0x1111;
    if(r->rv30){ //RV30 marks both subblocks on the edge for filtering
        vmvmask |= (vmvmask & 0x4444) >> 1;
        hmvmask |= (hmvmask & 0x0F00) >> 4;
        if(s->mb_x)
            r->deblock_coefs[s->mb_x - 1 + s->mb_y*s->mb_stride] |= (vmvmask & 0x1111) << 3;
        if(!s->first_slice_line)
            r->deblock_coefs[s->mb_x + (s->mb_y - 1)*s->mb_stride] |= (hmvmask & 0xF) << 12;
    }
    return hmvmask | vmvmask;
}