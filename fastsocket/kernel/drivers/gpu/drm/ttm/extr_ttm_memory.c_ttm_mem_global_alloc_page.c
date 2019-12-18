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
struct ttm_mem_zone {int dummy; } ;
struct ttm_mem_global {struct ttm_mem_zone* zone_kernel; scalar_t__ zone_dma32; struct ttm_mem_zone* zone_highmem; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ PageHighMem (struct page*) ; 
 int page_to_pfn (struct page*) ; 
 int ttm_mem_global_alloc_zone (struct ttm_mem_global*,struct ttm_mem_zone*,int /*<<< orphan*/ ,int,int) ; 

int ttm_mem_global_alloc_page(struct ttm_mem_global *glob,
			      struct page *page,
			      bool no_wait, bool interruptible)
{

	struct ttm_mem_zone *zone = NULL;

	/**
	 * Page allocations may be registed in a single zone
	 * only if highmem or !dma32.
	 */

#ifdef CONFIG_HIGHMEM
	if (PageHighMem(page) && glob->zone_highmem != NULL)
		zone = glob->zone_highmem;
#else
	if (glob->zone_dma32 && page_to_pfn(page) > 0x00100000UL)
		zone = glob->zone_kernel;
#endif
	return ttm_mem_global_alloc_zone(glob, zone, PAGE_SIZE, no_wait,
					 interruptible);
}