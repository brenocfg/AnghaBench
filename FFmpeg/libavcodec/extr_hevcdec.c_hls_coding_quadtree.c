#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_4__* sps; TYPE_3__* pps; } ;
struct TYPE_12__ {scalar_t__ cu_chroma_qp_offset_enabled_flag; } ;
struct TYPE_18__ {TYPE_5__ ps; TYPE_1__ sh; TYPE_6__* HEVClc; } ;
struct TYPE_13__ {scalar_t__ is_cu_chroma_qp_offset_coded; scalar_t__ cu_qp_delta; scalar_t__ is_cu_qp_delta_coded; } ;
struct TYPE_17__ {int ct_depth; int /*<<< orphan*/  qp_y; int /*<<< orphan*/  qPy_pred; TYPE_2__ tu; } ;
struct TYPE_15__ {int width; int height; int log2_min_cb_size; int log2_ctb_size; } ;
struct TYPE_14__ {int diff_cu_qp_delta_depth; int diff_cu_chroma_qp_offset_depth; scalar_t__ cu_qp_delta_enabled_flag; } ;
typedef  TYPE_6__ HEVCLocalContext ;
typedef  TYPE_7__ HEVCContext ;

/* Variables and functions */
 int ff_hevc_end_of_slice_flag_decode (TYPE_7__*) ; 
 int ff_hevc_split_coding_unit_flag_decode (TYPE_7__*,int,int,int) ; 
 int hls_coding_unit (TYPE_7__*,int,int,int) ; 

__attribute__((used)) static int hls_coding_quadtree(HEVCContext *s, int x0, int y0,
                               int log2_cb_size, int cb_depth)
{
    HEVCLocalContext *lc = s->HEVClc;
    const int cb_size    = 1 << log2_cb_size;
    int ret;
    int split_cu;

    lc->ct_depth = cb_depth;
    if (x0 + cb_size <= s->ps.sps->width  &&
        y0 + cb_size <= s->ps.sps->height &&
        log2_cb_size > s->ps.sps->log2_min_cb_size) {
        split_cu = ff_hevc_split_coding_unit_flag_decode(s, cb_depth, x0, y0);
    } else {
        split_cu = (log2_cb_size > s->ps.sps->log2_min_cb_size);
    }
    if (s->ps.pps->cu_qp_delta_enabled_flag &&
        log2_cb_size >= s->ps.sps->log2_ctb_size - s->ps.pps->diff_cu_qp_delta_depth) {
        lc->tu.is_cu_qp_delta_coded = 0;
        lc->tu.cu_qp_delta          = 0;
    }

    if (s->sh.cu_chroma_qp_offset_enabled_flag &&
        log2_cb_size >= s->ps.sps->log2_ctb_size - s->ps.pps->diff_cu_chroma_qp_offset_depth) {
        lc->tu.is_cu_chroma_qp_offset_coded = 0;
    }

    if (split_cu) {
        int qp_block_mask = (1<<(s->ps.sps->log2_ctb_size - s->ps.pps->diff_cu_qp_delta_depth)) - 1;
        const int cb_size_split = cb_size >> 1;
        const int x1 = x0 + cb_size_split;
        const int y1 = y0 + cb_size_split;

        int more_data = 0;

        more_data = hls_coding_quadtree(s, x0, y0, log2_cb_size - 1, cb_depth + 1);
        if (more_data < 0)
            return more_data;

        if (more_data && x1 < s->ps.sps->width) {
            more_data = hls_coding_quadtree(s, x1, y0, log2_cb_size - 1, cb_depth + 1);
            if (more_data < 0)
                return more_data;
        }
        if (more_data && y1 < s->ps.sps->height) {
            more_data = hls_coding_quadtree(s, x0, y1, log2_cb_size - 1, cb_depth + 1);
            if (more_data < 0)
                return more_data;
        }
        if (more_data && x1 < s->ps.sps->width &&
            y1 < s->ps.sps->height) {
            more_data = hls_coding_quadtree(s, x1, y1, log2_cb_size - 1, cb_depth + 1);
            if (more_data < 0)
                return more_data;
        }

        if(((x0 + (1<<log2_cb_size)) & qp_block_mask) == 0 &&
            ((y0 + (1<<log2_cb_size)) & qp_block_mask) == 0)
            lc->qPy_pred = lc->qp_y;

        if (more_data)
            return ((x1 + cb_size_split) < s->ps.sps->width ||
                    (y1 + cb_size_split) < s->ps.sps->height);
        else
            return 0;
    } else {
        ret = hls_coding_unit(s, x0, y0, log2_cb_size);
        if (ret < 0)
            return ret;
        if ((!((x0 + cb_size) %
               (1 << (s->ps.sps->log2_ctb_size))) ||
             (x0 + cb_size >= s->ps.sps->width)) &&
            (!((y0 + cb_size) %
               (1 << (s->ps.sps->log2_ctb_size))) ||
             (y0 + cb_size >= s->ps.sps->height))) {
            int end_of_slice_flag = ff_hevc_end_of_slice_flag_decode(s);
            return !end_of_slice_flag;
        } else {
            return 1;
        }
    }

    return 0;
}