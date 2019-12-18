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
struct tioca_kernel {int ca_ap_pagesize; int ca_pcigart_entries; int /*<<< orphan*/  ca_lock; void** ca_pcigart; int /*<<< orphan*/  ca_dmamaps; scalar_t__ ca_pciap_base; void* ca_pcigart_pagemap; } ;
struct tioca_dmamap {int cad_gart_size; int cad_gart_entry; int /*<<< orphan*/  cad_list; scalar_t__ cad_dma_addr; } ;
struct tioca_common {scalar_t__ ca_kernel_private; } ;
struct pcidev_info {scalar_t__ pdi_pcibus_info; } ;
struct pci_dev {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 size_t PHYS_TO_TIODMA (unsigned long) ; 
 struct pcidev_info* SN_PCIDEV_INFO (struct pci_dev*) ; 
 int ffs (int) ; 
 int find_first_zero_bit (void*,int) ; 
 int find_next_bit (void*,int,int) ; 
 int find_next_zero_bit (void*,int,int) ; 
 int /*<<< orphan*/  kfree (struct tioca_dmamap*) ; 
 struct tioca_dmamap* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int,void*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 void* tioca_paddr_to_gart (size_t) ; 
 int /*<<< orphan*/  tioca_tlbflush (struct tioca_kernel*) ; 

__attribute__((used)) static dma_addr_t
tioca_dma_mapped(struct pci_dev *pdev, unsigned long paddr, size_t req_size)
{
	int i, ps, ps_shift, entry, entries, mapsize, last_entry;
	u64 xio_addr, end_xio_addr;
	struct tioca_common *tioca_common;
	struct tioca_kernel *tioca_kern;
	dma_addr_t bus_addr = 0;
	struct tioca_dmamap *ca_dmamap;
	void *map;
	unsigned long flags;
	struct pcidev_info *pcidev_info = SN_PCIDEV_INFO(pdev);

	tioca_common = (struct tioca_common *)pcidev_info->pdi_pcibus_info;
	tioca_kern = (struct tioca_kernel *)tioca_common->ca_kernel_private;

	xio_addr = PHYS_TO_TIODMA(paddr);
	if (!xio_addr)
		return 0;

	spin_lock_irqsave(&tioca_kern->ca_lock, flags);

	/*
	 * allocate a map struct
	 */

	ca_dmamap = kzalloc(sizeof(struct tioca_dmamap), GFP_ATOMIC);
	if (!ca_dmamap)
		goto map_return;

	/*
	 * Locate free entries that can hold req_size.  Account for
	 * unaligned start/length when allocating.
	 */

	ps = tioca_kern->ca_ap_pagesize;	/* will be power of 2 */
	ps_shift = ffs(ps) - 1;
	end_xio_addr = xio_addr + req_size - 1;

	entries = (end_xio_addr >> ps_shift) - (xio_addr >> ps_shift) + 1;

	map = tioca_kern->ca_pcigart_pagemap;
	mapsize = tioca_kern->ca_pcigart_entries;

	entry = find_first_zero_bit(map, mapsize);
	while (entry < mapsize) {
		last_entry = find_next_bit(map, mapsize, entry);

		if (last_entry - entry >= entries)
			break;

		entry = find_next_zero_bit(map, mapsize, last_entry);
	}

	if (entry > mapsize) {
		kfree(ca_dmamap);
		goto map_return;
	}

	for (i = 0; i < entries; i++)
		set_bit(entry + i, map);

	bus_addr = tioca_kern->ca_pciap_base + (entry * ps);

	ca_dmamap->cad_dma_addr = bus_addr;
	ca_dmamap->cad_gart_size = entries;
	ca_dmamap->cad_gart_entry = entry;
	list_add(&ca_dmamap->cad_list, &tioca_kern->ca_dmamaps);

	if (xio_addr % ps) {
		tioca_kern->ca_pcigart[entry] = tioca_paddr_to_gart(xio_addr);
		bus_addr += xio_addr & (ps - 1);
		xio_addr &= ~(ps - 1);
		xio_addr += ps;
		entry++;
	}

	while (xio_addr < end_xio_addr) {
		tioca_kern->ca_pcigart[entry] = tioca_paddr_to_gart(xio_addr);
		xio_addr += ps;
		entry++;
	}

	tioca_tlbflush(tioca_kern);

map_return:
	spin_unlock_irqrestore(&tioca_kern->ca_lock, flags);
	return bus_addr;
}