#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct bnx2x_fp_txdata {int txq_index; int /*<<< orphan*/  cid; int /*<<< orphan*/  tx_ring_size; struct bnx2x_fastpath* parent_fp; int /*<<< orphan*/ * tx_cons_sb; } ;
struct bnx2x_fastpath {int dummy; } ;
struct bnx2x {int /*<<< orphan*/  tx_ring_size; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ IS_FCOE_FP (struct bnx2x_fastpath*) ; 
 int /*<<< orphan*/  MAX_TX_AVAIL ; 
 int /*<<< orphan*/  NETIF_MSG_IFUP ; 

__attribute__((used)) static inline void bnx2x_init_txdata(struct bnx2x *bp,
				     struct bnx2x_fp_txdata *txdata, u32 cid,
				     int txq_index, __le16 *tx_cons_sb,
				     struct bnx2x_fastpath *fp)
{
	txdata->cid = cid;
	txdata->txq_index = txq_index;
	txdata->tx_cons_sb = tx_cons_sb;
	txdata->parent_fp = fp;
	txdata->tx_ring_size = IS_FCOE_FP(fp) ? MAX_TX_AVAIL : bp->tx_ring_size;

	DP(NETIF_MSG_IFUP, "created tx data cid %d, txq %d\n",
	   txdata->cid, txdata->txq_index);
}