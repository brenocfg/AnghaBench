#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct page {int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {scalar_t__ n_aliases; } ;
struct TYPE_4__ {TYPE_1__ dcache; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PG_dcache_dirty ; 
 int /*<<< orphan*/  __flush_purge_region (void*,int /*<<< orphan*/ ) ; 
 TYPE_2__ boot_cpu_data ; 
 void* kmap_coherent (struct page*,unsigned long) ; 
 int /*<<< orphan*/  kunmap_coherent (void*) ; 
 scalar_t__ page_address (struct page*) ; 
 scalar_t__ page_mapped (struct page*) ; 
 scalar_t__ pages_do_alias (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void __flush_anon_page(struct page *page, unsigned long vmaddr)
{
	unsigned long addr = (unsigned long) page_address(page);

	if (pages_do_alias(addr, vmaddr)) {
		if (boot_cpu_data.dcache.n_aliases && page_mapped(page) &&
		    !test_bit(PG_dcache_dirty, &page->flags)) {
			void *kaddr;

			kaddr = kmap_coherent(page, vmaddr);
			/* XXX.. For now kunmap_coherent() does a purge */
			/* __flush_purge_region((void *)kaddr, PAGE_SIZE); */
			kunmap_coherent(kaddr);
		} else
			__flush_purge_region((void *)addr, PAGE_SIZE);
	}
}