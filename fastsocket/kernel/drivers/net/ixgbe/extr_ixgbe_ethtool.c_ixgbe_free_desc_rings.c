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
struct ixgbe_ring {int /*<<< orphan*/  reg_idx; } ;
struct TYPE_2__ {int type; } ;
struct ixgbe_hw {TYPE_1__ mac; } ;
struct ixgbe_adapter {struct ixgbe_ring test_rx_ring; struct ixgbe_ring test_tx_ring; struct ixgbe_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_DMATXCTL ; 
 int /*<<< orphan*/  IXGBE_DMATXCTL_TE ; 
 int /*<<< orphan*/  IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_RXCTRL ; 
 int /*<<< orphan*/  IXGBE_RXCTRL_RXEN ; 
 int /*<<< orphan*/  IXGBE_TXDCTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_TXDCTL_ENABLE ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_disable_rx_queue (struct ixgbe_adapter*,struct ixgbe_ring*) ; 
 int /*<<< orphan*/  ixgbe_free_rx_resources (struct ixgbe_ring*) ; 
 int /*<<< orphan*/  ixgbe_free_tx_resources (struct ixgbe_ring*) ; 
#define  ixgbe_mac_82599EB 129 
#define  ixgbe_mac_X540 128 
 int /*<<< orphan*/  ixgbe_reset (struct ixgbe_adapter*) ; 

__attribute__((used)) static void ixgbe_free_desc_rings(struct ixgbe_adapter *adapter)
{
	struct ixgbe_ring *tx_ring = &adapter->test_tx_ring;
	struct ixgbe_ring *rx_ring = &adapter->test_rx_ring;
	struct ixgbe_hw *hw = &adapter->hw;
	u32 reg_ctl;

	/* shut down the DMA engines now so they can be reinitialized later */

	/* first Rx */
	reg_ctl = IXGBE_READ_REG(hw, IXGBE_RXCTRL);
	reg_ctl &= ~IXGBE_RXCTRL_RXEN;
	IXGBE_WRITE_REG(hw, IXGBE_RXCTRL, reg_ctl);
	ixgbe_disable_rx_queue(adapter, rx_ring);

	/* now Tx */
	reg_ctl = IXGBE_READ_REG(hw, IXGBE_TXDCTL(tx_ring->reg_idx));
	reg_ctl &= ~IXGBE_TXDCTL_ENABLE;
	IXGBE_WRITE_REG(hw, IXGBE_TXDCTL(tx_ring->reg_idx), reg_ctl);

	switch (hw->mac.type) {
	case ixgbe_mac_82599EB:
	case ixgbe_mac_X540:
		reg_ctl = IXGBE_READ_REG(hw, IXGBE_DMATXCTL);
		reg_ctl &= ~IXGBE_DMATXCTL_TE;
		IXGBE_WRITE_REG(hw, IXGBE_DMATXCTL, reg_ctl);
		break;
	default:
		break;
	}

	ixgbe_reset(adapter);

	ixgbe_free_tx_resources(&adapter->test_tx_ring);
	ixgbe_free_rx_resources(&adapter->test_rx_ring);
}