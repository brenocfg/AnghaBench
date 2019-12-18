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
struct page {int dummy; } ;
struct address_space {int dummy; } ;

/* Variables and functions */
 scalar_t__ PageHighMem (struct page*) ; 
 int /*<<< orphan*/  SetPageDcacheDirty (struct page*) ; 
 int /*<<< orphan*/  flush_data_cache_page (unsigned long) ; 
 int /*<<< orphan*/  mapping_mapped (struct address_space*) ; 
 scalar_t__ page_address (struct page*) ; 
 struct address_space* page_mapping (struct page*) ; 

void __flush_dcache_page(struct page *page)
{
	struct address_space *mapping = page_mapping(page);
	unsigned long addr;

	if (PageHighMem(page))
		return;
	if (mapping && !mapping_mapped(mapping)) {
		SetPageDcacheDirty(page);
		return;
	}

	/*
	 * We could delay the flush for the !page_mapping case too.  But that
	 * case is for exec env/arg pages and those are %99 certainly going to
	 * get faulted into the tlb (and thus flushed) anyways.
	 */
	addr = (unsigned long) page_address(page);
	flush_data_cache_page(addr);
}