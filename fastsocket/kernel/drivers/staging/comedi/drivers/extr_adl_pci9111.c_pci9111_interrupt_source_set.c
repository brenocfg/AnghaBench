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
struct comedi_device {int dummy; } ;
typedef  enum pci9111_ISC1_sources { ____Placeholder_pci9111_ISC1_sources } pci9111_ISC1_sources ;
typedef  enum pci9111_ISC0_sources { ____Placeholder_pci9111_ISC0_sources } pci9111_ISC0_sources ;

/* Variables and functions */
 int PCI9111_ISC0_SET_IRQ_ON_FIFO_HALF_FULL ; 
 int PCI9111_ISC1_SET_IRQ_ON_EXT_TRG ; 
 int irq_on_external_trigger ; 
 int irq_on_fifo_half_full ; 
 int pci9111_interrupt_and_fifo_get () ; 
 int /*<<< orphan*/  pci9111_interrupt_and_fifo_set (int) ; 

__attribute__((used)) static void pci9111_interrupt_source_set(struct comedi_device *dev,
					 enum pci9111_ISC0_sources irq_0_source,
					 enum pci9111_ISC1_sources irq_1_source)
{
	int flags;

	flags = pci9111_interrupt_and_fifo_get() & 0x04;

	if (irq_0_source == irq_on_fifo_half_full)
		flags |= PCI9111_ISC0_SET_IRQ_ON_FIFO_HALF_FULL;

	if (irq_1_source == irq_on_external_trigger)
		flags |= PCI9111_ISC1_SET_IRQ_ON_EXT_TRG;

	pci9111_interrupt_and_fifo_set(flags);
}