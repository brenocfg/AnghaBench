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
struct io_apic_irq_attr {int dummy; } ;
struct TYPE_4__ {scalar_t__ apicid; } ;
struct TYPE_3__ {int srcbus; scalar_t__ dstapic; int srcbusirq; int /*<<< orphan*/  dstirq; int /*<<< orphan*/  irqtype; } ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_DEBUG ; 
 int /*<<< orphan*/  APIC_VERBOSE ; 
 scalar_t__ IO_APIC_IRQ (int) ; 
 scalar_t__ MP_APIC_ALL ; 
 int /*<<< orphan*/  apic_printk (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  irq_polarity (int) ; 
 int /*<<< orphan*/  irq_trigger (int) ; 
 int /*<<< orphan*/  mp_bus_not_pci ; 
 TYPE_2__* mp_ioapics ; 
 int mp_irq_entries ; 
 TYPE_1__* mp_irqs ; 
 int nr_ioapics ; 
 int pin_2_irq (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_io_apic_irq_attr (struct io_apic_irq_attr*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

int IO_APIC_get_PCI_irq_vector(int bus, int slot, int pin,
				struct io_apic_irq_attr *irq_attr)
{
	int apic, i, best_guess = -1;

	apic_printk(APIC_DEBUG,
		    "querying PCI -> IRQ mapping bus:%d, slot:%d, pin:%d.\n",
		    bus, slot, pin);
	if (test_bit(bus, mp_bus_not_pci)) {
		apic_printk(APIC_VERBOSE,
			    "PCI BIOS passed nonexistent PCI bus %d!\n", bus);
		return -1;
	}
	for (i = 0; i < mp_irq_entries; i++) {
		int lbus = mp_irqs[i].srcbus;

		for (apic = 0; apic < nr_ioapics; apic++)
			if (mp_ioapics[apic].apicid == mp_irqs[i].dstapic ||
			    mp_irqs[i].dstapic == MP_APIC_ALL)
				break;

		if (!test_bit(lbus, mp_bus_not_pci) &&
		    !mp_irqs[i].irqtype &&
		    (bus == lbus) &&
		    (slot == ((mp_irqs[i].srcbusirq >> 2) & 0x1f))) {
			int irq = pin_2_irq(i, apic, mp_irqs[i].dstirq);

			if (!(apic || IO_APIC_IRQ(irq)))
				continue;

			if (pin == (mp_irqs[i].srcbusirq & 3)) {
				set_io_apic_irq_attr(irq_attr, apic,
						     mp_irqs[i].dstirq,
						     irq_trigger(i),
						     irq_polarity(i));
				return irq;
			}
			/*
			 * Use the first all-but-pin matching entry as a
			 * best-guess fuzzy result for broken mptables.
			 */
			if (best_guess < 0) {
				set_io_apic_irq_attr(irq_attr, apic,
						     mp_irqs[i].dstirq,
						     irq_trigger(i),
						     irq_polarity(i));
				best_guess = irq;
			}
		}
	}
	return best_guess;
}