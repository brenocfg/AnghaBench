#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct lguest {TYPE_1__* pgdirs; } ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;
struct TYPE_2__ {int /*<<< orphan*/ * pgdir; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int PAGE_SHIFT ; 
 int SWITCHER_PGD_INDEX ; 
 unsigned int SWITCHER_PMD_INDEX ; 
 int /*<<< orphan*/ * __va (int) ; 
 int pgd_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_pgd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_pmd (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void release_all_pagetables(struct lguest *lg)
{
	unsigned int i, j;

	/* Every shadow pagetable this Guest has */
	for (i = 0; i < ARRAY_SIZE(lg->pgdirs); i++)
		if (lg->pgdirs[i].pgdir) {
#ifdef CONFIG_X86_PAE
			pgd_t *spgd;
			pmd_t *pmdpage;
			unsigned int k;

			/* Get the last pmd page. */
			spgd = lg->pgdirs[i].pgdir + SWITCHER_PGD_INDEX;
			pmdpage = __va(pgd_pfn(*spgd) << PAGE_SHIFT);

			/*
			 * And release the pmd entries of that pmd page,
			 * except for the switcher pmd.
			 */
			for (k = 0; k < SWITCHER_PMD_INDEX; k++)
				release_pmd(&pmdpage[k]);
#endif
			/* Every PGD entry except the Switcher at the top */
			for (j = 0; j < SWITCHER_PGD_INDEX; j++)
				release_pgd(lg->pgdirs[i].pgdir + j);
		}
}