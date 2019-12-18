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
struct mm_struct {int context; } ;

/* Variables and functions */
 int ASID_MASK ; 
 int /*<<< orphan*/  get_new_mmu_context (struct mm_struct*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  pevn_set (int) ; 

__attribute__((used)) static inline void
drop_mmu_context(struct mm_struct *mm)
{
	unsigned long flags;

	local_irq_save(flags);
	get_new_mmu_context(mm);
	pevn_set(mm->context & ASID_MASK);
	local_irq_restore(flags);
}