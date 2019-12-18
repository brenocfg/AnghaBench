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
struct mm_struct {int /*<<< orphan*/  page_table_lock; } ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  pgd_populate (struct mm_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pgd_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_alloc_one (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/  pmd_free (struct mm_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pud_populate (struct mm_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pud_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int __pmd_alloc(struct mm_struct *mm, pud_t *pud, unsigned long address)
{
	pmd_t *new = pmd_alloc_one(mm, address);
	if (!new)
		return -ENOMEM;

	smp_wmb(); /* See comment in __pte_alloc */

	spin_lock(&mm->page_table_lock);
#ifndef __ARCH_HAS_4LEVEL_HACK
	if (pud_present(*pud))		/* Another has populated it */
		pmd_free(mm, new);
	else
		pud_populate(mm, pud, new);
#else
	if (pgd_present(*pud))		/* Another has populated it */
		pmd_free(mm, new);
	else
		pgd_populate(mm, pud, new);
#endif /* __ARCH_HAS_4LEVEL_HACK */
	spin_unlock(&mm->page_table_lock);
	return 0;
}