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
typedef  int u16 ;
struct e1000_hw {scalar_t__ mac_type; } ;
struct e1000_adapter {int itr; scalar_t__ link_speed; scalar_t__ tx_itr; int itr_setting; scalar_t__ rx_itr; int /*<<< orphan*/  total_rx_bytes; int /*<<< orphan*/  total_rx_packets; int /*<<< orphan*/  total_tx_bytes; int /*<<< orphan*/  total_tx_packets; struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ITR ; 
 scalar_t__ SPEED_1000 ; 
#define  bulk_latency 130 
 scalar_t__ e1000_82540 ; 
 void* e1000_update_itr (struct e1000_adapter*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
#define  low_latency 129 
#define  lowest_latency 128 
 int max (int,int) ; 
 int min (int,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void e1000_set_itr(struct e1000_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	u16 current_itr;
	u32 new_itr = adapter->itr;

	if (unlikely(hw->mac_type < e1000_82540))
		return;

	/* for non-gigabit speeds, just fix the interrupt rate at 4000 */
	if (unlikely(adapter->link_speed != SPEED_1000)) {
		current_itr = 0;
		new_itr = 4000;
		goto set_itr_now;
	}

	adapter->tx_itr = e1000_update_itr(adapter,
	                            adapter->tx_itr,
	                            adapter->total_tx_packets,
	                            adapter->total_tx_bytes);
	/* conservative mode (itr 3) eliminates the lowest_latency setting */
	if (adapter->itr_setting == 3 && adapter->tx_itr == lowest_latency)
		adapter->tx_itr = low_latency;

	adapter->rx_itr = e1000_update_itr(adapter,
	                            adapter->rx_itr,
	                            adapter->total_rx_packets,
	                            adapter->total_rx_bytes);
	/* conservative mode (itr 3) eliminates the lowest_latency setting */
	if (adapter->itr_setting == 3 && adapter->rx_itr == lowest_latency)
		adapter->rx_itr = low_latency;

	current_itr = max(adapter->rx_itr, adapter->tx_itr);

	switch (current_itr) {
	/* counts and packets in update_itr are dependent on these numbers */
	case lowest_latency:
		new_itr = 70000;
		break;
	case low_latency:
		new_itr = 20000; /* aka hwitr = ~200 */
		break;
	case bulk_latency:
		new_itr = 4000;
		break;
	default:
		break;
	}

set_itr_now:
	if (new_itr != adapter->itr) {
		/* this attempts to bias the interrupt rate towards Bulk
		 * by adding intermediate steps when interrupt rate is
		 * increasing */
		new_itr = new_itr > adapter->itr ?
		             min(adapter->itr + (new_itr >> 2), new_itr) :
		             new_itr;
		adapter->itr = new_itr;
		ew32(ITR, 1000000000 / (new_itr * 256));
	}
}