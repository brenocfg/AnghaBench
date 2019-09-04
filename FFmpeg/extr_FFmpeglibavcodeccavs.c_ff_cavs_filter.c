#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  enum cavs_mb { ____Placeholder_cavs_mb } cavs_mb ;
struct TYPE_4__ {int /*<<< orphan*/  (* cavs_filter_ch ) (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* cavs_filter_lh ) (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* cavs_filter_lv ) (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* cavs_filter_cv ) (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int mbx; int l_stride; int c_stride; int flags; int qp; int left_qp; int* top_qp; int /*<<< orphan*/ * cv; TYPE_1__ cdsp; int /*<<< orphan*/ * cu; int /*<<< orphan*/ * cy; int /*<<< orphan*/ * mv; int /*<<< orphan*/  loop_filter_disable; int /*<<< orphan*/ * left_border_v; int /*<<< orphan*/ * left_border_u; int /*<<< orphan*/ * left_border_y; int /*<<< orphan*/ * top_border_v; int /*<<< orphan*/ * top_border_u; int /*<<< orphan*/ * top_border_y; int /*<<< orphan*/  topleft_border_v; int /*<<< orphan*/  topleft_border_u; int /*<<< orphan*/  topleft_border_y; } ;
typedef  TYPE_2__ AVSContext ;

/* Variables and functions */
 scalar_t__ AV_RN64 (int /*<<< orphan*/ *) ; 
 int A_AVAIL ; 
 int B_AVAIL ; 
 int I_8X8 ; 
 size_t MV_FWD_A1 ; 
 size_t MV_FWD_A3 ; 
 size_t MV_FWD_B2 ; 
 size_t MV_FWD_B3 ; 
 size_t MV_FWD_X0 ; 
 size_t MV_FWD_X1 ; 
 size_t MV_FWD_X2 ; 
 size_t MV_FWD_X3 ; 
 int P_8X8 ; 
 int /*<<< orphan*/  SET_PARAMS ; 
 int SPLITH ; 
 int SPLITV ; 
 int* ff_cavs_chroma_qp ; 
 int* ff_cavs_partition_flags ; 
 int /*<<< orphan*/  get_bs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ff_cavs_filter(AVSContext *h, enum cavs_mb mb_type)
{
    uint8_t bs[8];
    int qp_avg, alpha, beta, tc;
    int i;

    /* save un-deblocked lines */
    h->topleft_border_y = h->top_border_y[h->mbx * 16 + 15];
    h->topleft_border_u = h->top_border_u[h->mbx * 10 + 8];
    h->topleft_border_v = h->top_border_v[h->mbx * 10 + 8];
    memcpy(&h->top_border_y[h->mbx * 16],     h->cy + 15 * h->l_stride, 16);
    memcpy(&h->top_border_u[h->mbx * 10 + 1], h->cu +  7 * h->c_stride, 8);
    memcpy(&h->top_border_v[h->mbx * 10 + 1], h->cv +  7 * h->c_stride, 8);
    for (i = 0; i < 8; i++) {
        h->left_border_y[i * 2 + 1] = *(h->cy + 15 + (i * 2 + 0) * h->l_stride);
        h->left_border_y[i * 2 + 2] = *(h->cy + 15 + (i * 2 + 1) * h->l_stride);
        h->left_border_u[i + 1]     = *(h->cu + 7  +  i          * h->c_stride);
        h->left_border_v[i + 1]     = *(h->cv + 7  +  i          * h->c_stride);
    }
    if (!h->loop_filter_disable) {
        /* determine bs */
        if (mb_type == I_8X8)
            memset(bs, 2, 8);
        else {
            memset(bs, 0, 8);
            if (ff_cavs_partition_flags[mb_type] & SPLITV) {
                bs[2] = get_bs(&h->mv[MV_FWD_X0], &h->mv[MV_FWD_X1], mb_type > P_8X8);
                bs[3] = get_bs(&h->mv[MV_FWD_X2], &h->mv[MV_FWD_X3], mb_type > P_8X8);
            }
            if (ff_cavs_partition_flags[mb_type] & SPLITH) {
                bs[6] = get_bs(&h->mv[MV_FWD_X0], &h->mv[MV_FWD_X2], mb_type > P_8X8);
                bs[7] = get_bs(&h->mv[MV_FWD_X1], &h->mv[MV_FWD_X3], mb_type > P_8X8);
            }
            bs[0] = get_bs(&h->mv[MV_FWD_A1], &h->mv[MV_FWD_X0], mb_type > P_8X8);
            bs[1] = get_bs(&h->mv[MV_FWD_A3], &h->mv[MV_FWD_X2], mb_type > P_8X8);
            bs[4] = get_bs(&h->mv[MV_FWD_B2], &h->mv[MV_FWD_X0], mb_type > P_8X8);
            bs[5] = get_bs(&h->mv[MV_FWD_B3], &h->mv[MV_FWD_X1], mb_type > P_8X8);
        }
        if (AV_RN64(bs)) {
            if (h->flags & A_AVAIL) {
                qp_avg = (h->qp + h->left_qp + 1) >> 1;
                SET_PARAMS;
                h->cdsp.cavs_filter_lv(h->cy, h->l_stride, alpha, beta, tc, bs[0], bs[1]);
                qp_avg = (ff_cavs_chroma_qp[h->qp] + ff_cavs_chroma_qp[h->left_qp] + 1) >> 1;
                SET_PARAMS;
                h->cdsp.cavs_filter_cv(h->cu, h->c_stride, alpha, beta, tc, bs[0], bs[1]);
                h->cdsp.cavs_filter_cv(h->cv, h->c_stride, alpha, beta, tc, bs[0], bs[1]);
            }
            qp_avg = h->qp;
            SET_PARAMS;
            h->cdsp.cavs_filter_lv(h->cy + 8,               h->l_stride, alpha, beta, tc, bs[2], bs[3]);
            h->cdsp.cavs_filter_lh(h->cy + 8 * h->l_stride, h->l_stride, alpha, beta, tc, bs[6], bs[7]);

            if (h->flags & B_AVAIL) {
                qp_avg = (h->qp + h->top_qp[h->mbx] + 1) >> 1;
                SET_PARAMS;
                h->cdsp.cavs_filter_lh(h->cy, h->l_stride, alpha, beta, tc, bs[4], bs[5]);
                qp_avg = (ff_cavs_chroma_qp[h->qp] + ff_cavs_chroma_qp[h->top_qp[h->mbx]] + 1) >> 1;
                SET_PARAMS;
                h->cdsp.cavs_filter_ch(h->cu, h->c_stride, alpha, beta, tc, bs[4], bs[5]);
                h->cdsp.cavs_filter_ch(h->cv, h->c_stride, alpha, beta, tc, bs[4], bs[5]);
            }
        }
    }
    h->left_qp        = h->qp;
    h->top_qp[h->mbx] = h->qp;
}