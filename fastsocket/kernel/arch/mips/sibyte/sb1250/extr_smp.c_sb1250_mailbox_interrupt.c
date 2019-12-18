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

/* Variables and functions */
 int K_INT_MBOX_0 ; 
 unsigned int SMP_CALL_FUNCTION ; 
 int ____raw_readq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ____raw_writeq (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_to_desc (int) ; 
 int /*<<< orphan*/  kstat_incr_irqs_this_cpu (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mailbox_clear_regs ; 
 int /*<<< orphan*/ * mailbox_regs ; 
 int /*<<< orphan*/  smp_call_function_interrupt () ; 
 int smp_processor_id () ; 

void sb1250_mailbox_interrupt(void)
{
	int cpu = smp_processor_id();
	int irq = K_INT_MBOX_0;
	unsigned int action;

	kstat_incr_irqs_this_cpu(irq, irq_to_desc(irq));
	/* Load the mailbox register to figure out what we're supposed to do */
	action = (____raw_readq(mailbox_regs[cpu]) >> 48) & 0xffff;

	/* Clear the mailbox to clear the interrupt */
	____raw_writeq(((u64)action) << 48, mailbox_clear_regs[cpu]);

	/*
	 * Nothing to do for SMP_RESCHEDULE_YOURSELF; returning from the
	 * interrupt will do the reschedule for us
	 */

	if (action & SMP_CALL_FUNCTION)
		smp_call_function_interrupt();
}