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
struct mm_struct {scalar_t__ context; int /*<<< orphan*/  mm_users; } ;
typedef  int /*<<< orphan*/  smpfunc_t ;
typedef  int /*<<< orphan*/  cpumask_t ;
struct TYPE_2__ {struct mm_struct* active_mm; } ;

/* Variables and functions */
 scalar_t__ BTFIXUP_CALL (int /*<<< orphan*/  (*) (struct mm_struct*)) ; 
 scalar_t__ NO_CONTEXT ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_of (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpus_empty (int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  local_flush_tlb_mm (struct mm_struct*) ; 
 int /*<<< orphan*/ * mm_cpumask (struct mm_struct*) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  xc1 (int /*<<< orphan*/ ,unsigned long) ; 

void smp_flush_tlb_mm(struct mm_struct *mm)
{
	if(mm->context != NO_CONTEXT) {
		cpumask_t cpu_mask = *mm_cpumask(mm);
		cpu_clear(smp_processor_id(), cpu_mask);
		if (!cpus_empty(cpu_mask)) {
			xc1((smpfunc_t) BTFIXUP_CALL(local_flush_tlb_mm), (unsigned long) mm);
			if(atomic_read(&mm->mm_users) == 1 && current->active_mm == mm)
				cpumask_copy(mm_cpumask(mm),
					     cpumask_of(smp_processor_id()));
		}
		local_flush_tlb_mm(mm);
	}
}