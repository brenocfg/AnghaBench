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
struct mm_struct {unsigned long* context; } ;
typedef  int /*<<< orphan*/  cpumask_t ;
struct TYPE_2__ {struct mm_struct* mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLUSH_ALL ; 
 unsigned long NO_CONTEXT ; 
 int /*<<< orphan*/  activate_context (struct mm_struct*) ; 
 int /*<<< orphan*/  cpu_clear (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_clear_cpu (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpus_empty (int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  flush_tlb_others (int /*<<< orphan*/ ,struct mm_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/ * mm_cpumask (struct mm_struct*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int smp_processor_id () ; 

void smp_flush_tlb_mm(struct mm_struct *mm)
{
	int cpu_id;
	cpumask_t cpu_mask;
	unsigned long *mmc;
	unsigned long flags;

	preempt_disable();
	cpu_id = smp_processor_id();
	mmc = &mm->context[cpu_id];
	cpu_mask = *mm_cpumask(mm);
	cpu_clear(cpu_id, cpu_mask);

	if (*mmc != NO_CONTEXT) {
		local_irq_save(flags);
		*mmc = NO_CONTEXT;
		if (mm == current->mm)
			activate_context(mm);
		else
			cpumask_clear_cpu(cpu_id, mm_cpumask(mm));
		local_irq_restore(flags);
	}
	if (!cpus_empty(cpu_mask))
		flush_tlb_others(cpu_mask, mm, NULL, FLUSH_ALL);

	preempt_enable();
}