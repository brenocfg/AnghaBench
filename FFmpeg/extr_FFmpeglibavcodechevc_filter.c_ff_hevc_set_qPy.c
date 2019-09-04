#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* sps; } ;
struct TYPE_12__ {TYPE_4__* HEVClc; TYPE_2__ ps; } ;
struct TYPE_10__ {scalar_t__ cu_qp_delta; } ;
struct TYPE_11__ {int qp_y; TYPE_3__ tu; } ;
struct TYPE_8__ {int qp_bd_offset; } ;
typedef  TYPE_5__ HEVCContext ;

/* Variables and functions */
 int FFUMOD (scalar_t__,int) ; 
 int get_qPy_pred (TYPE_5__*,int,int,int) ; 

void ff_hevc_set_qPy(HEVCContext *s, int xBase, int yBase, int log2_cb_size)
{
    int qp_y = get_qPy_pred(s, xBase, yBase, log2_cb_size);

    if (s->HEVClc->tu.cu_qp_delta != 0) {
        int off = s->ps.sps->qp_bd_offset;
        s->HEVClc->qp_y = FFUMOD(qp_y + s->HEVClc->tu.cu_qp_delta + 52 + 2 * off,
                                 52 + off) - off;
    } else
        s->HEVClc->qp_y = qp_y;
}