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
struct bnx2x {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BNX2X_LOOPBACK_FAILED ; 
 int /*<<< orphan*/  BNX2X_MAC_LOOPBACK ; 
 int BNX2X_MAC_LOOPBACK_FAILED ; 
 int /*<<< orphan*/  BNX2X_MSG_ETHTOOL ; 
 int /*<<< orphan*/  BNX2X_PHY_LOOPBACK ; 
 int BNX2X_PHY_LOOPBACK_FAILED ; 
 scalar_t__ BP_NOMCP (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  bnx2x_acquire_phy_lock (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_netif_start (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_netif_stop (struct bnx2x*,int) ; 
 int /*<<< orphan*/  bnx2x_release_phy_lock (struct bnx2x*) ; 
 int bnx2x_run_loopback (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnx2x_test_loopback(struct bnx2x *bp)
{
	int rc = 0, res;

	if (BP_NOMCP(bp))
		return rc;

	if (!netif_running(bp->dev))
		return BNX2X_LOOPBACK_FAILED;

	bnx2x_netif_stop(bp, 1);
	bnx2x_acquire_phy_lock(bp);

	res = bnx2x_run_loopback(bp, BNX2X_PHY_LOOPBACK);
	if (res) {
		DP(BNX2X_MSG_ETHTOOL, "  PHY loopback failed  (res %d)\n", res);
		rc |= BNX2X_PHY_LOOPBACK_FAILED;
	}

	res = bnx2x_run_loopback(bp, BNX2X_MAC_LOOPBACK);
	if (res) {
		DP(BNX2X_MSG_ETHTOOL, "  MAC loopback failed  (res %d)\n", res);
		rc |= BNX2X_MAC_LOOPBACK_FAILED;
	}

	bnx2x_release_phy_lock(bp);
	bnx2x_netif_start(bp);

	return rc;
}