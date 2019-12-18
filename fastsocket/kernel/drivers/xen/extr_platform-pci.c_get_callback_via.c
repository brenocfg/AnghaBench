#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int u8 ;
struct pci_dev {int irq; int pin; int devfn; TYPE_1__* bus; } ;
struct TYPE_2__ {scalar_t__ number; } ;

/* Variables and functions */
 scalar_t__ pci_domain_nr (TYPE_1__*) ; 

__attribute__((used)) static uint64_t get_callback_via(struct pci_dev *pdev)
{
	u8 pin;
	int irq;

	irq = pdev->irq;
	if (irq < 16)
		return irq; /* ISA IRQ */

	pin = pdev->pin;

	/* We don't know the GSI. Specify the PCI INTx line instead. */
	return ((uint64_t)0x01 << 56) | /* PCI INTx identifier */
		((uint64_t)pci_domain_nr(pdev->bus) << 32) |
		((uint64_t)pdev->bus->number << 16) |
		((uint64_t)(pdev->devfn & 0xff) << 8) |
		((uint64_t)(pin - 1) & 3);
}