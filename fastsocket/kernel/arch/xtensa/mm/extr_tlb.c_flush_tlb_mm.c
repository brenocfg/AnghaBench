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
struct mm_struct {scalar_t__ context; } ;
struct TYPE_2__ {struct mm_struct* active_mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  __get_new_mmu_context (struct mm_struct*) ; 
 int /*<<< orphan*/  __load_mmu_context (struct mm_struct*) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  local_irq_restore (int) ; 
 int /*<<< orphan*/  local_save_flags (int) ; 

void flush_tlb_mm(struct mm_struct *mm)
{
	if (mm == current->active_mm) {
		int flags;
		local_save_flags(flags);
		__get_new_mmu_context(mm);
		__load_mmu_context(mm);
		local_irq_restore(flags);
	}
	else
		mm->context = 0;
}