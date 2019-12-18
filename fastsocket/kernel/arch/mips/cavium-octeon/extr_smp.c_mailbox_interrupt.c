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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_CIU_MBOX_CLRX (int const) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int SMP_CALL_FUNCTION ; 
 int SMP_ICACHE_FLUSH ; 
 int cvmx_get_core_num () ; 
 int cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smp_call_function_interrupt () ; 

__attribute__((used)) static irqreturn_t mailbox_interrupt(int irq, void *dev_id)
{
	const int coreid = cvmx_get_core_num();
	uint64_t action;

	/* Load the mailbox register to figure out what we're supposed to do */
	action = cvmx_read_csr(CVMX_CIU_MBOX_CLRX(coreid));

	/* Clear the mailbox to clear the interrupt */
	cvmx_write_csr(CVMX_CIU_MBOX_CLRX(coreid), action);

	if (action & SMP_CALL_FUNCTION)
		smp_call_function_interrupt();

	/* Check if we've been told to flush the icache */
	if (action & SMP_ICACHE_FLUSH)
		asm volatile ("synci 0($0)\n");
	return IRQ_HANDLED;
}