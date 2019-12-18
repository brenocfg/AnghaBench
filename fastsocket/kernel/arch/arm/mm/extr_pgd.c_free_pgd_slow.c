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
typedef  int /*<<< orphan*/  pgtable_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int /*<<< orphan*/  free_pages (unsigned long,int) ; 
 int /*<<< orphan*/  pmd_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_bad (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmd_free (struct mm_struct*,int /*<<< orphan*/ *) ; 
 scalar_t__ pmd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_off (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_pgtable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_free (struct mm_struct*,int /*<<< orphan*/ ) ; 

void free_pgd_slow(struct mm_struct *mm, pgd_t *pgd)
{
	pmd_t *pmd;
	pgtable_t pte;

	if (!pgd)
		return;

	/* pgd is always present and good */
	pmd = pmd_off(pgd, 0);
	if (pmd_none(*pmd))
		goto free;
	if (pmd_bad(*pmd)) {
		pmd_ERROR(*pmd);
		pmd_clear(pmd);
		goto free;
	}

	pte = pmd_pgtable(*pmd);
	pmd_clear(pmd);
	pte_free(mm, pte);
	pmd_free(mm, pmd);
free:
	free_pages((unsigned long) pgd, 2);
}