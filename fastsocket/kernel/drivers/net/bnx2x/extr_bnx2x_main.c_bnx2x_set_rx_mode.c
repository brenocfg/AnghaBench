#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int flags; } ;
struct bnx2x {scalar_t__ state; int /*<<< orphan*/  sp_rtnl_task; int /*<<< orphan*/  sp_rtnl_state; int /*<<< orphan*/  sp_state; int /*<<< orphan*/  rx_mode; TYPE_1__* dev; } ;
struct TYPE_2__ {scalar_t__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_FILTER_RX_MODE_PENDING ; 
 int /*<<< orphan*/  BNX2X_FILTER_RX_MODE_SCHED ; 
 scalar_t__ BNX2X_MAX_MULTICAST ; 
 int /*<<< orphan*/  BNX2X_RX_MODE_ALLMULTI ; 
 int /*<<< orphan*/  BNX2X_RX_MODE_NONE ; 
 int /*<<< orphan*/  BNX2X_RX_MODE_NORMAL ; 
 int /*<<< orphan*/  BNX2X_RX_MODE_PROMISC ; 
 int /*<<< orphan*/  BNX2X_SP_RTNL_VFPF_MCAST ; 
 int /*<<< orphan*/  BNX2X_SP_RTNL_VFPF_STORM_RX_MODE ; 
 scalar_t__ BNX2X_STATE_OPEN ; 
 scalar_t__ CHIP_IS_E1 (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 scalar_t__ IS_MF_ISCSI_SD (struct bnx2x*) ; 
 scalar_t__ IS_PF (struct bnx2x*) ; 
 int /*<<< orphan*/  NETIF_MSG_IFUP ; 
 scalar_t__ bnx2x_set_mc_list (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_set_storm_rx_mode (struct bnx2x*) ; 
 scalar_t__ bnx2x_set_uc_list (struct bnx2x*) ; 
 scalar_t__ netdev_mc_count (struct net_device*) ; 
 struct bnx2x* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_clear_bit () ; 
 int /*<<< orphan*/  smp_mb__before_clear_bit () ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void bnx2x_set_rx_mode(struct net_device *dev)
{
	struct bnx2x *bp = netdev_priv(dev);
	u32 rx_mode = BNX2X_RX_MODE_NORMAL;

	if (bp->state != BNX2X_STATE_OPEN) {
		DP(NETIF_MSG_IFUP, "state is %x, returning\n", bp->state);
		return;
	}

	DP(NETIF_MSG_IFUP, "dev->flags = %x\n", bp->dev->flags);

	if (dev->flags & IFF_PROMISC)
		rx_mode = BNX2X_RX_MODE_PROMISC;
	else if ((dev->flags & IFF_ALLMULTI) ||
		 ((netdev_mc_count(dev) > BNX2X_MAX_MULTICAST) &&
		  CHIP_IS_E1(bp)))
		rx_mode = BNX2X_RX_MODE_ALLMULTI;
	else {
		if (IS_PF(bp)) {
			/* some multicasts */
			if (bnx2x_set_mc_list(bp) < 0)
				rx_mode = BNX2X_RX_MODE_ALLMULTI;

			if (bnx2x_set_uc_list(bp) < 0)
				rx_mode = BNX2X_RX_MODE_PROMISC;
		} else {
			/* configuring mcast to a vf involves sleeping (when we
			 * wait for the pf's response). Since this function is
			 * called from non sleepable context we must schedule
			 * a work item for this purpose
			 */
			smp_mb__before_clear_bit();
			set_bit(BNX2X_SP_RTNL_VFPF_MCAST,
				&bp->sp_rtnl_state);
			smp_mb__after_clear_bit();
			schedule_delayed_work(&bp->sp_rtnl_task, 0);
		}
	}

	bp->rx_mode = rx_mode;
	/* handle ISCSI SD mode */
	if (IS_MF_ISCSI_SD(bp))
		bp->rx_mode = BNX2X_RX_MODE_NONE;

	/* Schedule the rx_mode command */
	if (test_bit(BNX2X_FILTER_RX_MODE_PENDING, &bp->sp_state)) {
		set_bit(BNX2X_FILTER_RX_MODE_SCHED, &bp->sp_state);
		return;
	}

	if (IS_PF(bp)) {
		bnx2x_set_storm_rx_mode(bp);
	} else {
		/* configuring rx mode to storms in a vf involves sleeping (when
		 * we wait for the pf's response). Since this function is
		 * called from non sleepable context we must schedule
		 * a work item for this purpose
		 */
		smp_mb__before_clear_bit();
		set_bit(BNX2X_SP_RTNL_VFPF_STORM_RX_MODE,
			&bp->sp_rtnl_state);
		smp_mb__after_clear_bit();
		schedule_delayed_work(&bp->sp_rtnl_task, 0);
	}
}