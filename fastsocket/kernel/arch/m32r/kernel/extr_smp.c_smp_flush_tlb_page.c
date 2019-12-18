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
struct vm_area_struct {struct mm_struct* vm_mm; } ;
struct mm_struct {unsigned long* context; } ;
typedef  int /*<<< orphan*/  cpumask_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 unsigned long MMU_CONTEXT_ASID_MASK ; 
 unsigned long NO_CONTEXT ; 
 unsigned long PAGE_MASK ; 
 int /*<<< orphan*/  __flush_tlb_page (unsigned long) ; 
 int /*<<< orphan*/  cpu_clear (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpus_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_tlb_others (int /*<<< orphan*/ ,struct mm_struct*,struct vm_area_struct*,unsigned long) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/ * mm_cpumask (struct mm_struct*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int smp_processor_id () ; 

void smp_flush_tlb_page(struct vm_area_struct *vma, unsigned long va)
{
	struct mm_struct *mm = vma->vm_mm;
	int cpu_id;
	cpumask_t cpu_mask;
	unsigned long *mmc;
	unsigned long flags;

	preempt_disable();
	cpu_id = smp_processor_id();
	mmc = &mm->context[cpu_id];
	cpu_mask = *mm_cpumask(mm);
	cpu_clear(cpu_id, cpu_mask);

#ifdef DEBUG_SMP
	if (!mm)
		BUG();
#endif

	if (*mmc != NO_CONTEXT) {
		local_irq_save(flags);
		va &= PAGE_MASK;
		va |= (*mmc & MMU_CONTEXT_ASID_MASK);
		__flush_tlb_page(va);
		local_irq_restore(flags);
	}
	if (!cpus_empty(cpu_mask))
		flush_tlb_others(cpu_mask, mm, vma, va);

	preempt_enable();
}