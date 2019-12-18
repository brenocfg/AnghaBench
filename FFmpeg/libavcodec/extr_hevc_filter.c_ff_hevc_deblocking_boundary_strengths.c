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
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_21__ {int /*<<< orphan*/ * refPicList; TYPE_5__* tab_mvf; } ;
struct TYPE_17__ {TYPE_3__* sps; TYPE_2__* pps; } ;
struct TYPE_14__ {int /*<<< orphan*/  slice_loop_filter_across_slices_enabled_flag; } ;
struct TYPE_20__ {int* horizontal_bs; int bs_width; int* vertical_bs; TYPE_9__* ref; scalar_t__* cbf_luma; TYPE_4__ ps; TYPE_1__ sh; TYPE_6__* HEVClc; } ;
struct TYPE_19__ {int boundary_flags; } ;
struct TYPE_18__ {scalar_t__ pred_flag; } ;
struct TYPE_16__ {int log2_min_pu_size; int log2_min_tb_size; int min_pu_width; int min_tb_width; int log2_ctb_size; } ;
struct TYPE_15__ {int /*<<< orphan*/  loop_filter_across_tiles_enabled_flag; } ;
typedef  int /*<<< orphan*/  RefPicList ;
typedef  TYPE_5__ MvField ;
typedef  TYPE_6__ HEVCLocalContext ;
typedef  TYPE_7__ HEVCContext ;

