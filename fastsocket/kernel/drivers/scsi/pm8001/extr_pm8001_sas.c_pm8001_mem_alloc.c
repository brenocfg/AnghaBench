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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct pci_dev {int dummy; } ;
typedef  int dma_addr_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 scalar_t__ lower_32_bits (int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ pci_alloc_consistent (struct pci_dev*,scalar_t__,int*) ; 
 int /*<<< orphan*/  pm8001_printk (char*) ; 
 scalar_t__ upper_32_bits (int) ; 

int pm8001_mem_alloc(struct pci_dev *pdev, void **virt_addr,
	dma_addr_t *pphys_addr, u32 *pphys_addr_hi,
	u32 *pphys_addr_lo, u32 mem_size, u32 align)
{
	caddr_t mem_virt_alloc;
	dma_addr_t mem_dma_handle;
	u64 phys_align;
	u64 align_offset = 0;
	if (align)
		align_offset = (dma_addr_t)align - 1;
	mem_virt_alloc =
		pci_alloc_consistent(pdev, mem_size + align, &mem_dma_handle);
	if (!mem_virt_alloc) {
		pm8001_printk("memory allocation error\n");
		return -1;
	}
	memset((void *)mem_virt_alloc, 0, mem_size+align);
	*pphys_addr = mem_dma_handle;
	phys_align = (*pphys_addr + align_offset) & ~align_offset;
	*virt_addr = (void *)mem_virt_alloc + phys_align - *pphys_addr;
	*pphys_addr_hi = upper_32_bits(phys_align);
	*pphys_addr_lo = lower_32_bits(phys_align);
	return 0;
}