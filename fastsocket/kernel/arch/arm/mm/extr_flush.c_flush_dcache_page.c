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
struct page {int /*<<< orphan*/  flags; } ;
struct address_space {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PG_dcache_dirty ; 
 int /*<<< orphan*/  PageHighMem (struct page*) ; 
 int /*<<< orphan*/  __flush_dcache_aliases (struct address_space*,struct page*) ; 
 int /*<<< orphan*/  __flush_dcache_page (struct address_space*,struct page*) ; 
 int /*<<< orphan*/  __flush_icache_all () ; 
 scalar_t__ cache_is_vivt () ; 
 int /*<<< orphan*/  mapping_mapped (struct address_space*) ; 
 struct address_space* page_mapping (struct page*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void flush_dcache_page(struct page *page)
{
	struct address_space *mapping = page_mapping(page);

#ifndef CONFIG_SMP
	if (!PageHighMem(page) && mapping && !mapping_mapped(mapping))
		set_bit(PG_dcache_dirty, &page->flags);
	else
#endif
	{
		__flush_dcache_page(mapping, page);
		if (mapping && cache_is_vivt())
			__flush_dcache_aliases(mapping, page);
		else if (mapping)
			__flush_icache_all();
	}
}