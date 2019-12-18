#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_22__ {TYPE_2__* pps; TYPE_5__* sps; } ;
struct TYPE_17__ {int /*<<< orphan*/  disable_deblocking_filter_flag; } ;
struct TYPE_25__ {int* cbf_luma; TYPE_6__ ps; TYPE_1__ sh; TYPE_8__* HEVClc; } ;
struct TYPE_23__ {int max_trafo_depth; scalar_t__ pred_mode; scalar_t__ part_mode; scalar_t__ cu_transquant_bypass_flag; scalar_t__ intra_split_flag; } ;
struct TYPE_20__ {int /*<<< orphan*/ * chroma_mode_c; int /*<<< orphan*/ * intra_pred_mode_c; int /*<<< orphan*/ * intra_pred_mode; } ;
struct TYPE_19__ {int /*<<< orphan*/  chroma_mode_c; int /*<<< orphan*/  intra_pred_mode_c; int /*<<< orphan*/  intra_pred_mode; } ;
struct TYPE_24__ {TYPE_7__ cu; TYPE_4__ pu; TYPE_3__ tu; } ;
struct TYPE_21__ {int chroma_format_idc; int log2_max_trafo_size; int log2_min_tb_size; scalar_t__ max_transform_hierarchy_depth_inter; int min_tb_width; } ;
struct TYPE_18__ {scalar_t__ transquant_bypass_enable_flag; } ;
typedef  TYPE_8__ HEVCLocalContext ;
typedef  TYPE_9__ HEVCContext ;

/* Variables and functions */
 scalar_t__ MODE_INTER ; 
 scalar_t__ MODE_INTRA ; 
 scalar_t__ PART_2Nx2N ; 
 int /*<<< orphan*/  SUBDIVIDE (int const,int const,int) ; 
 int ff_hevc_cbf_cb_cr_decode (TYPE_9__*,int) ; 
 int ff_hevc_cbf_luma_decode (TYPE_9__*,int) ; 
 int /*<<< orphan*/  ff_hevc_deblocking_boundary_strengths (TYPE_9__*,int,int,int) ; 
 int ff_hevc_split_transform_flag_decode (TYPE_9__*,int) ; 
 int hls_transform_unit (TYPE_9__*,int,int,int,int,int,int,int,int,int,int,int*,int*) ; 
 int /*<<< orphan*/  set_deblocking_bypass (TYPE_9__*,int,int,int) ; 

