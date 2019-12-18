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
struct device {int /*<<< orphan*/ * dma_mask; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  alpha_gendev_to_pci (struct device*) ; 
 int /*<<< orphan*/  pci_dma_supported (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
dma_set_mask(struct device *dev, u64 mask)
{
	if (!dev->dma_mask ||
	    !pci_dma_supported(alpha_gendev_to_pci(dev), mask))
		return -EIO;

	*dev->dma_mask = mask;

	return 0;
}