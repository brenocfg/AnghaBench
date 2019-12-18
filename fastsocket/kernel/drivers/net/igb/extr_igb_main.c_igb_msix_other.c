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
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  doosync; } ;
struct TYPE_4__ {int get_link_status; } ;
struct e1000_hw {TYPE_2__ mac; } ;
struct igb_adapter {int eims_other; int /*<<< orphan*/  ptp_tx_work; int /*<<< orphan*/  watchdog_timer; int /*<<< orphan*/  state; TYPE_1__ stats; int /*<<< orphan*/  reset_task; struct e1000_hw hw; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_EIMS ; 
 int /*<<< orphan*/  E1000_ICR ; 
 int E1000_ICR_DOUTSYNC ; 
 int E1000_ICR_DRSTA ; 
 int E1000_ICR_LSC ; 
 int E1000_ICR_TS ; 
 int E1000_ICR_VMMB ; 
 int /*<<< orphan*/  E1000_TSICR ; 
 int E1000_TSICR_TXTS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  __IGB_DOWN ; 
 int /*<<< orphan*/  igb_check_wvbr (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_msg_task (struct igb_adapter*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t igb_msix_other(int irq, void *data)
{
	struct igb_adapter *adapter = data;
	struct e1000_hw *hw = &adapter->hw;
	u32 icr = rd32(E1000_ICR);
	/* reading ICR causes bit 31 of EICR to be cleared */

	if (icr & E1000_ICR_DRSTA)
		schedule_work(&adapter->reset_task);

	if (icr & E1000_ICR_DOUTSYNC) {
		/* HW is reporting DMA is out of sync */
		adapter->stats.doosync++;
		/* The DMA Out of Sync is also indication of a spoof event
		 * in IOV mode. Check the Wrong VM Behavior register to
		 * see if it is really a spoof event.
		 */
		igb_check_wvbr(adapter);
	}

	/* Check for a mailbox event */
	if (icr & E1000_ICR_VMMB)
		igb_msg_task(adapter);

	if (icr & E1000_ICR_LSC) {
		hw->mac.get_link_status = 1;
		/* guard against interrupt when we're going down */
		if (!test_bit(__IGB_DOWN, &adapter->state))
			mod_timer(&adapter->watchdog_timer, jiffies + 1);
	}

	if (icr & E1000_ICR_TS) {
		u32 tsicr = rd32(E1000_TSICR);

		if (tsicr & E1000_TSICR_TXTS) {
			/* acknowledge the interrupt */
			wr32(E1000_TSICR, E1000_TSICR_TXTS);
			/* retrieve hardware timestamp */
			schedule_work(&adapter->ptp_tx_work);
		}
	}

	wr32(E1000_EIMS, adapter->eims_other);

	return IRQ_HANDLED;
}