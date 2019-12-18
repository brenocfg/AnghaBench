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
typedef  int /*<<< orphan*/  u64 ;
struct device {int /*<<< orphan*/ * bus; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  pci_bus_type ; 
 int pci_set_dma_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_pci_dev (struct device*) ; 

int dma_set_mask(struct device *dev, u64 dma_mask)
{
#ifdef CONFIG_PCI
	if (dev->bus == &pci_bus_type)
		return pci_set_dma_mask(to_pci_dev(dev), dma_mask);
#endif
	return -EOPNOTSUPP;
}