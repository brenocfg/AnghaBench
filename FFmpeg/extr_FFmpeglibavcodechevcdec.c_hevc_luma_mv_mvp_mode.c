#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_16__ ;

/* Type definitions */
typedef  enum InterPredIdc { ____Placeholder_InterPredIdc } InterPredIdc ;
struct TYPE_18__ {scalar_t__ slice_type; int mvd_l1_zero_flag; scalar_t__* nb_refs; } ;
struct TYPE_23__ {TYPE_1__ sh; TYPE_5__* HEVClc; } ;
struct TYPE_17__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_20__ {TYPE_16__ mvd; } ;
struct TYPE_22__ {TYPE_3__ pu; } ;
struct TYPE_21__ {TYPE_2__* mv; scalar_t__ pred_flag; void** ref_idx; } ;
struct TYPE_19__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_4__ MvField ;
typedef  TYPE_5__ HEVCLocalContext ;
typedef  TYPE_6__ HEVCContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_ZERO32 (TYPE_16__*) ; 
 scalar_t__ HEVC_SLICE_B ; 
 size_t L0 ; 
 size_t L1 ; 
 scalar_t__ PF_L0 ; 
 scalar_t__ PF_L1 ; 
 int PRED_BI ; 
 int PRED_L0 ; 
 int PRED_L1 ; 
 int /*<<< orphan*/  ff_hevc_hls_mvd_coding (TYPE_6__*,int,int,int) ; 
 int ff_hevc_inter_pred_idc_decode (TYPE_6__*,int,int) ; 
 int /*<<< orphan*/  ff_hevc_luma_mv_mvp_mode (TYPE_6__*,int,int,int,int,int,int,int,TYPE_4__*,int,int) ; 
 int ff_hevc_mvp_lx_flag_decode (TYPE_6__*) ; 
 void* ff_hevc_ref_idx_lx_decode (TYPE_6__*,scalar_t__) ; 
 int /*<<< orphan*/  ff_hevc_set_neighbour_available (TYPE_6__*,int,int,int,int) ; 

__attribute__((used)) static void hevc_luma_mv_mvp_mode(HEVCContext *s, int x0, int y0, int nPbW,
                                  int nPbH, int log2_cb_size, int part_idx,
                                  int merge_idx, MvField *mv)
{
    HEVCLocalContext *lc = s->HEVClc;
    enum InterPredIdc inter_pred_idc = PRED_L0;
    int mvp_flag;

    ff_hevc_set_neighbour_available(s, x0, y0, nPbW, nPbH);
    mv->pred_flag = 0;
    if (s->sh.slice_type == HEVC_SLICE_B)
        inter_pred_idc = ff_hevc_inter_pred_idc_decode(s, nPbW, nPbH);

    if (inter_pred_idc != PRED_L1) {
        if (s->sh.nb_refs[L0])
            mv->ref_idx[0]= ff_hevc_ref_idx_lx_decode(s, s->sh.nb_refs[L0]);

        mv->pred_flag = PF_L0;
        ff_hevc_hls_mvd_coding(s, x0, y0, 0);
        mvp_flag = ff_hevc_mvp_lx_flag_decode(s);
        ff_hevc_luma_mv_mvp_mode(s, x0, y0, nPbW, nPbH, log2_cb_size,
                                 part_idx, merge_idx, mv, mvp_flag, 0);
        mv->mv[0].x += lc->pu.mvd.x;
        mv->mv[0].y += lc->pu.mvd.y;
    }

    if (inter_pred_idc != PRED_L0) {
        if (s->sh.nb_refs[L1])
            mv->ref_idx[1]= ff_hevc_ref_idx_lx_decode(s, s->sh.nb_refs[L1]);

        if (s->sh.mvd_l1_zero_flag == 1 && inter_pred_idc == PRED_BI) {
            AV_ZERO32(&lc->pu.mvd);
        } else {
            ff_hevc_hls_mvd_coding(s, x0, y0, 1);
        }

        mv->pred_flag += PF_L1;
        mvp_flag = ff_hevc_mvp_lx_flag_decode(s);
        ff_hevc_luma_mv_mvp_mode(s, x0, y0, nPbW, nPbH, log2_cb_size,
                                 part_idx, merge_idx, mv, mvp_flag, 1);
        mv->mv[1].x += lc->pu.mvd.x;
        mv->mv[1].y += lc->pu.mvd.y;
    }
}