__attribute__((used)) static int hls_transform_tree(HEVCContext *s, int x0, int y0,
                              int xBase, int yBase, int cb_xBase, int cb_yBase,
                              int log2_cb_size, int log2_trafo_size,
                              int trafo_depth, int blk_idx,
                              const int *base_cbf_cb, const int *base_cbf_cr)
{
    HEVCLocalContext *lc = s->HEVClc;
    uint8_t split_transform_flag;
    int cbf_cb[2];
    int cbf_cr[2];
    int ret;

    cbf_cb[0] = base_cbf_cb[0];
    cbf_cb[1] = base_cbf_cb[1];
    cbf_cr[0] = base_cbf_cr[0];
    cbf_cr[1] = base_cbf_cr[1];

    if (lc->cu.intra_split_flag) {
        if (trafo_depth == 1) {
            lc->tu.intra_pred_mode   = lc->pu.intra_pred_mode[blk_idx];
            if (s->ps.sps->chroma_format_idc == 3) {
                lc->tu.intra_pred_mode_c = lc->pu.intra_pred_mode_c[blk_idx];
                lc->tu.chroma_mode_c     = lc->pu.chroma_mode_c[blk_idx];
            } else {
                lc->tu.intra_pred_mode_c = lc->pu.intra_pred_mode_c[0];
                lc->tu.chroma_mode_c     = lc->pu.chroma_mode_c[0];
            }
        }
    } else {
        lc->tu.intra_pred_mode   = lc->pu.intra_pred_mode[0];
        lc->tu.intra_pred_mode_c = lc->pu.intra_pred_mode_c[0];
        lc->tu.chroma_mode_c     = lc->pu.chroma_mode_c[0];
    }

    if (log2_trafo_size <= s->ps.sps->log2_max_trafo_size &&
        log2_trafo_size >  s->ps.sps->log2_min_tb_size    &&
        trafo_depth     < lc->cu.max_trafo_depth       &&
        !(lc->cu.intra_split_flag && trafo_depth == 0)) {
        split_transform_flag = ff_hevc_split_transform_flag_decode(s, log2_trafo_size);
    } else {
        int inter_split = s->ps.sps->max_transform_hierarchy_depth_inter == 0 &&
                          lc->cu.pred_mode == MODE_INTER &&
                          lc->cu.part_mode != PART_2Nx2N &&
                          trafo_depth == 0;

        split_transform_flag = log2_trafo_size > s->ps.sps->log2_max_trafo_size ||
                               (lc->cu.intra_split_flag && trafo_depth == 0) ||
                               inter_split;
    }

    if (s->ps.sps->chroma_format_idc && (log2_trafo_size > 2 || s->ps.sps->chroma_format_idc == 3)) {
        if (trafo_depth == 0 || cbf_cb[0]) {
            cbf_cb[0] = ff_hevc_cbf_cb_cr_decode(s, trafo_depth);
            if (s->ps.sps->chroma_format_idc == 2 && (!split_transform_flag || log2_trafo_size == 3)) {
                cbf_cb[1] = ff_hevc_cbf_cb_cr_decode(s, trafo_depth);
            }
        }

        if (trafo_depth == 0 || cbf_cr[0]) {
            cbf_cr[0] = ff_hevc_cbf_cb_cr_decode(s, trafo_depth);
            if (s->ps.sps->chroma_format_idc == 2 && (!split_transform_flag || log2_trafo_size == 3)) {
                cbf_cr[1] = ff_hevc_cbf_cb_cr_decode(s, trafo_depth);
            }
        }
    }

    if (split_transform_flag) {
        const int trafo_size_split = 1 << (log2_trafo_size - 1);
        const int x1 = x0 + trafo_size_split;
        const int y1 = y0 + trafo_size_split;

#define SUBDIVIDE(x, y, idx)                                                    \
do {                                                                            \
    ret = hls_transform_tree(s, x, y, x0, y0, cb_xBase, cb_yBase, log2_cb_size, \
                             log2_trafo_size - 1, trafo_depth + 1, idx,         \
                             cbf_cb, cbf_cr);                                   \
    if (ret < 0)                                                                \
        return ret;                                                             \
} while (0)

        SUBDIVIDE(x0, y0, 0);
        SUBDIVIDE(x1, y0, 1);
        SUBDIVIDE(x0, y1, 2);
        SUBDIVIDE(x1, y1, 3);

#undef SUBDIVIDE
    } else {
        int min_tu_size      = 1 << s->ps.sps->log2_min_tb_size;
        int log2_min_tu_size = s->ps.sps->log2_min_tb_size;
        int min_tu_width     = s->ps.sps->min_tb_width;
        int cbf_luma         = 1;

        if (lc->cu.pred_mode == MODE_INTRA || trafo_depth != 0 ||
            cbf_cb[0] || cbf_cr[0] ||
            (s->ps.sps->chroma_format_idc == 2 && (cbf_cb[1] || cbf_cr[1]))) {
            cbf_luma = ff_hevc_cbf_luma_decode(s, trafo_depth);
        }

        ret = hls_transform_unit(s, x0, y0, xBase, yBase, cb_xBase, cb_yBase,
                                 log2_cb_size, log2_trafo_size,
                                 blk_idx, cbf_luma, cbf_cb, cbf_cr);
        if (ret < 0)
            return ret;
        // TODO: store cbf_luma somewhere else
        if (cbf_luma) {
            int i, j;
            for (i = 0; i < (1 << log2_trafo_size); i += min_tu_size)
                for (j = 0; j < (1 << log2_trafo_size); j += min_tu_size) {
                    int x_tu = (x0 + j) >> log2_min_tu_size;
                    int y_tu = (y0 + i) >> log2_min_tu_size;
                    s->cbf_luma[y_tu * min_tu_width + x_tu] = 1;
                }
        }
        if (!s->sh.disable_deblocking_filter_flag) {
            ff_hevc_deblocking_boundary_strengths(s, x0, y0, log2_trafo_size);
            if (s->ps.pps->transquant_bypass_enable_flag &&
                lc->cu.cu_transquant_bypass_flag)
                set_deblocking_bypass(s, x0, y0, log2_trafo_size);
        }
    }
    return 0;
}