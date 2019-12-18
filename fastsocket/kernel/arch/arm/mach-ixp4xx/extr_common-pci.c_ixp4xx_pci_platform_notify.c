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
struct device {void* coherent_dma_mask; void** dma_mask; int /*<<< orphan*/ * bus; } ;

/* Variables and functions */
 void* SZ_64M ; 
 int /*<<< orphan*/  dmabounce_register_dev (struct device*,int,int) ; 
 int /*<<< orphan*/  pci_bus_type ; 

__attribute__((used)) static int ixp4xx_pci_platform_notify(struct device *dev)
{
	if(dev->bus == &pci_bus_type) {
		*dev->dma_mask =  SZ_64M - 1;
		dev->coherent_dma_mask = SZ_64M - 1;
		dmabounce_register_dev(dev, 2048, 4096);
	}
	return 0;
}