/* Variables and functions */
 int BOUNDARY_LEFT_SLICE ; 
 int BOUNDARY_LEFT_TILE ; 
 int BOUNDARY_UPPER_SLICE ; 
 int BOUNDARY_UPPER_TILE ; 
 scalar_t__ PF_INTRA ; 
 int boundary_strength (TYPE_7__*,TYPE_5__*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ff_hevc_get_ref_list (TYPE_7__*,TYPE_9__*,int,int) ; 

void ff_hevc_deblocking_boundary_strengths(HEVCContext *s, int x0, int y0,
                                           int log2_trafo_size)
{
    HEVCLocalContext *lc = s->HEVClc;
    MvField *tab_mvf     = s->ref->tab_mvf;
    int log2_min_pu_size = s->ps.sps->log2_min_pu_size;
    int log2_min_tu_size = s->ps.sps->log2_min_tb_size;
    int min_pu_width     = s->ps.sps->min_pu_width;
    int min_tu_width     = s->ps.sps->min_tb_width;
    int is_intra = tab_mvf[(y0 >> log2_min_pu_size) * min_pu_width +
                           (x0 >> log2_min_pu_size)].pred_flag == PF_INTRA;
    int boundary_upper, boundary_left;
    int i, j, bs;

    boundary_upper = y0 > 0 && !(y0 & 7);
    if (boundary_upper &&
        ((!s->sh.slice_loop_filter_across_slices_enabled_flag &&
          lc->boundary_flags & BOUNDARY_UPPER_SLICE &&
          (y0 % (1 << s->ps.sps->log2_ctb_size)) == 0) ||
         (!s->ps.pps->loop_filter_across_tiles_enabled_flag &&
          lc->boundary_flags & BOUNDARY_UPPER_TILE &&
          (y0 % (1 << s->ps.sps->log2_ctb_size)) == 0)))
        boundary_upper = 0;

    if (boundary_upper) {
        RefPicList *rpl_top = (lc->boundary_flags & BOUNDARY_UPPER_SLICE) ?
                              ff_hevc_get_ref_list(s, s->ref, x0, y0 - 1) :
                              s->ref->refPicList;
        int yp_pu = (y0 - 1) >> log2_min_pu_size;
        int yq_pu =  y0      >> log2_min_pu_size;
        int yp_tu = (y0 - 1) >> log2_min_tu_size;
        int yq_tu =  y0      >> log2_min_tu_size;

            for (i = 0; i < (1 << log2_trafo_size); i += 4) {
                int x_pu = (x0 + i) >> log2_min_pu_size;
                int x_tu = (x0 + i) >> log2_min_tu_size;
                MvField *top  = &tab_mvf[yp_pu * min_pu_width + x_pu];
                MvField *curr = &tab_mvf[yq_pu * min_pu_width + x_pu];
                uint8_t top_cbf_luma  = s->cbf_luma[yp_tu * min_tu_width + x_tu];
                uint8_t curr_cbf_luma = s->cbf_luma[yq_tu * min_tu_width + x_tu];

                if (curr->pred_flag == PF_INTRA || top->pred_flag == PF_INTRA)
                    bs = 2;
                else if (curr_cbf_luma || top_cbf_luma)
                    bs = 1;
                else
                    bs = boundary_strength(s, curr, top, rpl_top);
                s->horizontal_bs[((x0 + i) + y0 * s->bs_width) >> 2] = bs;
            }
    }

    // bs for vertical TU boundaries
    boundary_left = x0 > 0 && !(x0 & 7);
    if (boundary_left &&
        ((!s->sh.slice_loop_filter_across_slices_enabled_flag &&
          lc->boundary_flags & BOUNDARY_LEFT_SLICE &&
          (x0 % (1 << s->ps.sps->log2_ctb_size)) == 0) ||
         (!s->ps.pps->loop_filter_across_tiles_enabled_flag &&
          lc->boundary_flags & BOUNDARY_LEFT_TILE &&
          (x0 % (1 << s->ps.sps->log2_ctb_size)) == 0)))
        boundary_left = 0;

    if (boundary_left) {
        RefPicList *rpl_left = (lc->boundary_flags & BOUNDARY_LEFT_SLICE) ?
                               ff_hevc_get_ref_list(s, s->ref, x0 - 1, y0) :
                               s->ref->refPicList;
        int xp_pu = (x0 - 1) >> log2_min_pu_size;
        int xq_pu =  x0      >> log2_min_pu_size;
        int xp_tu = (x0 - 1) >> log2_min_tu_size;
        int xq_tu =  x0      >> log2_min_tu_size;

            for (i = 0; i < (1 << log2_trafo_size); i += 4) {
                int y_pu      = (y0 + i) >> log2_min_pu_size;
                int y_tu      = (y0 + i) >> log2_min_tu_size;
                MvField *left = &tab_mvf[y_pu * min_pu_width + xp_pu];
                MvField *curr = &tab_mvf[y_pu * min_pu_width + xq_pu];
                uint8_t left_cbf_luma = s->cbf_luma[y_tu * min_tu_width + xp_tu];
                uint8_t curr_cbf_luma = s->cbf_luma[y_tu * min_tu_width + xq_tu];

                if (curr->pred_flag == PF_INTRA || left->pred_flag == PF_INTRA)
                    bs = 2;
                else if (curr_cbf_luma || left_cbf_luma)
                    bs = 1;
                else
                    bs = boundary_strength(s, curr, left, rpl_left);
                s->vertical_bs[(x0 + (y0 + i) * s->bs_width) >> 2] = bs;
            }
    }

    if (log2_trafo_size > log2_min_pu_size && !is_intra) {
        RefPicList *rpl = s->ref->refPicList;

        // bs for TU internal horizontal PU boundaries
        for (j = 8; j < (1 << log2_trafo_size); j += 8) {
            int yp_pu = (y0 + j - 1) >> log2_min_pu_size;
            int yq_pu = (y0 + j)     >> log2_min_pu_size;

            for (i = 0; i < (1 << log2_trafo_size); i += 4) {
                int x_pu = (x0 + i) >> log2_min_pu_size;
                MvField *top  = &tab_mvf[yp_pu * min_pu_width + x_pu];
                MvField *curr = &tab_mvf[yq_pu * min_pu_width + x_pu];

                bs = boundary_strength(s, curr, top, rpl);
                s->horizontal_bs[((x0 + i) + (y0 + j) * s->bs_width) >> 2] = bs;
            }
        }

        // bs for TU internal vertical PU boundaries
        for (j = 0; j < (1 << log2_trafo_size); j += 4) {
            int y_pu = (y0 + j) >> log2_min_pu_size;

            for (i = 8; i < (1 << log2_trafo_size); i += 8) {
                int xp_pu = (x0 + i - 1) >> log2_min_pu_size;
                int xq_pu = (x0 + i)     >> log2_min_pu_size;
                MvField *left = &tab_mvf[y_pu * min_pu_width + xp_pu];
                MvField *curr = &tab_mvf[y_pu * min_pu_width + xq_pu];

                bs = boundary_strength(s, curr, left, rpl);
                s->vertical_bs[((x0 + i) + (y0 + j) * s->bs_width) >> 2] = bs;
            }
        }
    }
}