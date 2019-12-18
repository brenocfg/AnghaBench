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
struct bnx2x {int max_cos; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,int) ; 
 int BNX2X_NUM_ETH_QUEUES (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  NETIF_MSG_IFUP ; 
 int /*<<< orphan*/  NO_FCOE (struct bnx2x*) ; 
 int netif_set_real_num_rx_queues (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_set_real_num_tx_queues (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bnx2x_set_real_num_queues(struct bnx2x *bp, int include_cnic)
{
	int rc, tx, rx;

	tx = BNX2X_NUM_ETH_QUEUES(bp) * bp->max_cos;
	rx = BNX2X_NUM_ETH_QUEUES(bp);

/* account for fcoe queue */
	if (include_cnic && !NO_FCOE(bp)) {
		rx++;
		tx++;
	}

	netif_set_real_num_tx_queues(bp->dev, tx);

	rc = netif_set_real_num_rx_queues(bp->dev, rx);
	if (rc) {
		BNX2X_ERR("Failed to set real number of Rx queues: %d\n", rc);
		return rc;
	}

	DP(NETIF_MSG_IFUP, "Setting real num queues to (tx, rx) (%d, %d)\n",
			  tx, rx);

	return rc;
}