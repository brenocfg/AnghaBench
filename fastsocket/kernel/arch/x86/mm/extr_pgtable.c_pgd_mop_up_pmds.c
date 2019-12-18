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
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int PREALLOCATED_PMDS ; 
 int /*<<< orphan*/  native_make_pgd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  paravirt_release_pmd (int) ; 
 scalar_t__ pgd_page_vaddr (int /*<<< orphan*/ ) ; 
 int pgd_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_free (struct mm_struct*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pgd_mop_up_pmds(struct mm_struct *mm, pgd_t *pgdp)
{
	int i;

	for(i = 0; i < PREALLOCATED_PMDS; i++) {
		pgd_t pgd = pgdp[i];

		if (pgd_val(pgd) != 0) {
			pmd_t *pmd = (pmd_t *)pgd_page_vaddr(pgd);

			pgdp[i] = native_make_pgd(0);

			paravirt_release_pmd(pgd_val(pgd) >> PAGE_SHIFT);
			pmd_free(mm, pmd);
		}
	}
}