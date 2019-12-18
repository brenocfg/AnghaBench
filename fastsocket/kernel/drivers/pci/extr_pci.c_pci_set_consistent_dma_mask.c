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
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int dma_set_coherent_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fls64 (int /*<<< orphan*/ ) ; 

int
pci_set_consistent_dma_mask(struct pci_dev *dev, u64 mask)
{
	int ret = dma_set_coherent_mask(&dev->dev, mask);
	if (ret)
		return ret;

	dev_dbg(&dev->dev, "using %dbit consistent DMA mask\n", fls64(mask));
	return 0;
}