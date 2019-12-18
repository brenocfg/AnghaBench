#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mm_struct {TYPE_1__* pmd_huge_pte; int /*<<< orphan*/  page_table_lock; } ;
typedef  TYPE_1__* pgtable_t ;
struct TYPE_3__ {int /*<<< orphan*/  lru; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VM_BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_can_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void prepare_pmd_huge_pte(pgtable_t pgtable,
				 struct mm_struct *mm)
{
	VM_BUG_ON(spin_can_lock(&mm->page_table_lock));

	/* FIFO */
	if (!mm->pmd_huge_pte)
		INIT_LIST_HEAD(&pgtable->lru);
	else
		list_add(&pgtable->lru, &mm->pmd_huge_pte->lru);
	mm->pmd_huge_pte = pgtable;
}