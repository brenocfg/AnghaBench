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
struct scatterlist {long dma_length; scalar_t__ dma_address; long length; } ;
struct pci_iommu_arena {scalar_t__ dma_base; unsigned long* ptes; } ;
struct device {int dummy; } ;
typedef  unsigned long dma_addr_t ;
struct TYPE_2__ {unsigned long pci_dac_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGA (char*,int,long,unsigned long,...) ; 
 unsigned long PAGE_MASK ; 
 long PAGE_SIZE ; 
 unsigned long SG_ENT_PHYS_ADDRESS (struct scatterlist*) ; 
 long SG_ENT_VIRT_ADDRESS (struct scatterlist*) ; 
 unsigned long __direct_map_base ; 
 unsigned long __direct_map_size ; 
 int __va (unsigned long) ; 
 TYPE_1__ alpha_mv ; 
 long iommu_arena_alloc (struct device*,struct pci_iommu_arena*,long,int /*<<< orphan*/ ) ; 
 long iommu_num_pages (unsigned long,long,long) ; 
 int /*<<< orphan*/  mk_iommu_pte (unsigned long) ; 
 int /*<<< orphan*/  sg_classify (struct device*,struct scatterlist*,struct scatterlist*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sg_fill(struct device *dev, struct scatterlist *leader, struct scatterlist *end,
	struct scatterlist *out, struct pci_iommu_arena *arena,
	dma_addr_t max_dma, int dac_allowed)
{
	unsigned long paddr = SG_ENT_PHYS_ADDRESS(leader);
	long size = leader->dma_length;
	struct scatterlist *sg;
	unsigned long *ptes;
	long npages, dma_ofs, i;

#if !DEBUG_NODIRECT
	/* If everything is physically contiguous, and the addresses
	   fall into the direct-map window, use it.  */
	if (leader->dma_address == 0
	    && paddr + size + __direct_map_base - 1 <= max_dma
	    && paddr + size <= __direct_map_size) {
		out->dma_address = paddr + __direct_map_base;
		out->dma_length = size;

		DBGA("    sg_fill: [%p,%lx] -> direct %llx\n",
		     __va(paddr), size, out->dma_address);

		return 0;
	}
#endif

	/* If physically contiguous and DAC is available, use it.  */
	if (leader->dma_address == 0 && dac_allowed) {
		out->dma_address = paddr + alpha_mv.pci_dac_offset;
		out->dma_length = size;

		DBGA("    sg_fill: [%p,%lx] -> DAC %llx\n",
		     __va(paddr), size, out->dma_address);

		return 0;
	}

	/* Otherwise, we'll use the iommu to make the pages virtually
	   contiguous.  */

	paddr &= ~PAGE_MASK;
	npages = iommu_num_pages(paddr, size, PAGE_SIZE);
	dma_ofs = iommu_arena_alloc(dev, arena, npages, 0);
	if (dma_ofs < 0) {
		/* If we attempted a direct map above but failed, die.  */
		if (leader->dma_address == 0)
			return -1;

		/* Otherwise, break up the remaining virtually contiguous
		   hunks into individual direct maps and retry.  */
		sg_classify(dev, leader, end, 0);
		return sg_fill(dev, leader, end, out, arena, max_dma, dac_allowed);
	}

	out->dma_address = arena->dma_base + dma_ofs*PAGE_SIZE + paddr;
	out->dma_length = size;

	DBGA("    sg_fill: [%p,%lx] -> sg %llx np %ld\n",
	     __va(paddr), size, out->dma_address, npages);

	/* All virtually contiguous.  We need to find the length of each
	   physically contiguous subsegment to fill in the ptes.  */
	ptes = &arena->ptes[dma_ofs];
	sg = leader;
	do {
#if DEBUG_ALLOC > 0
		struct scatterlist *last_sg = sg;
#endif

		size = sg->length;
		paddr = SG_ENT_PHYS_ADDRESS(sg);

		while (sg+1 < end && (int) sg[1].dma_address == -1) {
			size += sg[1].length;
			sg++;
		}

		npages = iommu_num_pages(paddr, size, PAGE_SIZE);

		paddr &= PAGE_MASK;
		for (i = 0; i < npages; ++i, paddr += PAGE_SIZE)
			*ptes++ = mk_iommu_pte(paddr);

#if DEBUG_ALLOC > 0
		DBGA("    (%ld) [%p,%x] np %ld\n",
		     last_sg - leader, SG_ENT_VIRT_ADDRESS(last_sg),
		     last_sg->length, npages);
		while (++last_sg <= sg) {
			DBGA("        (%ld) [%p,%x] cont\n",
			     last_sg - leader, SG_ENT_VIRT_ADDRESS(last_sg),
			     last_sg->length);
		}
#endif
	} while (++sg < end && (int) sg->dma_address < 0);

	return 1;
}