#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  scalar_t__ u32 ;
struct ixgbe_ring {size_t dcb_tc; int /*<<< orphan*/  state; } ;
struct ixgbe_hw_stats {int /*<<< orphan*/ * pxoffrxc; } ;
struct TYPE_6__ {int type; } ;
struct ixgbe_hw {TYPE_3__ mac; } ;
struct TYPE_4__ {int pfc_mode_enable; } ;
struct ixgbe_adapter {int flags; int num_tx_queues; struct ixgbe_ring** tx_ring; int /*<<< orphan*/  netdev; TYPE_2__* ixgbe_ieee_pfc; TYPE_1__ dcb_cfg; struct ixgbe_hw_stats stats; struct ixgbe_hw hw; } ;
struct TYPE_5__ {int /*<<< orphan*/  pfc_en; } ;

/* Variables and functions */
 int IXGBE_FLAG_DCB_ENABLED ; 
 int /*<<< orphan*/  IXGBE_PXOFFRXC (int) ; 
 int /*<<< orphan*/  IXGBE_PXOFFRXCNT (int) ; 
 scalar_t__ IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int MAX_TX_PACKET_BUFFERS ; 
 int /*<<< orphan*/  __IXGBE_HANG_CHECK_ARMED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
#define  ixgbe_mac_82598EB 128 
 int /*<<< orphan*/  ixgbe_update_xoff_rx_lfc (struct ixgbe_adapter*) ; 
 size_t netdev_get_prio_tc_map (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ixgbe_update_xoff_received(struct ixgbe_adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;
	struct ixgbe_hw_stats *hwstats = &adapter->stats;
	u32 xoff[8] = {0};
	u8 tc;
	int i;
	bool pfc_en = adapter->dcb_cfg.pfc_mode_enable;

	if (adapter->ixgbe_ieee_pfc)
		pfc_en |= !!(adapter->ixgbe_ieee_pfc->pfc_en);

	if (!(adapter->flags & IXGBE_FLAG_DCB_ENABLED) || !pfc_en) {
		ixgbe_update_xoff_rx_lfc(adapter);
		return;
	}

	/* update stats for each tc, only valid with PFC enabled */
	for (i = 0; i < MAX_TX_PACKET_BUFFERS; i++) {
		u32 pxoffrxc;

		switch (hw->mac.type) {
		case ixgbe_mac_82598EB:
			pxoffrxc = IXGBE_READ_REG(hw, IXGBE_PXOFFRXC(i));
			break;
		default:
			pxoffrxc = IXGBE_READ_REG(hw, IXGBE_PXOFFRXCNT(i));
		}
		hwstats->pxoffrxc[i] += pxoffrxc;
		/* Get the TC for given UP */
		tc = netdev_get_prio_tc_map(adapter->netdev, i);
		xoff[tc] += pxoffrxc;
	}

	/* disarm tx queues that have received xoff frames */
	for (i = 0; i < adapter->num_tx_queues; i++) {
		struct ixgbe_ring *tx_ring = adapter->tx_ring[i];

		tc = tx_ring->dcb_tc;
		if (xoff[tc])
			clear_bit(__IXGBE_HANG_CHECK_ARMED, &tx_ring->state);
	}
}