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
typedef  int u64 ;
struct unity_map_entry {int address_start; int address_end; int /*<<< orphan*/  prot; } ;
struct dma_ops_domain {int aperture_size; TYPE_1__** aperture; int /*<<< orphan*/  domain; } ;
struct TYPE_2__ {int /*<<< orphan*/  bitmap; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PM_MAP_4k ; 
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ ) ; 
 int iommu_map_page (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dma_ops_unity_map(struct dma_ops_domain *dma_dom,
			     struct unity_map_entry *e)
{
	u64 addr;
	int ret;

	for (addr = e->address_start; addr < e->address_end;
	     addr += PAGE_SIZE) {
		ret = iommu_map_page(&dma_dom->domain, addr, addr, e->prot,
				     PM_MAP_4k);
		if (ret)
			return ret;
		/*
		 * if unity mapping is in aperture range mark the page
		 * as allocated in the aperture
		 */
		if (addr < dma_dom->aperture_size)
			__set_bit(addr >> PAGE_SHIFT,
				  dma_dom->aperture[0]->bitmap);
	}

	return 0;
}