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
typedef  int u64 ;
struct net_device {int dummy; } ;
struct ethtool_test {int flags; } ;
struct bnx2 {int /*<<< orphan*/  dev; scalar_t__ link_up; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2_DRV_MSG_CODE_DIAG ; 
 int BNX2_NUM_TESTS ; 
 int ETH_TEST_FL_FAILED ; 
 int ETH_TEST_FL_OFFLINE ; 
 int /*<<< orphan*/  PCI_D0 ; 
 int /*<<< orphan*/  PCI_D3hot ; 
 int /*<<< orphan*/  bnx2_free_skbs (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_init_nic (struct bnx2*,int) ; 
 int /*<<< orphan*/  bnx2_netif_start (struct bnx2*,int) ; 
 int /*<<< orphan*/  bnx2_netif_stop (struct bnx2*,int) ; 
 int /*<<< orphan*/  bnx2_reset_chip (struct bnx2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2_set_power_state (struct bnx2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2_shutdown_chip (struct bnx2*) ; 
 scalar_t__ bnx2_test_intr (struct bnx2*) ; 
 scalar_t__ bnx2_test_link (struct bnx2*) ; 
 int bnx2_test_loopback (struct bnx2*) ; 
 scalar_t__ bnx2_test_memory (struct bnx2*) ; 
 scalar_t__ bnx2_test_nvram (struct bnx2*) ; 
 scalar_t__ bnx2_test_registers (struct bnx2*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 struct bnx2* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bnx2_self_test(struct net_device *dev, struct ethtool_test *etest, u64 *buf)
{
	struct bnx2 *bp = netdev_priv(dev);

	bnx2_set_power_state(bp, PCI_D0);

	memset(buf, 0, sizeof(u64) * BNX2_NUM_TESTS);
	if (etest->flags & ETH_TEST_FL_OFFLINE) {
		int i;

		bnx2_netif_stop(bp, true);
		bnx2_reset_chip(bp, BNX2_DRV_MSG_CODE_DIAG);
		bnx2_free_skbs(bp);

		if (bnx2_test_registers(bp) != 0) {
			buf[0] = 1;
			etest->flags |= ETH_TEST_FL_FAILED;
		}
		if (bnx2_test_memory(bp) != 0) {
			buf[1] = 1;
			etest->flags |= ETH_TEST_FL_FAILED;
		}
		if ((buf[2] = bnx2_test_loopback(bp)) != 0)
			etest->flags |= ETH_TEST_FL_FAILED;

		if (!netif_running(bp->dev))
			bnx2_shutdown_chip(bp);
		else {
			bnx2_init_nic(bp, 1);
			bnx2_netif_start(bp, true);
		}

		/* wait for link up */
		for (i = 0; i < 7; i++) {
			if (bp->link_up)
				break;
			msleep_interruptible(1000);
		}
	}

	if (bnx2_test_nvram(bp) != 0) {
		buf[3] = 1;
		etest->flags |= ETH_TEST_FL_FAILED;
	}
	if (bnx2_test_intr(bp) != 0) {
		buf[4] = 1;
		etest->flags |= ETH_TEST_FL_FAILED;
	}

	if (bnx2_test_link(bp) != 0) {
		buf[5] = 1;
		etest->flags |= ETH_TEST_FL_FAILED;

	}
	if (!netif_running(bp->dev))
		bnx2_set_power_state(bp, PCI_D3hot);
}