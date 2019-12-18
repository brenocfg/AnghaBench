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
struct pci_dev {int dummy; } ;
struct dma_loaf {int /*<<< orphan*/  dma_base; int /*<<< orphan*/ * cpu_base; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_free_consistent (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_dma_loaf(struct pci_dev *dev, struct dma_loaf *loaf_handle)
{
	if (loaf_handle->cpu_base != NULL)
		pci_free_consistent(dev, loaf_handle->length,
			loaf_handle->cpu_base, loaf_handle->dma_base);
}