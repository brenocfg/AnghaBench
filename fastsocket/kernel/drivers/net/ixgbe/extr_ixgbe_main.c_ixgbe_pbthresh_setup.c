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
struct TYPE_2__ {scalar_t__ low_water; scalar_t__* high_water; } ;
struct ixgbe_hw {TYPE_1__ fc; } ;
struct ixgbe_adapter {int /*<<< orphan*/  netdev; struct ixgbe_hw hw; } ;

/* Variables and functions */
 scalar_t__ ixgbe_hpbthresh (struct ixgbe_adapter*,int) ; 
 scalar_t__ ixgbe_lpbthresh (struct ixgbe_adapter*) ; 
 int netdev_get_num_tc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ixgbe_pbthresh_setup(struct ixgbe_adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;
	int num_tc = netdev_get_num_tc(adapter->netdev);
	int i;

	if (!num_tc)
		num_tc = 1;

	hw->fc.low_water = ixgbe_lpbthresh(adapter);

	for (i = 0; i < num_tc; i++) {
		hw->fc.high_water[i] = ixgbe_hpbthresh(adapter, i);

		/* Low water marks must not be larger than high water marks */
		if (hw->fc.low_water > hw->fc.high_water[i])
			hw->fc.low_water = 0;
	}
}