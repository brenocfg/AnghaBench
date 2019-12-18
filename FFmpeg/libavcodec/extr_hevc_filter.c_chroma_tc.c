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
struct TYPE_8__ {TYPE_2__* sps; TYPE_1__* pps; } ;
struct TYPE_9__ {TYPE_3__ ps; } ;
struct TYPE_7__ {int chroma_format_idc; } ;
struct TYPE_6__ {int cb_qp_offset; int cr_qp_offset; } ;
typedef  TYPE_4__ HEVCContext ;

/* Variables and functions */
 int DEFAULT_INTRA_TC_OFFSET ; 
 int av_clip (int,int /*<<< orphan*/ ,int) ; 
 int* tctable ; 

__attribute__((used)) static int chroma_tc(HEVCContext *s, int qp_y, int c_idx, int tc_offset)
{
    static const int qp_c[] = {
        29, 30, 31, 32, 33, 33, 34, 34, 35, 35, 36, 36, 37, 37
    };
    int qp, qp_i, offset, idxt;

    // slice qp offset is not used for deblocking
    if (c_idx == 1)
        offset = s->ps.pps->cb_qp_offset;
    else
        offset = s->ps.pps->cr_qp_offset;

    qp_i = av_clip(qp_y + offset, 0, 57);
    if (s->ps.sps->chroma_format_idc == 1) {
        if (qp_i < 30)
            qp = qp_i;
        else if (qp_i > 43)
            qp = qp_i - 6;
        else
            qp = qp_c[qp_i - 30];
    } else {
        qp = av_clip(qp_i, 0, 51);
    }

    idxt = av_clip(qp + DEFAULT_INTRA_TC_OFFSET + tc_offset, 0, 53);
    return tctable[idxt];
}