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
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 void* pci_alloc_consistent (struct pci_dev*,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *diva_pci_alloc_consistent(struct pci_dev *hwdev,
				       size_t size,
				       dma_addr_t * dma_handle,
				       void **addr_handle)
{
	void *addr = pci_alloc_consistent(hwdev, size, dma_handle);

	*addr_handle = addr;

	return (addr);
}