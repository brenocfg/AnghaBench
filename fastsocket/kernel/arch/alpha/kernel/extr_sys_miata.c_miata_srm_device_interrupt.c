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
 int /*<<< orphan*/  handle_irq (int) ; 

__attribute__((used)) static void 
miata_srm_device_interrupt(unsigned long vector)
{
	int irq;

	irq = (vector - 0x800) >> 4;

	/*
	 * I really hate to do this, but the MIATA SRM console ignores the
	 *  low 8 bits in the interrupt summary register, and reports the
	 *  vector 0x80 *lower* than I expected from the bit numbering in
	 *  the documentation.
	 * This was done because the low 8 summary bits really aren't used
	 *  for reporting any interrupts (the PCI-ISA bridge, bit 7, isn't
	 *  used for this purpose, as PIC interrupts are delivered as the
	 *  vectors 0x800-0x8f0).
	 * But I really don't want to change the fixup code for allocation
	 *  of IRQs, nor the alpha_irq_mask maintenance stuff, both of which
	 *  look nice and clean now.
	 * So, here's this grotty hack... :-(
	 */
	if (irq >= 16)
		irq = irq + 8;

	handle_irq(irq);
}