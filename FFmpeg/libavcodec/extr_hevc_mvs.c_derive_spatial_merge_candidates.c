#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct MvField {int pred_flag; size_t* ref_idx; void** mv; } ;
struct TYPE_14__ {scalar_t__ slice_type; int* nb_refs; int max_num_merge_cand; scalar_t__ slice_temporal_mvp_enabled_flag; } ;
struct TYPE_17__ {TYPE_4__* sps; } ;
struct TYPE_21__ {TYPE_2__ sh; TYPE_5__ ps; TYPE_3__* ref; TYPE_8__* HEVClc; } ;
struct TYPE_13__ {scalar_t__ part_mode; } ;
struct TYPE_18__ {int cand_bottom_left; int cand_left; int cand_up_left; int cand_up; int cand_up_right_sap; } ;
struct TYPE_20__ {TYPE_1__ cu; TYPE_6__ na; } ;
struct TYPE_19__ {scalar_t__* list; } ;
struct TYPE_16__ {int min_pu_width; int const width; int const height; } ;
struct TYPE_15__ {struct MvField* tab_mvf; TYPE_7__* refPicList; } ;
typedef  TYPE_7__ RefPicList ;
typedef  struct MvField MvField ;
typedef  void* Mv ;
typedef  TYPE_8__ HEVCLocalContext ;
typedef  TYPE_9__ HEVCContext ;

