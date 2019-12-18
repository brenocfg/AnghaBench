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
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgprot_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned long PAGE_MASK ; 
 int /*<<< orphan*/  mk_pte_phys (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pgd_offset_k (unsigned long) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/ * pte_alloc_kernel (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  set_pte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int map_page(unsigned long va, unsigned long pa, pgprot_t prot)
{
	pgd_t *pge;
	pud_t *pue;
	pmd_t *pme;
	pte_t *pte;
	int err = -ENOMEM;

	/* Use upper 10 bits of VA to index the first level map */
	pge = pgd_offset_k(va);
	pue = pud_offset(pge, va);
	pme = pmd_offset(pue, va);

	/* Use middle 10 bits of VA to index the second-level map */
	pte = pte_alloc_kernel(pme, va);
	if (pte != 0) {
		err = 0;
		set_pte(pte, mk_pte_phys(pa & PAGE_MASK, prot));
	}

	return err;
}