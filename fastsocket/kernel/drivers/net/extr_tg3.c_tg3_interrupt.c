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
struct tg3_napi {size_t rx_rcb_ptr; int /*<<< orphan*/  napi; int /*<<< orphan*/ * rx_rcb; struct tg3_hw_status* hw_status; struct tg3* tp; } ;
struct tg3_hw_status {int status; } ;
struct tg3 {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHIP_RESETTING ; 
 int /*<<< orphan*/  IRQ_RETVAL (unsigned int) ; 
 scalar_t__ MAILBOX_INTERRUPT_0 ; 
 int PCISTATE_INT_NOT_ACTIVE ; 
 int SD_STATUS_UPDATED ; 
 int /*<<< orphan*/  TG3PCI_PCISTATE ; 
 scalar_t__ TG3_64BIT_REG_LOW ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prefetch (int /*<<< orphan*/ *) ; 
 scalar_t__ tg3_flag (struct tg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg3_has_work (struct tg3_napi*) ; 
 scalar_t__ tg3_irq_sync (struct tg3*) ; 
 int tr32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw32_mailbox_f (scalar_t__,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t tg3_interrupt(int irq, void *dev_id)
{
	struct tg3_napi *tnapi = dev_id;
	struct tg3 *tp = tnapi->tp;
	struct tg3_hw_status *sblk = tnapi->hw_status;
	unsigned int handled = 1;

	/* In INTx mode, it is possible for the interrupt to arrive at
	 * the CPU before the status block posted prior to the interrupt.
	 * Reading the PCI State register will confirm whether the
	 * interrupt is ours and will flush the status block.
	 */
	if (unlikely(!(sblk->status & SD_STATUS_UPDATED))) {
		if (tg3_flag(tp, CHIP_RESETTING) ||
		    (tr32(TG3PCI_PCISTATE) & PCISTATE_INT_NOT_ACTIVE)) {
			handled = 0;
			goto out;
		}
	}

	/*
	 * Writing any value to intr-mbox-0 clears PCI INTA# and
	 * chip-internal interrupt pending events.
	 * Writing non-zero to intr-mbox-0 additional tells the
	 * NIC to stop sending us irqs, engaging "in-intr-handler"
	 * event coalescing.
	 *
	 * Flush the mailbox to de-assert the IRQ immediately to prevent
	 * spurious interrupts.  The flush impacts performance but
	 * excessive spurious interrupts can be worse in some cases.
	 */
	tw32_mailbox_f(MAILBOX_INTERRUPT_0 + TG3_64BIT_REG_LOW, 0x00000001);
	if (tg3_irq_sync(tp))
		goto out;
	sblk->status &= ~SD_STATUS_UPDATED;
	if (likely(tg3_has_work(tnapi))) {
		prefetch(&tnapi->rx_rcb[tnapi->rx_rcb_ptr]);
		napi_schedule(&tnapi->napi);
	} else {
		/* No work, shared interrupt perhaps?  re-enable
		 * interrupts, and flush that PCI write
		 */
		tw32_mailbox_f(MAILBOX_INTERRUPT_0 + TG3_64BIT_REG_LOW,
			       0x00000000);
	}
out:
	return IRQ_RETVAL(handled);
}