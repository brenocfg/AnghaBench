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
struct irq_handler_data {unsigned long imap; unsigned long iclr; } ;

/* Variables and functions */
 unsigned long ICLR_IDLE ; 
 unsigned long IMAP_AID_SAFARI ; 
 unsigned long IMAP_NID_SAFARI ; 
 unsigned long IMAP_TID_JBUS ; 
 unsigned long IMAP_TID_UPA ; 
 unsigned int IMAP_VALID ; 
 struct irq_handler_data* get_irq_chip_data (unsigned int) ; 
 unsigned long irq_choose_cpu (unsigned int) ; 
 scalar_t__ likely (struct irq_handler_data*) ; 
 unsigned int sun4u_compute_tid (unsigned long,unsigned long) ; 
 unsigned long upa_readq (unsigned long) ; 
 int /*<<< orphan*/  upa_writeq (unsigned long,unsigned long) ; 

__attribute__((used)) static void sun4u_irq_enable(unsigned int virt_irq)
{
	struct irq_handler_data *data = get_irq_chip_data(virt_irq);

	if (likely(data)) {
		unsigned long cpuid, imap, val;
		unsigned int tid;

		cpuid = irq_choose_cpu(virt_irq);
		imap = data->imap;

		tid = sun4u_compute_tid(imap, cpuid);

		val = upa_readq(imap);
		val &= ~(IMAP_TID_UPA | IMAP_TID_JBUS |
			 IMAP_AID_SAFARI | IMAP_NID_SAFARI);
		val |= tid | IMAP_VALID;
		upa_writeq(val, imap);
		upa_writeq(ICLR_IDLE, data->iclr);
	}
}