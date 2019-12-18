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
struct irq_desc {int dummy; } ;

/* Variables and functions */
 scalar_t__ IRQ_SIC_START ; 
 scalar_t__ SIC_IRQ_STATUS ; 
 scalar_t__ VA_SIC_BASE ; 
 int /*<<< orphan*/  do_bad_IRQ (unsigned int,struct irq_desc*) ; 
 unsigned int ffs (unsigned long) ; 
 int /*<<< orphan*/  generic_handle_irq (unsigned int) ; 
 unsigned long readl (scalar_t__) ; 

__attribute__((used)) static void
sic_handle_irq(unsigned int irq, struct irq_desc *desc)
{
	unsigned long status = readl(VA_SIC_BASE + SIC_IRQ_STATUS);

	if (status == 0) {
		do_bad_IRQ(irq, desc);
		return;
	}

	do {
		irq = ffs(status) - 1;
		status &= ~(1 << irq);

		irq += IRQ_SIC_START;

		generic_handle_irq(irq);
	} while (status);
}