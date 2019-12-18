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
struct skb_shared_hwtstamps {int dummy; } ;
struct e1000_hw {int dummy; } ;
struct igb_adapter {int /*<<< orphan*/ * ptp_tx_skb; struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_TXSTMPH ; 
 int /*<<< orphan*/  E1000_TXSTMPL ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  igb_ptp_systim_to_hwtstamp (struct igb_adapter*,struct skb_shared_hwtstamps*,int) ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_tstamp_tx (int /*<<< orphan*/ *,struct skb_shared_hwtstamps*) ; 

void igb_ptp_tx_hwtstamp(struct igb_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	struct skb_shared_hwtstamps shhwtstamps;
	u64 regval;

	regval = rd32(E1000_TXSTMPL);
	regval |= (u64)rd32(E1000_TXSTMPH) << 32;

	igb_ptp_systim_to_hwtstamp(adapter, &shhwtstamps, regval);
	skb_tstamp_tx(adapter->ptp_tx_skb, &shhwtstamps);
	dev_kfree_skb_any(adapter->ptp_tx_skb);
	adapter->ptp_tx_skb = NULL;
}