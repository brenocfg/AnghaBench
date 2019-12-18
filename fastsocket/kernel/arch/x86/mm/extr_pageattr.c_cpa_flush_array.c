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
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int CPA_PAGES_ARRAY ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int _PAGE_PRESENT ; 
 int /*<<< orphan*/  __cpa_flush_all ; 
 int /*<<< orphan*/  clflush_cache_range (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int /*<<< orphan*/ * lookup_address (unsigned long,unsigned int*) ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,void*,int) ; 
 scalar_t__ page_address (struct page*) ; 
 int pte_val (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cpa_flush_array(unsigned long *start, int numpages, int cache,
			    int in_flags, struct page **pages)
{
	unsigned int i, level;
	unsigned long do_wbinvd = cache && numpages >= 1024; /* 4M threshold */

	BUG_ON(irqs_disabled());

	on_each_cpu(__cpa_flush_all, (void *) do_wbinvd, 1);

	if (!cache || do_wbinvd)
		return;

	/*
	 * We only need to flush on one CPU,
	 * clflush is a MESI-coherent instruction that
	 * will cause all other CPUs to flush the same
	 * cachelines:
	 */
	for (i = 0; i < numpages; i++) {
		unsigned long addr;
		pte_t *pte;

		if (in_flags & CPA_PAGES_ARRAY)
			addr = (unsigned long)page_address(pages[i]);
		else
			addr = start[i];

		pte = lookup_address(addr, &level);

		/*
		 * Only flush present addresses:
		 */
		if (pte && (pte_val(*pte) & _PAGE_PRESENT))
			clflush_cache_range((void *)addr, PAGE_SIZE);
	}
}