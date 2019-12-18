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
typedef  size_t u64 ;
struct pcidev_info {scalar_t__ pdi_pcibus_info; struct pcidev_info* pdi_host_pcidev_info; } ;
struct pcibus_info {size_t pbi_dir_xbase; } ;
typedef  size_t dma_addr_t ;

/* Variables and functions */
 scalar_t__ IS_PCIX (struct pcibus_info*) ; 
 scalar_t__ IS_PIC_SOFT (struct pcibus_info*) ; 
 size_t PCI32_DIRECT_BASE ; 
 size_t PHYS_TO_DMA (size_t) ; 
 size_t PHYS_TO_TIODMA (size_t) ; 
 scalar_t__ SN_DMA_ADDRTYPE (int) ; 
 scalar_t__ SN_DMA_ADDR_PHYS ; 
 int SN_DMA_MSI ; 

__attribute__((used)) static dma_addr_t
pcibr_dmatrans_direct32(struct pcidev_info * info,
			u64 paddr, size_t req_size, u64 flags, int dma_flags)
{
	struct pcidev_info *pcidev_info = info->pdi_host_pcidev_info;
	struct pcibus_info *pcibus_info = (struct pcibus_info *)pcidev_info->
	    pdi_pcibus_info;
	u64 xio_addr;

	u64 xio_base;
	u64 offset;
	u64 endoff;

	if (IS_PCIX(pcibus_info)) {
		return 0;
	}

	if (dma_flags & SN_DMA_MSI)
		return 0;

	if (SN_DMA_ADDRTYPE(dma_flags) == SN_DMA_ADDR_PHYS)
		xio_addr = IS_PIC_SOFT(pcibus_info) ? PHYS_TO_DMA(paddr) :
	    					      PHYS_TO_TIODMA(paddr);
	else
		xio_addr = paddr;

	xio_base = pcibus_info->pbi_dir_xbase;
	offset = xio_addr - xio_base;
	endoff = req_size + offset;
	if ((req_size > (1ULL << 31)) ||	/* Too Big */
	    (xio_addr < xio_base) ||	/* Out of range for mappings */
	    (endoff > (1ULL << 31))) {	/* Too Big */
		return 0;
	}

	return PCI32_DIRECT_BASE | offset;
}