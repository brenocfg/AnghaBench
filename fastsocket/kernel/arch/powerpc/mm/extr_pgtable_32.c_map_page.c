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
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int phys_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int PAGE_SHIFT ; 
 int _PAGE_HASHPTE ; 
 int _PAGE_PRESENT ; 
 int /*<<< orphan*/  __pgprot (int) ; 
 int /*<<< orphan*/  init_mm ; 
 int /*<<< orphan*/  pfn_pte (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgd_offset_k (unsigned long) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/ * pte_alloc_kernel (int /*<<< orphan*/ *,unsigned long) ; 
 int pte_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pud_offset (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  set_pte_at (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int map_page(unsigned long va, phys_addr_t pa, int flags)
{
	pmd_t *pd;
	pte_t *pg;
	int err = -ENOMEM;

	/* Use upper 10 bits of VA to index the first level map */
	pd = pmd_offset(pud_offset(pgd_offset_k(va), va), va);
	/* Use middle 10 bits of VA to index the second-level map */
	pg = pte_alloc_kernel(pd, va);
	if (pg != 0) {
		err = 0;
		/* The PTE should never be already set nor present in the
		 * hash table
		 */
		BUG_ON((pte_val(*pg) & (_PAGE_PRESENT | _PAGE_HASHPTE)) &&
		       flags);
		set_pte_at(&init_mm, va, pg, pfn_pte(pa >> PAGE_SHIFT,
						     __pgprot(flags)));
	}
	return err;
}