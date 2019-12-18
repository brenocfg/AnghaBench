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
struct notifier_block {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma_ops; } ;
struct device {TYPE_1__ archdata; } ;

/* Variables and functions */
 unsigned long BUS_NOTIFY_ADD_DEVICE ; 
 int /*<<< orphan*/  cell_dma_dev_setup (struct device*) ; 
 int /*<<< orphan*/  get_pci_dma_ops () ; 

__attribute__((used)) static int cell_of_bus_notify(struct notifier_block *nb, unsigned long action,
			      void *data)
{
	struct device *dev = data;

	/* We are only intereted in device addition */
	if (action != BUS_NOTIFY_ADD_DEVICE)
		return 0;

	/* We use the PCI DMA ops */
	dev->archdata.dma_ops = get_pci_dma_ops();

	cell_dma_dev_setup(dev);

	return 0;
}