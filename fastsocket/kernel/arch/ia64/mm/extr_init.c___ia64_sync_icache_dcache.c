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
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  PG_arch_1 ; 
 unsigned long compound_order (struct page*) ; 
 int /*<<< orphan*/  flush_icache_range (unsigned long,unsigned long) ; 
 scalar_t__ page_address (struct page*) ; 
 struct page* pte_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
__ia64_sync_icache_dcache (pte_t pte)
{
	unsigned long addr;
	struct page *page;

	page = pte_page(pte);
	addr = (unsigned long) page_address(page);

	if (test_bit(PG_arch_1, &page->flags))
		return;				/* i-cache is already coherent with d-cache */

	flush_icache_range(addr, addr + (PAGE_SIZE << compound_order(page)));
	set_bit(PG_arch_1, &page->flags);	/* mark page as clean */
}