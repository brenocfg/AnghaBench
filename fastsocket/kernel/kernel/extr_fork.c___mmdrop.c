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
struct mm_struct {int /*<<< orphan*/  pmd_huge_pte; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  VM_BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_context (struct mm_struct*) ; 
 int /*<<< orphan*/  free_mm (struct mm_struct*) ; 
 struct mm_struct init_mm ; 
 int /*<<< orphan*/  mm_free_pgd (struct mm_struct*) ; 
 int /*<<< orphan*/  mmu_notifier_mm_destroy (struct mm_struct*) ; 

void __mmdrop(struct mm_struct *mm)
{
	BUG_ON(mm == &init_mm);
	mm_free_pgd(mm);
	destroy_context(mm);
	mmu_notifier_mm_destroy(mm);
#ifdef CONFIG_TRANSPARENT_HUGEPAGE
	VM_BUG_ON(mm->pmd_huge_pte);
#endif
	free_mm(mm);
}