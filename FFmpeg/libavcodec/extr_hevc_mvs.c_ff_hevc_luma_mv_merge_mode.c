#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_1__* pps; } ;
struct TYPE_17__ {TYPE_2__ ps; TYPE_5__* HEVClc; } ;
struct TYPE_14__ {int x; int y; } ;
struct TYPE_16__ {TYPE_3__ cu; } ;
struct TYPE_15__ {scalar_t__ pred_flag; } ;
struct TYPE_12__ {int log2_parallel_merge_level; } ;
typedef  TYPE_4__ MvField ;
typedef  TYPE_5__ HEVCLocalContext ;
typedef  TYPE_6__ HEVCContext ;

/* Variables and functions */
 int MRG_MAX_NUM_CANDS ; 
 scalar_t__ PF_BI ; 
 scalar_t__ PF_L0 ; 
 int /*<<< orphan*/  derive_spatial_merge_candidates (TYPE_6__*,int,int,int,int,int,int,int,int,TYPE_4__*) ; 
 int /*<<< orphan*/  ff_hevc_set_neighbour_available (TYPE_6__*,int,int,int,int) ; 

void ff_hevc_luma_mv_merge_mode(HEVCContext *s, int x0, int y0, int nPbW,
                                int nPbH, int log2_cb_size, int part_idx,
                                int merge_idx, MvField *mv)
{
    int singleMCLFlag = 0;
    int nCS = 1 << log2_cb_size;
    MvField mergecand_list[MRG_MAX_NUM_CANDS];
    int nPbW2 = nPbW;
    int nPbH2 = nPbH;
    HEVCLocalContext *lc = s->HEVClc;

    if (s->ps.pps->log2_parallel_merge_level > 2 && nCS == 8) {
        singleMCLFlag = 1;
        x0            = lc->cu.x;
        y0            = lc->cu.y;
        nPbW          = nCS;
        nPbH          = nCS;
        part_idx      = 0;
    }

    ff_hevc_set_neighbour_available(s, x0, y0, nPbW, nPbH);
    derive_spatial_merge_candidates(s, x0, y0, nPbW, nPbH, log2_cb_size,
                                    singleMCLFlag, part_idx,
                                    merge_idx, mergecand_list);

    if (mergecand_list[merge_idx].pred_flag == PF_BI &&
        (nPbW2 + nPbH2) == 12) {
        mergecand_list[merge_idx].pred_flag = PF_L0;
    }

    *mv = mergecand_list[merge_idx];
}