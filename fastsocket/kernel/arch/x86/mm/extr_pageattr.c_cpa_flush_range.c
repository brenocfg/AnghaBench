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
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 unsigned long PAGE_ALIGN (unsigned long) ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int _PAGE_PRESENT ; 
 int /*<<< orphan*/  __cpa_flush_range ; 
 int /*<<< orphan*/  clflush_cache_range (void*,scalar_t__) ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int /*<<< orphan*/ * lookup_address (unsigned long,unsigned int*) ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int pte_val (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cpa_flush_range(unsigned long start, int numpages, int cache)
{
	unsigned int i, level;
	unsigned long addr;

	BUG_ON(irqs_disabled());
	WARN_ON(PAGE_ALIGN(start) != start);

	on_each_cpu(__cpa_flush_range, NULL, 1);

	if (!cache)
		return;

	/*
	 * We only need to flush on one CPU,
	 * clflush is a MESI-coherent instruction that
	 * will cause all other CPUs to flush the same
	 * cachelines:
	 */
	for (i = 0, addr = start; i < numpages; i++, addr += PAGE_SIZE) {
		pte_t *pte = lookup_address(addr, &level);

		/*
		 * Only flush present addresses:
		 */
		if (pte && (pte_val(*pte) & _PAGE_PRESENT))
			clflush_cache_range((void *) addr, PAGE_SIZE);
	}
}