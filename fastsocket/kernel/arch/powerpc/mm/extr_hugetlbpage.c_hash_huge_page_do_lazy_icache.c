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
 unsigned long HPTE_R_N ; 
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  PG_arch_1 ; 
 int /*<<< orphan*/  PageReserved (struct page*) ; 
 int /*<<< orphan*/  __flush_dcache_icache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 
 int /*<<< orphan*/  pfn_valid (int /*<<< orphan*/ ) ; 
 struct page* pte_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int hash_huge_page_do_lazy_icache(unsigned long rflags,
					pte_t pte, int trap, unsigned long sz)
{
	struct page *page;
	int i;

	if (!pfn_valid(pte_pfn(pte)))
		return rflags;

	page = pte_page(pte);

	/* page is dirty */
	if (!test_bit(PG_arch_1, &page->flags) && !PageReserved(page)) {
		if (trap == 0x400) {
			for (i = 0; i < (sz / PAGE_SIZE); i++)
				__flush_dcache_icache(page_address(page+i));
			set_bit(PG_arch_1, &page->flags);
		} else {
			rflags |= HPTE_R_N;
		}
	}
	return rflags;
}