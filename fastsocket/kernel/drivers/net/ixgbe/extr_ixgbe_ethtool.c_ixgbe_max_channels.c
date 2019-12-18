#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_3__ {scalar_t__ type; } ;
struct TYPE_4__ {TYPE_1__ mac; } ;
struct ixgbe_adapter {int flags; scalar_t__ atr_sample_rate; TYPE_2__ hw; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int IXGBE_FLAG_MSIX_ENABLED ; 
 int IXGBE_FLAG_SRIOV_ENABLED ; 
 unsigned int IXGBE_MAX_FDIR_INDICES ; 
 unsigned int IXGBE_MAX_RSS_INDICES ; 
 scalar_t__ ixgbe_mac_82598EB ; 
 int netdev_get_num_tc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int ixgbe_max_channels(struct ixgbe_adapter *adapter)
{
	unsigned int max_combined;
	u8 tcs = netdev_get_num_tc(adapter->netdev);

	if (!(adapter->flags & IXGBE_FLAG_MSIX_ENABLED)) {
		/* We only support one q_vector without MSI-X */
		max_combined = 1;
	} else if (adapter->flags & IXGBE_FLAG_SRIOV_ENABLED) {
		/* SR-IOV currently only allows one queue on the PF */
		max_combined = 1;
	} else if (tcs > 1) {
		/* For DCB report channels per traffic class */
		if (adapter->hw.mac.type == ixgbe_mac_82598EB) {
			/* 8 TC w/ 4 queues per TC */
			max_combined = 4;
		} else if (tcs > 4) {
			/* 8 TC w/ 8 queues per TC */
			max_combined = 8;
		} else {
			/* 4 TC w/ 16 queues per TC */
			max_combined = 16;
		}
	} else if (adapter->atr_sample_rate) {
		/* support up to 64 queues with ATR */
		max_combined = IXGBE_MAX_FDIR_INDICES;
	} else {
		/* support up to 16 queues with RSS */
		max_combined = IXGBE_MAX_RSS_INDICES;
	}

	return max_combined;
}