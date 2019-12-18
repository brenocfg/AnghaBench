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
typedef  int u32 ;
struct net_device {int mtu; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* set_rar ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {scalar_t__ type; int get_link_status; int /*<<< orphan*/  perm_addr; TYPE_3__ ops; int /*<<< orphan*/  addr; } ;
struct ixgbe_hw {TYPE_4__ mac; } ;
struct ixgbevf_adapter {int num_rx_queues; int num_tx_queues; int /*<<< orphan*/  watchdog_timer; int /*<<< orphan*/  state; int /*<<< orphan*/  mbx_lock; TYPE_2__* rx_ring; TYPE_1__* tx_ring; struct ixgbe_hw hw; struct net_device* netdev; } ;
struct TYPE_6__ {int reg_idx; } ;
struct TYPE_5__ {int reg_idx; } ;

/* Variables and functions */
 int ETH_FCS_LEN ; 
 int ETH_HLEN ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int IXGBE_RXDCTL_ENABLE ; 
 int IXGBE_RXDCTL_RLPMLMASK ; 
 int IXGBE_RXDCTL_RLPML_EN ; 
 int IXGBE_TXDCTL_ENABLE ; 
 int /*<<< orphan*/  IXGBE_VFRXDCTL (int) ; 
 int /*<<< orphan*/  IXGBE_VFTXDCTL (int) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __IXGBEVF_DOWN ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ ixgbe_mac_X540_vf ; 
 int /*<<< orphan*/  ixgbevf_configure_msix (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_init_last_counter_stats (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_napi_enable_all (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_rx_desc_queue_enable (struct ixgbevf_adapter*,int) ; 
 int /*<<< orphan*/  ixgbevf_save_reset_stats (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_start_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ixgbevf_up_complete(struct ixgbevf_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	struct ixgbe_hw *hw = &adapter->hw;
	int i, j = 0;
	int num_rx_rings = adapter->num_rx_queues;
	u32 txdctl, rxdctl;

	for (i = 0; i < adapter->num_tx_queues; i++) {
		j = adapter->tx_ring[i].reg_idx;
		txdctl = IXGBE_READ_REG(hw, IXGBE_VFTXDCTL(j));
		/* enable WTHRESH=8 descriptors, to encourage burst writeback */
		txdctl |= (8 << 16);
		IXGBE_WRITE_REG(hw, IXGBE_VFTXDCTL(j), txdctl);
	}

	for (i = 0; i < adapter->num_tx_queues; i++) {
		j = adapter->tx_ring[i].reg_idx;
		txdctl = IXGBE_READ_REG(hw, IXGBE_VFTXDCTL(j));
		txdctl |= IXGBE_TXDCTL_ENABLE;
		IXGBE_WRITE_REG(hw, IXGBE_VFTXDCTL(j), txdctl);
	}

	for (i = 0; i < num_rx_rings; i++) {
		j = adapter->rx_ring[i].reg_idx;
		rxdctl = IXGBE_READ_REG(hw, IXGBE_VFRXDCTL(j));
		rxdctl |= IXGBE_RXDCTL_ENABLE;
		if (hw->mac.type == ixgbe_mac_X540_vf) {
			rxdctl &= ~IXGBE_RXDCTL_RLPMLMASK;
			rxdctl |= ((netdev->mtu + ETH_HLEN + ETH_FCS_LEN) |
				   IXGBE_RXDCTL_RLPML_EN);
		}
		IXGBE_WRITE_REG(hw, IXGBE_VFRXDCTL(j), rxdctl);
		ixgbevf_rx_desc_queue_enable(adapter, i);
	}

	ixgbevf_configure_msix(adapter);

	spin_lock_bh(&adapter->mbx_lock);

	if (is_valid_ether_addr(hw->mac.addr))
		hw->mac.ops.set_rar(hw, 0, hw->mac.addr, 0);
	else
		hw->mac.ops.set_rar(hw, 0, hw->mac.perm_addr, 0);

	spin_unlock_bh(&adapter->mbx_lock);

	clear_bit(__IXGBEVF_DOWN, &adapter->state);
	ixgbevf_napi_enable_all(adapter);

	/* enable transmits */
	netif_tx_start_all_queues(netdev);

	ixgbevf_save_reset_stats(adapter);
	ixgbevf_init_last_counter_stats(adapter);

	hw->mac.get_link_status = 1;
	mod_timer(&adapter->watchdog_timer, jiffies);
}