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
struct pci_dev {scalar_t__ dma_mask; } ;
struct device {scalar_t__* dma_mask; int /*<<< orphan*/ * bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct pci_dev* isa_bridge ; 
 int /*<<< orphan*/  pci_bus_type ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

struct pci_dev *
alpha_gendev_to_pci(struct device *dev)
{
	if (dev && dev->bus == &pci_bus_type)
		return to_pci_dev(dev);

	/* Assume that non-PCI devices asking for DMA are either ISA or EISA,
	   BUG() otherwise. */
	BUG_ON(!isa_bridge);

	/* Assume non-busmaster ISA DMA when dma_mask is not set (the ISA
	   bridge is bus master then). */
	if (!dev || !dev->dma_mask || !*dev->dma_mask)
		return isa_bridge;

	/* For EISA bus masters, return isa_bridge (it might have smaller
	   dma_mask due to wiring limitations). */
	if (*dev->dma_mask >= isa_bridge->dma_mask)
		return isa_bridge;

	/* This assumes ISA bus master with dma_mask 0xffffff. */
	return NULL;
}