#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct net_device {int dummy; } ;
struct TYPE_11__ {int InterruptStatus; } ;
struct TYPE_8__ {scalar_t__ UnfinishedReceives; } ;
struct TYPE_7__ {TYPE_6__* CurrSendHead; } ;
struct et131x_adapter {scalar_t__ FlowControl; int /*<<< orphan*/  task; TYPE_5__ Stats; TYPE_4__* regs; TYPE_2__ RxRing; TYPE_1__ TxRing; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_12__ {int PacketStaleCount; } ;
struct TYPE_9__ {int /*<<< orphan*/  watchdog_timer; int /*<<< orphan*/  int_status; } ;
struct TYPE_10__ {TYPE_3__ global; } ;
typedef  TYPE_6__* PMP_TCB ;

/* Variables and functions */
 scalar_t__ Both ; 
 int ET_INTR_RXDMA_XFR_DONE ; 
 int ET_INTR_TXDMA_ISR ; 
 int ET_INTR_WATCHDOG ; 
 int INT_MASK_ENABLE ; 
 int INT_MASK_ENABLE_NO_FLOW ; 
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 scalar_t__ TxOnly ; 
 int /*<<< orphan*/  et131x_disable_interrupts (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_enable_interrupts (struct et131x_adapter*) ; 
 struct et131x_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_present (struct net_device*) ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

irqreturn_t et131x_isr(int irq, void *dev_id)
{
	bool handled = true;
	struct net_device *netdev = (struct net_device *)dev_id;
	struct et131x_adapter *adapter = NULL;
	u32 status;

	if (!netif_device_present(netdev)) {
		handled = false;
		goto out;
	}

	adapter = netdev_priv(netdev);

	/* If the adapter is in low power state, then it should not
	 * recognize any interrupt
	 */

	/* Disable Device Interrupts */
	et131x_disable_interrupts(adapter);

	/* Get a copy of the value in the interrupt status register
	 * so we can process the interrupting section
	 */
	status = readl(&adapter->regs->global.int_status);

	if (adapter->FlowControl == TxOnly ||
	    adapter->FlowControl == Both) {
		status &= ~INT_MASK_ENABLE;
	} else {
		status &= ~INT_MASK_ENABLE_NO_FLOW;
	}

	/* Make sure this is our interrupt */
	if (!status) {
		handled = false;
		et131x_enable_interrupts(adapter);
		goto out;
	}

	/* This is our interrupt, so process accordingly */

	if (status & ET_INTR_WATCHDOG) {
		PMP_TCB pMpTcb = adapter->TxRing.CurrSendHead;

		if (pMpTcb)
			if (++pMpTcb->PacketStaleCount > 1)
				status |= ET_INTR_TXDMA_ISR;

		if (adapter->RxRing.UnfinishedReceives)
			status |= ET_INTR_RXDMA_XFR_DONE;
		else if (pMpTcb == NULL)
			writel(0, &adapter->regs->global.watchdog_timer);

		status &= ~ET_INTR_WATCHDOG;
	}

	if (status == 0) {
		/* This interrupt has in some way been "handled" by
		 * the ISR. Either it was a spurious Rx interrupt, or
		 * it was a Tx interrupt that has been filtered by
		 * the ISR.
		 */
		et131x_enable_interrupts(adapter);
		goto out;
	}

	/* We need to save the interrupt status value for use in our
	 * DPC. We will clear the software copy of that in that
	 * routine.
	 */
	adapter->Stats.InterruptStatus = status;

	/* Schedule the ISR handler as a bottom-half task in the
	 * kernel's tq_immediate queue, and mark the queue for
	 * execution
	 */
	schedule_work(&adapter->task);
out:
	return IRQ_RETVAL(handled);
}