#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* active_mm; } ;
struct TYPE_5__ {unsigned long* context; } ;

/* Variables and functions */
 unsigned long FLUSH_ALL ; 
 unsigned long MMU_CONTEXT_ASID_MASK ; 
 unsigned long NO_CONTEXT ; 
 unsigned long PAGE_MASK ; 
 int /*<<< orphan*/  __flush_tlb_page (unsigned long) ; 
 int /*<<< orphan*/  activate_context (TYPE_1__*) ; 
 int /*<<< orphan*/  cpu_clear (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_isset (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_clear_cpu (int,int /*<<< orphan*/ ) ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  flush_cpumask ; 
 TYPE_1__* flush_mm ; 
 unsigned long flush_va ; 
 int /*<<< orphan*/  mm_cpumask (TYPE_1__*) ; 
 int smp_processor_id () ; 

void smp_invalidate_interrupt(void)
{
	int cpu_id = smp_processor_id();
	unsigned long *mmc = &flush_mm->context[cpu_id];

	if (!cpu_isset(cpu_id, flush_cpumask))
		return;

	if (flush_va == FLUSH_ALL) {
		*mmc = NO_CONTEXT;
		if (flush_mm == current->active_mm)
			activate_context(flush_mm);
		else
			cpumask_clear_cpu(cpu_id, mm_cpumask(flush_mm));
	} else {
		unsigned long va = flush_va;

		if (*mmc != NO_CONTEXT) {
			va &= PAGE_MASK;
			va |= (*mmc & MMU_CONTEXT_ASID_MASK);
			__flush_tlb_page(va);
		}
	}
	cpu_clear(cpu_id, flush_cpumask);
}