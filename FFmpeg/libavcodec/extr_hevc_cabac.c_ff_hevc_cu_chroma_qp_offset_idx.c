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
struct TYPE_6__ {TYPE_1__* pps; } ;
struct TYPE_7__ {TYPE_2__ ps; } ;
struct TYPE_5__ {int /*<<< orphan*/  chroma_qp_offset_list_len_minus1; } ;
typedef  TYPE_3__ HEVCContext ;

/* Variables and functions */
 size_t CU_CHROMA_QP_OFFSET_IDX ; 
 int FFMAX (int,int /*<<< orphan*/ ) ; 
 scalar_t__ GET_CABAC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * elem_offset ; 

int ff_hevc_cu_chroma_qp_offset_idx(HEVCContext *s)
{
    int c_max= FFMAX(5, s->ps.pps->chroma_qp_offset_list_len_minus1);
    int i = 0;

    while (i < c_max && GET_CABAC(elem_offset[CU_CHROMA_QP_OFFSET_IDX]))
        i++;

    return i;
}