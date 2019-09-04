#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_4__* sps; TYPE_1__* pps; } ;
struct TYPE_11__ {int slice_qp; } ;
struct TYPE_15__ {int* qp_y_tab; TYPE_5__ ps; TYPE_3__ sh; TYPE_6__* HEVClc; } ;
struct TYPE_10__ {int /*<<< orphan*/  is_cu_qp_delta_coded; } ;
struct TYPE_14__ {int first_qp_group; int qPy_pred; TYPE_2__ tu; } ;
struct TYPE_12__ {int log2_ctb_size; int min_cb_width; int log2_min_cb_size; int qp_bd_offset; } ;
struct TYPE_9__ {int diff_cu_qp_delta_depth; } ;
typedef  TYPE_6__ HEVCLocalContext ;
typedef  TYPE_7__ HEVCContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert2 (int) ; 

__attribute__((used)) static int get_qPy_pred(HEVCContext *s, int xBase, int yBase, int log2_cb_size)
{
    HEVCLocalContext *lc     = s->HEVClc;
    int ctb_size_mask        = (1 << s->ps.sps->log2_ctb_size) - 1;
    int MinCuQpDeltaSizeMask = (1 << (s->ps.sps->log2_ctb_size -
                                      s->ps.pps->diff_cu_qp_delta_depth)) - 1;
    int xQgBase              = xBase - (xBase & MinCuQpDeltaSizeMask);
    int yQgBase              = yBase - (yBase & MinCuQpDeltaSizeMask);
    int min_cb_width         = s->ps.sps->min_cb_width;
    int x_cb                 = xQgBase >> s->ps.sps->log2_min_cb_size;
    int y_cb                 = yQgBase >> s->ps.sps->log2_min_cb_size;
    int availableA           = (xBase   & ctb_size_mask) &&
                               (xQgBase & ctb_size_mask);
    int availableB           = (yBase   & ctb_size_mask) &&
                               (yQgBase & ctb_size_mask);
    int qPy_pred, qPy_a, qPy_b;

    // qPy_pred
    if (lc->first_qp_group || (!xQgBase && !yQgBase)) {
        lc->first_qp_group = !lc->tu.is_cu_qp_delta_coded;
        qPy_pred = s->sh.slice_qp;
    } else {
        qPy_pred = lc->qPy_pred;
    }

    // qPy_a
    if (availableA == 0)
        qPy_a = qPy_pred;
    else
        qPy_a = s->qp_y_tab[(x_cb - 1) + y_cb * min_cb_width];

    // qPy_b
    if (availableB == 0)
        qPy_b = qPy_pred;
    else
        qPy_b = s->qp_y_tab[x_cb + (y_cb - 1) * min_cb_width];

    av_assert2(qPy_a >= -s->ps.sps->qp_bd_offset && qPy_a < 52);
    av_assert2(qPy_b >= -s->ps.sps->qp_bd_offset && qPy_b < 52);

    return (qPy_a + qPy_b + 1) >> 1;
}