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
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct e1000_hw {int dummy; } ;
struct e1000_adapter {int flags; int /*<<< orphan*/  flags2; struct e1000_hw hw; } ;

/* Variables and functions */
 int E1000_RXDEXT_STATERR_TST ; 
 int E1000_TSYNCRXCTL_VALID ; 
 int /*<<< orphan*/  FLAG2_CHECK_RX_HWTSTAMP ; 
 int FLAG_HAS_HW_TIMESTAMP ; 
 int /*<<< orphan*/  RXSTMPH ; 
 int /*<<< orphan*/  RXSTMPL ; 
 int /*<<< orphan*/  TSYNCRXCTL ; 
 int /*<<< orphan*/  e1000e_systim_to_hwtstamp (struct e1000_adapter*,int /*<<< orphan*/ ,int) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_hwtstamps (struct sk_buff*) ; 

__attribute__((used)) static void e1000e_rx_hwtstamp(struct e1000_adapter *adapter, u32 status,
			       struct sk_buff *skb)
{
	struct e1000_hw *hw = &adapter->hw;
	u64 rxstmp;

	if (!(adapter->flags & FLAG_HAS_HW_TIMESTAMP) ||
	    !(status & E1000_RXDEXT_STATERR_TST) ||
	    !(er32(TSYNCRXCTL) & E1000_TSYNCRXCTL_VALID))
		return;

	/* The Rx time stamp registers contain the time stamp.  No other
	 * received packet will be time stamped until the Rx time stamp
	 * registers are read.  Because only one packet can be time stamped
	 * at a time, the register values must belong to this packet and
	 * therefore none of the other additional attributes need to be
	 * compared.
	 */
	rxstmp = (u64)er32(RXSTMPL);
	rxstmp |= (u64)er32(RXSTMPH) << 32;
	e1000e_systim_to_hwtstamp(adapter, skb_hwtstamps(skb), rxstmp);

	adapter->flags2 &= ~FLAG2_CHECK_RX_HWTSTAMP;
}