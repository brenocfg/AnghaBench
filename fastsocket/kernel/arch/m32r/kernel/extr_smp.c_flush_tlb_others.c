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
struct vm_area_struct {int dummy; } ;
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  cpumask_t ;
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  INVALIDATE_TLB_IPI ; 
 int /*<<< orphan*/  __save_flags (unsigned long) ; 
 int /*<<< orphan*/  atomic_set_mask (unsigned long,int /*<<< orphan*/ *) ; 
 int cpu_isset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_online_map ; 
 unsigned long* cpus_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpus_and (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cpus_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_cpumask ; 
 struct mm_struct* flush_mm ; 
 unsigned long flush_va ; 
 struct vm_area_struct* flush_vma ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  send_IPI_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tlbstate_lock ; 

__attribute__((used)) static void flush_tlb_others(cpumask_t cpumask, struct mm_struct *mm,
	struct vm_area_struct *vma, unsigned long va)
{
	unsigned long *mask;
#ifdef DEBUG_SMP
	unsigned long flags;
	__save_flags(flags);
	if (!(flags & 0x0040))	/* Interrupt Disable NONONO */
		BUG();
#endif /* DEBUG_SMP */

	/*
	 * A couple of (to be removed) sanity checks:
	 *
	 * - we do not send IPIs to not-yet booted CPUs.
	 * - current CPU must not be in mask
	 * - mask must exist :)
	 */
	BUG_ON(cpus_empty(cpumask));

	BUG_ON(cpu_isset(smp_processor_id(), cpumask));
	BUG_ON(!mm);

	/* If a CPU which we ran on has gone down, OK. */
	cpus_and(cpumask, cpumask, cpu_online_map);
	if (cpus_empty(cpumask))
		return;

	/*
	 * i'm not happy about this global shared spinlock in the
	 * MM hot path, but we'll see how contended it is.
	 * Temporarily this turns IRQs off, so that lockups are
	 * detected by the NMI watchdog.
	 */
	spin_lock(&tlbstate_lock);

	flush_mm = mm;
	flush_vma = vma;
	flush_va = va;
	mask=cpus_addr(cpumask);
	atomic_set_mask(*mask, (atomic_t *)&flush_cpumask);

	/*
	 * We have to send the IPI only to
	 * CPUs affected.
	 */
	send_IPI_mask(&cpumask, INVALIDATE_TLB_IPI, 0);

	while (!cpus_empty(flush_cpumask)) {
		/* nothing. lockup detection does not belong here */
		mb();
	}

	flush_mm = NULL;
	flush_vma = NULL;
	flush_va = 0;
	spin_unlock(&tlbstate_lock);
}