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
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ PMD_SIZE ; 
 long PTRS_PER_PMD ; 
 long PTRS_PER_PUD ; 
 long PUD_SIZE ; 
 int _KERNPG_TABLE ; 
 unsigned long __PAGE_KERNEL_LARGE_EXEC ; 
 int __pa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __pmd (unsigned long) ; 
 int /*<<< orphan*/  __pud (int) ; 
 unsigned long __supported_pte_mask ; 
 scalar_t__ get_safe_page (int /*<<< orphan*/ ) ; 
 long pud_index (unsigned long) ; 
 int /*<<< orphan*/  set_pmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pud (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int res_phys_pud_init(pud_t *pud, unsigned long address, unsigned long end)
{
	long i, j;

	i = pud_index(address);
	pud = pud + i;
	for (; i < PTRS_PER_PUD; pud++, i++) {
		unsigned long paddr;
		pmd_t *pmd;

		paddr = address + i*PUD_SIZE;
		if (paddr >= end)
			break;

		pmd = (pmd_t *)get_safe_page(GFP_ATOMIC);
		if (!pmd)
			return -ENOMEM;
		set_pud(pud, __pud(__pa(pmd) | _KERNPG_TABLE));
		for (j = 0; j < PTRS_PER_PMD; pmd++, j++, paddr += PMD_SIZE) {
			unsigned long pe;

			if (paddr >= end)
				break;
			pe = __PAGE_KERNEL_LARGE_EXEC | paddr;
			pe &= __supported_pte_mask;
			set_pmd(pmd, __pmd(pe));
		}
	}
	return 0;
}