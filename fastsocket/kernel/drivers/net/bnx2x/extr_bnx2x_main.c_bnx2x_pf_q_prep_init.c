#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct TYPE_7__ {int hc_rate; int /*<<< orphan*/  sb_cq_index; int /*<<< orphan*/  fw_sb_id; int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {int hc_rate; int /*<<< orphan*/  sb_cq_index; int /*<<< orphan*/  fw_sb_id; int /*<<< orphan*/  flags; } ;
struct bnx2x_queue_init_params {size_t max_cos; int /*<<< orphan*/ ** cxts; TYPE_2__ tx; TYPE_1__ rx; } ;
struct bnx2x_fastpath {size_t max_cos; TYPE_3__** txdata_ptr; int /*<<< orphan*/  index; int /*<<< orphan*/  fw_sb_id; } ;
struct bnx2x {int rx_ticks; int tx_ticks; TYPE_5__* context; } ;
struct TYPE_10__ {TYPE_4__* vcxt; } ;
struct TYPE_9__ {int /*<<< orphan*/  eth; } ;
struct TYPE_8__ {int cid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_Q_FLG_HC ; 
 int /*<<< orphan*/  BNX2X_Q_FLG_HC_EN ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,size_t) ; 
 size_t FIRST_TX_COS_INDEX ; 
 int /*<<< orphan*/  HC_INDEX_ETH_FIRST_TX_CQ_CONS ; 
 int /*<<< orphan*/  HC_INDEX_ETH_RX_CQ_CONS ; 
 int ILT_PAGE_CIDS ; 
 int /*<<< orphan*/  IS_FCOE_FP (struct bnx2x_fastpath*) ; 
 int /*<<< orphan*/  NETIF_MSG_IFUP ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bnx2x_pf_q_prep_init(struct bnx2x *bp,
	struct bnx2x_fastpath *fp, struct bnx2x_queue_init_params *init_params)
{
	u8 cos;
	int cxt_index, cxt_offset;

	/* FCoE Queue uses Default SB, thus has no HC capabilities */
	if (!IS_FCOE_FP(fp)) {
		__set_bit(BNX2X_Q_FLG_HC, &init_params->rx.flags);
		__set_bit(BNX2X_Q_FLG_HC, &init_params->tx.flags);

		/* If HC is supported, enable host coalescing in the transition
		 * to INIT state.
		 */
		__set_bit(BNX2X_Q_FLG_HC_EN, &init_params->rx.flags);
		__set_bit(BNX2X_Q_FLG_HC_EN, &init_params->tx.flags);

		/* HC rate */
		init_params->rx.hc_rate = bp->rx_ticks ?
			(1000000 / bp->rx_ticks) : 0;
		init_params->tx.hc_rate = bp->tx_ticks ?
			(1000000 / bp->tx_ticks) : 0;

		/* FW SB ID */
		init_params->rx.fw_sb_id = init_params->tx.fw_sb_id =
			fp->fw_sb_id;

		/*
		 * CQ index among the SB indices: FCoE clients uses the default
		 * SB, therefore it's different.
		 */
		init_params->rx.sb_cq_index = HC_INDEX_ETH_RX_CQ_CONS;
		init_params->tx.sb_cq_index = HC_INDEX_ETH_FIRST_TX_CQ_CONS;
	}

	/* set maximum number of COSs supported by this queue */
	init_params->max_cos = fp->max_cos;

	DP(NETIF_MSG_IFUP, "fp: %d setting queue params max cos to: %d\n",
	    fp->index, init_params->max_cos);

	/* set the context pointers queue object */
	for (cos = FIRST_TX_COS_INDEX; cos < init_params->max_cos; cos++) {
		cxt_index = fp->txdata_ptr[cos]->cid / ILT_PAGE_CIDS;
		cxt_offset = fp->txdata_ptr[cos]->cid - (cxt_index *
				ILT_PAGE_CIDS);
		init_params->cxts[cos] =
			&bp->context[cxt_index].vcxt[cxt_offset].eth;
	}
}