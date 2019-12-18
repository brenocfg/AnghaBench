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
struct sk_buff {int dummy; } ;
struct igb_q_vector {struct igb_adapter* adapter; } ;
struct e1000_hw {int dummy; } ;
struct igb_adapter {struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_RXSTMPH ; 
 int /*<<< orphan*/  E1000_RXSTMPL ; 
 int /*<<< orphan*/  E1000_TSYNCRXCTL ; 
 int E1000_TSYNCRXCTL_VALID ; 
 int /*<<< orphan*/  igb_ptp_systim_to_hwtstamp (struct igb_adapter*,int /*<<< orphan*/ ,int) ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_hwtstamps (struct sk_buff*) ; 

void igb_ptp_rx_rgtstamp(struct igb_q_vector *q_vector,
			 struct sk_buff *skb)
{
	struct igb_adapter *adapter = q_vector->adapter;
	struct e1000_hw *hw = &adapter->hw;
	u64 regval;

	/* If this bit is set, then the RX registers contain the time stamp. No
	 * other packet will be time stamped until we read these registers, so
	 * read the registers to make them available again. Because only one
	 * packet can be time stamped at a time, we know that the register
	 * values must belong to this one here and therefore we don't need to
	 * compare any of the additional attributes stored for it.
	 *
	 * If nothing went wrong, then it should have a shared tx_flags that we
	 * can turn into a skb_shared_hwtstamps.
	 */
	if (!(rd32(E1000_TSYNCRXCTL) & E1000_TSYNCRXCTL_VALID))
		return;

	regval = rd32(E1000_RXSTMPL);
	regval |= (u64)rd32(E1000_RXSTMPH) << 32;

	igb_ptp_systim_to_hwtstamp(adapter, skb_hwtstamps(skb), regval);
}