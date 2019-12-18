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
struct igb_q_vector {int /*<<< orphan*/  napi; } ;
struct TYPE_3__ {int /*<<< orphan*/  doosync; } ;
struct TYPE_4__ {int get_link_status; } ;
struct e1000_hw {TYPE_2__ mac; } ;
struct igb_adapter {int /*<<< orphan*/  ptp_tx_work; int /*<<< orphan*/  watchdog_timer; int /*<<< orphan*/  state; TYPE_1__ stats; int /*<<< orphan*/  reset_task; struct e1000_hw hw; struct igb_q_vector** q_vector; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_ICR ; 
 int E1000_ICR_DOUTSYNC ; 
 int E1000_ICR_DRSTA ; 
 int E1000_ICR_INT_ASSERTED ; 
 int E1000_ICR_LSC ; 
 int E1000_ICR_RXSEQ ; 
 int E1000_ICR_TS ; 
 int /*<<< orphan*/  E1000_TSICR ; 
 int E1000_TSICR_TXTS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  __IGB_DOWN ; 
 int /*<<< orphan*/  igb_write_itr (struct igb_q_vector*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t igb_intr(int irq, void *data)
{
	struct igb_adapter *adapter = data;
	struct igb_q_vector *q_vector = adapter->q_vector[0];
	struct e1000_hw *hw = &adapter->hw;
	/* Interrupt Auto-Mask...upon reading ICR, interrupts are masked.  No
	 * need for the IMC write
	 */
	u32 icr = rd32(E1000_ICR);

	/* IMS will not auto-mask if INT_ASSERTED is not set, and if it is
	 * not set, then the adapter didn't send an interrupt
	 */
	if (!(icr & E1000_ICR_INT_ASSERTED))
		return IRQ_NONE;

	igb_write_itr(q_vector);

	if (icr & E1000_ICR_DRSTA)
		schedule_work(&adapter->reset_task);

	if (icr & E1000_ICR_DOUTSYNC) {
		/* HW is reporting DMA is out of sync */
		adapter->stats.doosync++;
	}

	if (icr & (E1000_ICR_RXSEQ | E1000_ICR_LSC)) {
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

	napi_schedule(&q_vector->napi);

	return IRQ_HANDLED;
}