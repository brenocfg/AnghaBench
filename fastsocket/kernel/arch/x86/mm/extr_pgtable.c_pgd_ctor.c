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
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int KERNEL_PGD_BOUNDARY ; 
 int /*<<< orphan*/  KERNEL_PGD_PTRS ; 
 int PAGETABLE_LEVELS ; 
 int PAGE_SHIFT ; 
 scalar_t__ SHARED_KERNEL_PMD ; 
 int __pa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clone_pgd_range (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  paravirt_alloc_pmd_clone (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgd_list_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgd_set_mm (int /*<<< orphan*/ *,struct mm_struct*) ; 
 int /*<<< orphan*/ * swapper_pg_dir ; 

__attribute__((used)) static void pgd_ctor(struct mm_struct *mm, pgd_t *pgd)
{
	/* If the pgd points to a shared pagetable level (either the
	   ptes in non-PAE, or shared PMD in PAE), then just copy the
	   references from swapper_pg_dir. */
	if (PAGETABLE_LEVELS == 2 ||
	    (PAGETABLE_LEVELS == 3 && SHARED_KERNEL_PMD) ||
	    PAGETABLE_LEVELS == 4) {
		clone_pgd_range(pgd + KERNEL_PGD_BOUNDARY,
				swapper_pg_dir + KERNEL_PGD_BOUNDARY,
				KERNEL_PGD_PTRS);
		paravirt_alloc_pmd_clone(__pa(pgd) >> PAGE_SHIFT,
					 __pa(swapper_pg_dir) >> PAGE_SHIFT,
					 KERNEL_PGD_BOUNDARY,
					 KERNEL_PGD_PTRS);
	}

	/* list required to sync kernel mapping updates */
	if (!SHARED_KERNEL_PMD) {
		pgd_set_mm(pgd, mm);
		pgd_list_add(pgd);
	}
}