#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int int8_t ;
struct TYPE_8__ {TYPE_1__* sps; } ;
struct TYPE_10__ {TYPE_2__ ps; } ;
struct TYPE_9__ {scalar_t__ slice_type_nos; size_t cabac_init_idc; int* cabac_state; scalar_t__ qscale; } ;
struct TYPE_7__ {int bit_depth_luma; } ;
typedef  TYPE_3__ H264SliceContext ;
typedef  TYPE_4__ H264Context ;

/* Variables and functions */
 scalar_t__ AV_PICTURE_TYPE_I ; 
 int av_clip (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int** cabac_context_init_I ; 
 int*** cabac_context_init_PB ; 

void ff_h264_init_cabac_states(const H264Context *h, H264SliceContext *sl)
{
    int i;
    const int8_t (*tab)[2];
    const int slice_qp = av_clip(sl->qscale - 6*(h->ps.sps->bit_depth_luma-8), 0, 51);

    if (sl->slice_type_nos == AV_PICTURE_TYPE_I) tab = cabac_context_init_I;
    else                                 tab = cabac_context_init_PB[sl->cabac_init_idc];

    /* calculate pre-state */
    for( i= 0; i < 1024; i++ ) {
        int pre = 2*(((tab[i][0] * slice_qp) >>4 ) + tab[i][1]) - 127;

        pre^= pre>>31;
        if(pre > 124)
            pre= 124 + (pre&1);

        sl->cabac_state[i] =  pre;
    }
}