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
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int FIRST_KERNEL_PGD_NR ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PTRS_PER_PGD ; 
 scalar_t__ __get_free_pages (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clean_dcache_area (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * pgd_offset_k (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_alloc (struct mm_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_free (struct mm_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_alloc_map (struct mm_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_map_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_unmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pte_unmap_nested (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_pte_ext (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vectors_high () ; 

pgd_t *get_pgd_slow(struct mm_struct *mm)
{
	pgd_t *new_pgd, *init_pgd;
	pmd_t *new_pmd, *init_pmd;
	pte_t *new_pte, *init_pte;

	new_pgd = (pgd_t *)__get_free_pages(GFP_KERNEL, 2);
	if (!new_pgd)
		goto no_pgd;

	memset(new_pgd, 0, FIRST_KERNEL_PGD_NR * sizeof(pgd_t));

	/*
	 * Copy over the kernel and IO PGD entries
	 */
	init_pgd = pgd_offset_k(0);
	memcpy(new_pgd + FIRST_KERNEL_PGD_NR, init_pgd + FIRST_KERNEL_PGD_NR,
		       (PTRS_PER_PGD - FIRST_KERNEL_PGD_NR) * sizeof(pgd_t));

	clean_dcache_area(new_pgd, PTRS_PER_PGD * sizeof(pgd_t));

	if (!vectors_high()) {
		/*
		 * On ARM, first page must always be allocated since it
		 * contains the machine vectors.
		 */
		new_pmd = pmd_alloc(mm, new_pgd, 0);
		if (!new_pmd)
			goto no_pmd;

		new_pte = pte_alloc_map(mm, new_pmd, 0);
		if (!new_pte)
			goto no_pte;

		init_pmd = pmd_offset(init_pgd, 0);
		init_pte = pte_offset_map_nested(init_pmd, 0);
		set_pte_ext(new_pte, *init_pte, 0);
		pte_unmap_nested(init_pte);
		pte_unmap(new_pte);
	}

	return new_pgd;

no_pte:
	pmd_free(mm, new_pmd);
no_pmd:
	free_pages((unsigned long)new_pgd, 2);
no_pgd:
	return NULL;
}