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

/* Variables and functions */
 int /*<<< orphan*/  CVMX_CIU_MBOX_CLRX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQF_DISABLED ; 
 int /*<<< orphan*/  OCTEON_IRQ_MBOX0 ; 
 int /*<<< orphan*/  OCTEON_IRQ_MBOX1 ; 
 int /*<<< orphan*/  cvmx_get_core_num () ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mailbox_interrupt ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void octeon_prepare_cpus(unsigned int max_cpus)
{
	cvmx_write_csr(CVMX_CIU_MBOX_CLRX(cvmx_get_core_num()), 0xffffffff);
	if (request_irq(OCTEON_IRQ_MBOX0, mailbox_interrupt, IRQF_DISABLED,
			"mailbox0", mailbox_interrupt)) {
		panic("Cannot request_irq(OCTEON_IRQ_MBOX0)\n");
	}
	if (request_irq(OCTEON_IRQ_MBOX1, mailbox_interrupt, IRQF_DISABLED,
			"mailbox1", mailbox_interrupt)) {
		panic("Cannot request_irq(OCTEON_IRQ_MBOX1)\n");
	}
}