/* Variables and functions */
 int /*<<< orphan*/  A0 ; 
 int /*<<< orphan*/  A1 ; 
 int AVAILABLE (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_COPY32 (void**,void**) ; 
 scalar_t__ AV_RN32A (void**) ; 
 int /*<<< orphan*/  AV_ZERO16 (size_t*) ; 
 int /*<<< orphan*/  AV_ZERO32 (void**) ; 
 int /*<<< orphan*/  B0 ; 
 int /*<<< orphan*/  B1 ; 
 int /*<<< orphan*/  B2 ; 
 scalar_t__ COMPARE_MV_REFIDX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FFMIN (int,int) ; 
 scalar_t__ HEVC_SLICE_B ; 
 scalar_t__ HEVC_SLICE_P ; 
 scalar_t__ PART_2NxN ; 
 scalar_t__ PART_2NxnD ; 
 scalar_t__ PART_2NxnU ; 
 scalar_t__ PART_Nx2N ; 
 scalar_t__ PART_nLx2N ; 
 scalar_t__ PART_nRx2N ; 
 int PF_BI ; 
 int PF_L0 ; 
 int PF_L1 ; 
 scalar_t__ PRED_BLOCK_AVAILABLE (int /*<<< orphan*/ ) ; 
 struct MvField TAB_MVF_PU (int /*<<< orphan*/ ) ; 
 scalar_t__ is_diff_mer (TYPE_9__*,int const,int const,int,int) ; 
 int** l0_l1_cand_idx ; 
 int temporal_luma_motion_vector (TYPE_9__*,int,int,int,int,int /*<<< orphan*/ ,void**,int) ; 

__attribute__((used)) static void derive_spatial_merge_candidates(HEVCContext *s, int x0, int y0,
                                            int nPbW, int nPbH,
                                            int log2_cb_size,
                                            int singleMCLFlag, int part_idx,
                                            int merge_idx,
                                            struct MvField mergecandlist[])
{
    HEVCLocalContext *lc   = s->HEVClc;
    RefPicList *refPicList = s->ref->refPicList;
    MvField *tab_mvf       = s->ref->tab_mvf;

    const int min_pu_width = s->ps.sps->min_pu_width;

    const int cand_bottom_left = lc->na.cand_bottom_left;
    const int cand_left        = lc->na.cand_left;
    const int cand_up_left     = lc->na.cand_up_left;
    const int cand_up          = lc->na.cand_up;
    const int cand_up_right    = lc->na.cand_up_right_sap;

    const int xA1    = x0 - 1;
    const int yA1    = y0 + nPbH - 1;

    const int xB1    = x0 + nPbW - 1;
    const int yB1    = y0 - 1;

    const int xB0    = x0 + nPbW;
    const int yB0    = y0 - 1;

    const int xA0    = x0 - 1;
    const int yA0    = y0 + nPbH;

    const int xB2    = x0 - 1;
    const int yB2    = y0 - 1;

    const int nb_refs = (s->sh.slice_type == HEVC_SLICE_P) ?
                        s->sh.nb_refs[0] : FFMIN(s->sh.nb_refs[0], s->sh.nb_refs[1]);

    int zero_idx = 0;

    int nb_merge_cand = 0;
    int nb_orig_merge_cand = 0;

    int is_available_a0;
    int is_available_a1;
    int is_available_b0;
    int is_available_b1;
    int is_available_b2;


    if (!singleMCLFlag && part_idx == 1 &&
        (lc->cu.part_mode == PART_Nx2N ||
         lc->cu.part_mode == PART_nLx2N ||
         lc->cu.part_mode == PART_nRx2N) ||
        is_diff_mer(s, xA1, yA1, x0, y0)) {
        is_available_a1 = 0;
    } else {
        is_available_a1 = AVAILABLE(cand_left, A1);
        if (is_available_a1) {
            mergecandlist[nb_merge_cand] = TAB_MVF_PU(A1);
            if (merge_idx == 0)
                return;
            nb_merge_cand++;
        }
    }

    if (!singleMCLFlag && part_idx == 1 &&
        (lc->cu.part_mode == PART_2NxN ||
         lc->cu.part_mode == PART_2NxnU ||
         lc->cu.part_mode == PART_2NxnD) ||
        is_diff_mer(s, xB1, yB1, x0, y0)) {
        is_available_b1 = 0;
    } else {
        is_available_b1 = AVAILABLE(cand_up, B1);
        if (is_available_b1 &&
            !(is_available_a1 && COMPARE_MV_REFIDX(B1, A1))) {
            mergecandlist[nb_merge_cand] = TAB_MVF_PU(B1);
            if (merge_idx == nb_merge_cand)
                return;
            nb_merge_cand++;
        }
    }

    // above right spatial merge candidate
    is_available_b0 = AVAILABLE(cand_up_right, B0) &&
                      xB0 < s->ps.sps->width &&
                      PRED_BLOCK_AVAILABLE(B0) &&
                      !is_diff_mer(s, xB0, yB0, x0, y0);

    if (is_available_b0 &&
        !(is_available_b1 && COMPARE_MV_REFIDX(B0, B1))) {
        mergecandlist[nb_merge_cand] = TAB_MVF_PU(B0);
        if (merge_idx == nb_merge_cand)
            return;
        nb_merge_cand++;
    }

    // left bottom spatial merge candidate
    is_available_a0 = AVAILABLE(cand_bottom_left, A0) &&
                      yA0 < s->ps.sps->height &&
                      PRED_BLOCK_AVAILABLE(A0) &&
                      !is_diff_mer(s, xA0, yA0, x0, y0);

    if (is_available_a0 &&
        !(is_available_a1 && COMPARE_MV_REFIDX(A0, A1))) {
        mergecandlist[nb_merge_cand] = TAB_MVF_PU(A0);
        if (merge_idx == nb_merge_cand)
            return;
        nb_merge_cand++;
    }

    // above left spatial merge candidate
    is_available_b2 = AVAILABLE(cand_up_left, B2) &&
                      !is_diff_mer(s, xB2, yB2, x0, y0);

    if (is_available_b2 &&
        !(is_available_a1 && COMPARE_MV_REFIDX(B2, A1)) &&
        !(is_available_b1 && COMPARE_MV_REFIDX(B2, B1)) &&
        nb_merge_cand != 4) {
        mergecandlist[nb_merge_cand] = TAB_MVF_PU(B2);
        if (merge_idx == nb_merge_cand)
            return;
        nb_merge_cand++;
    }

    // temporal motion vector candidate
    if (s->sh.slice_temporal_mvp_enabled_flag &&
        nb_merge_cand < s->sh.max_num_merge_cand) {
        Mv mv_l0_col = { 0 }, mv_l1_col = { 0 };
        int available_l0 = temporal_luma_motion_vector(s, x0, y0, nPbW, nPbH,
                                                       0, &mv_l0_col, 0);
        int available_l1 = (s->sh.slice_type == HEVC_SLICE_B) ?
                           temporal_luma_motion_vector(s, x0, y0, nPbW, nPbH,
                                                       0, &mv_l1_col, 1) : 0;

        if (available_l0 || available_l1) {
            mergecandlist[nb_merge_cand].pred_flag = available_l0 + (available_l1 << 1);
            AV_ZERO16(mergecandlist[nb_merge_cand].ref_idx);
            mergecandlist[nb_merge_cand].mv[0]      = mv_l0_col;
            mergecandlist[nb_merge_cand].mv[1]      = mv_l1_col;

            if (merge_idx == nb_merge_cand)
                return;
            nb_merge_cand++;
        }
    }

    nb_orig_merge_cand = nb_merge_cand;

    // combined bi-predictive merge candidates  (applies for B slices)
    if (s->sh.slice_type == HEVC_SLICE_B && nb_orig_merge_cand > 1 &&
        nb_orig_merge_cand < s->sh.max_num_merge_cand) {
        int comb_idx = 0;

        for (comb_idx = 0; nb_merge_cand < s->sh.max_num_merge_cand &&
                           comb_idx < nb_orig_merge_cand * (nb_orig_merge_cand - 1); comb_idx++) {
            int l0_cand_idx = l0_l1_cand_idx[comb_idx][0];
            int l1_cand_idx = l0_l1_cand_idx[comb_idx][1];
            MvField l0_cand = mergecandlist[l0_cand_idx];
            MvField l1_cand = mergecandlist[l1_cand_idx];

            if ((l0_cand.pred_flag & PF_L0) && (l1_cand.pred_flag & PF_L1) &&
                (refPicList[0].list[l0_cand.ref_idx[0]] !=
                 refPicList[1].list[l1_cand.ref_idx[1]] ||
                 AV_RN32A(&l0_cand.mv[0]) != AV_RN32A(&l1_cand.mv[1]))) {
                mergecandlist[nb_merge_cand].ref_idx[0]   = l0_cand.ref_idx[0];
                mergecandlist[nb_merge_cand].ref_idx[1]   = l1_cand.ref_idx[1];
                mergecandlist[nb_merge_cand].pred_flag    = PF_BI;
                AV_COPY32(&mergecandlist[nb_merge_cand].mv[0], &l0_cand.mv[0]);
                AV_COPY32(&mergecandlist[nb_merge_cand].mv[1], &l1_cand.mv[1]);
                if (merge_idx == nb_merge_cand)
                    return;
                nb_merge_cand++;
            }
        }
    }

    // append Zero motion vector candidates
    while (nb_merge_cand < s->sh.max_num_merge_cand) {
        mergecandlist[nb_merge_cand].pred_flag    = PF_L0 + ((s->sh.slice_type == HEVC_SLICE_B) << 1);
        AV_ZERO32(mergecandlist[nb_merge_cand].mv + 0);
        AV_ZERO32(mergecandlist[nb_merge_cand].mv + 1);
        mergecandlist[nb_merge_cand].ref_idx[0]   = zero_idx < nb_refs ? zero_idx : 0;
        mergecandlist[nb_merge_cand].ref_idx[1]   = zero_idx < nb_refs ? zero_idx : 0;

        if (merge_idx == nb_merge_cand)
            return;
        nb_merge_cand++;
        zero_idx++;
    }
}