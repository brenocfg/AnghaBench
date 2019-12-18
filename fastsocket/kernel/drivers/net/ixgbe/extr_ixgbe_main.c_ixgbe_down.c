#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct net_device {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* disable_tx_laser ) (struct ixgbe_hw*) ;} ;
struct TYPE_8__ {int type; TYPE_3__ ops; } ;
struct ixgbe_hw {TYPE_4__ mac; } ;
struct ixgbe_adapter {int num_rx_queues; int flags2; int num_vfs; int num_tx_queues; int /*<<< orphan*/  pdev; TYPE_2__** tx_ring; TYPE_1__* vfinfo; struct ixgbe_hw hw; int /*<<< orphan*/  service_timer; int /*<<< orphan*/  flags; int /*<<< orphan*/ * rx_ring; int /*<<< orphan*/  state; struct net_device* netdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  reg_idx; } ;
struct TYPE_5__ {int clear_to_send; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_DMATXCTL ; 
 int IXGBE_DMATXCTL_TE ; 
 int /*<<< orphan*/  IXGBE_EITRSEL ; 
 int IXGBE_FLAG2_FDIR_REQUIRES_REINIT ; 
 int IXGBE_FLAG2_RESET_REQUESTED ; 
 int /*<<< orphan*/  IXGBE_FLAG_NEED_LINK_UPDATE ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_RXCTRL ; 
 int IXGBE_RXCTRL_RXEN ; 
 int /*<<< orphan*/  IXGBE_TXDCTL (int /*<<< orphan*/ ) ; 
 int IXGBE_TXDCTL_SWFLSH ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __IXGBE_DOWN ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixgbe_clean_all_rx_rings (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_clean_all_tx_rings (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_disable_rx_queue (struct ixgbe_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_disable_tx_rx (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_irq_disable (struct ixgbe_adapter*) ; 
#define  ixgbe_mac_82599EB 129 
#define  ixgbe_mac_X540 128 
 int /*<<< orphan*/  ixgbe_napi_disable_all (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_ping_all_vfs (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_reset (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_setup_dca (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_disable (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  pci_channel_offline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

void ixgbe_down(struct ixgbe_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	struct ixgbe_hw *hw = &adapter->hw;
	u32 rxctrl;
	int i;

	/* signal that we are down to the interrupt handler */
	set_bit(__IXGBE_DOWN, &adapter->state);

	/* disable receives */
	rxctrl = IXGBE_READ_REG(hw, IXGBE_RXCTRL);
	IXGBE_WRITE_REG(hw, IXGBE_RXCTRL, rxctrl & ~IXGBE_RXCTRL_RXEN);

	/* disable all enabled rx queues */
	for (i = 0; i < adapter->num_rx_queues; i++)
		/* this call also flushes the previous write */
		ixgbe_disable_rx_queue(adapter, adapter->rx_ring[i]);

	usleep_range(10000, 20000);

	netif_tx_stop_all_queues(netdev);

	/* call carrier off first to avoid false dev_watchdog timeouts */
	netif_carrier_off(netdev);
	netif_tx_disable(netdev);

	ixgbe_irq_disable(adapter);

	ixgbe_napi_disable_all(adapter);

	adapter->flags2 &= ~(IXGBE_FLAG2_FDIR_REQUIRES_REINIT |
			     IXGBE_FLAG2_RESET_REQUESTED);
	adapter->flags &= ~IXGBE_FLAG_NEED_LINK_UPDATE;

	del_timer_sync(&adapter->service_timer);

	if (adapter->num_vfs) {
		/* Clear EITR Select mapping */
		IXGBE_WRITE_REG(&adapter->hw, IXGBE_EITRSEL, 0);

		/* Mark all the VFs as inactive */
		for (i = 0 ; i < adapter->num_vfs; i++)
			adapter->vfinfo[i].clear_to_send = false;

		/* ping all the active vfs to let them know we are going down */
		ixgbe_ping_all_vfs(adapter);

		/* Disable all VFTE/VFRE TX/RX */
		ixgbe_disable_tx_rx(adapter);
	}

	/* disable transmits in the hardware now that interrupts are off */
	for (i = 0; i < adapter->num_tx_queues; i++) {
		u8 reg_idx = adapter->tx_ring[i]->reg_idx;
		IXGBE_WRITE_REG(hw, IXGBE_TXDCTL(reg_idx), IXGBE_TXDCTL_SWFLSH);
	}

	/* Disable the Tx DMA engine on 82599 and X540 */
	switch (hw->mac.type) {
	case ixgbe_mac_82599EB:
	case ixgbe_mac_X540:
		IXGBE_WRITE_REG(hw, IXGBE_DMATXCTL,
				(IXGBE_READ_REG(hw, IXGBE_DMATXCTL) &
				 ~IXGBE_DMATXCTL_TE));
		break;
	default:
		break;
	}

	if (!pci_channel_offline(adapter->pdev))
		ixgbe_reset(adapter);

	/* power down the optics for 82599 SFP+ fiber */
	if (hw->mac.ops.disable_tx_laser)
		hw->mac.ops.disable_tx_laser(hw);

	ixgbe_clean_all_tx_rings(adapter);
	ixgbe_clean_all_rx_rings(adapter);

#ifdef CONFIG_IXGBE_DCA
	/* since we reset the hardware DCA settings were cleared */
	ixgbe_setup_dca(adapter);
#endif
}