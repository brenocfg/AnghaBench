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
typedef  int u32 ;
struct ixgbevf_ring {int /*<<< orphan*/  rx_buf_len; } ;
struct ixgbe_hw {int dummy; } ;
struct ixgbevf_adapter {struct ixgbevf_ring* rx_ring; struct ixgbe_hw hw; } ;

/* Variables and functions */
 int ALIGN (int /*<<< orphan*/ ,int) ; 
 int IXGBE_SRRCTL_BSIZEPKT_SHIFT ; 
 int IXGBE_SRRCTL_DESCTYPE_ADV_ONEBUF ; 
 int IXGBE_SRRCTL_DROP_EN ; 
 int /*<<< orphan*/  IXGBE_VFSRRCTL (int) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ixgbevf_configure_srrctl(struct ixgbevf_adapter *adapter, int index)
{
	struct ixgbevf_ring *rx_ring;
	struct ixgbe_hw *hw = &adapter->hw;
	u32 srrctl;

	rx_ring = &adapter->rx_ring[index];

	srrctl = IXGBE_SRRCTL_DROP_EN;

	srrctl |= IXGBE_SRRCTL_DESCTYPE_ADV_ONEBUF;

	srrctl |= ALIGN(rx_ring->rx_buf_len, 1024) >>
		  IXGBE_SRRCTL_BSIZEPKT_SHIFT;

	IXGBE_WRITE_REG(hw, IXGBE_VFSRRCTL(index), srrctl);
}