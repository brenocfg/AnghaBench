#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ ref_frame; int dc_coeff; } ;
typedef  TYPE_3__ VP56RefDc ;
typedef  scalar_t__ VP56Frame ;
struct TYPE_9__ {int* idct_scantable; size_t* above_block_idx; int** prev_dc; int** block_coeff; int dequant_dc; TYPE_2__* avctx; TYPE_3__* left_block; TYPE_3__* above_blocks; } ;
typedef  TYPE_4__ VP56Context ;
struct TYPE_7__ {TYPE_1__* codec; } ;
struct TYPE_6__ {scalar_t__ id; } ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_VP5 ; 
 size_t* ff_vp56_b2p ; 
 size_t* ff_vp56_b6to4 ; 

__attribute__((used)) static void vp56_add_predictors_dc(VP56Context *s, VP56Frame ref_frame)
{
    int idx = s->idct_scantable[0];
    int b;

    for (b=0; b<6; b++) {
        VP56RefDc *ab = &s->above_blocks[s->above_block_idx[b]];
        VP56RefDc *lb = &s->left_block[ff_vp56_b6to4[b]];
        int count = 0;
        int dc = 0;
        int i;

        if (ref_frame == lb->ref_frame) {
            dc += lb->dc_coeff;
            count++;
        }
        if (ref_frame == ab->ref_frame) {
            dc += ab->dc_coeff;
            count++;
        }
        if (s->avctx->codec->id == AV_CODEC_ID_VP5)
            for (i=0; i<2; i++)
                if (count < 2 && ref_frame == ab[-1+2*i].ref_frame) {
                    dc += ab[-1+2*i].dc_coeff;
                    count++;
                }
        if (count == 0)
            dc = s->prev_dc[ff_vp56_b2p[b]][ref_frame];
        else if (count == 2)
            dc /= 2;

        s->block_coeff[b][idx] += dc;
        s->prev_dc[ff_vp56_b2p[b]][ref_frame] = s->block_coeff[b][idx];
        ab->dc_coeff = s->block_coeff[b][idx];
        ab->ref_frame = ref_frame;
        lb->dc_coeff = s->block_coeff[b][idx];
        lb->ref_frame = ref_frame;
        s->block_coeff[b][idx] *= s->dequant_dc;
    }
}