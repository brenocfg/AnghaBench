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

/* Variables and functions */
 unsigned long PAGE_ALIGN (unsigned long) ; 
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  PG_arch_1 ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct page* virt_to_page (unsigned long) ; 

void
dma_mark_clean(void *addr, size_t size)
{
	unsigned long pg_addr, end;

	pg_addr = PAGE_ALIGN((unsigned long) addr);
	end = (unsigned long) addr + size;
	while (pg_addr + PAGE_SIZE <= end) {
		struct page *page = virt_to_page(pg_addr);
		set_bit(PG_arch_1, &page->flags);
		pg_addr += PAGE_SIZE;
	}
}