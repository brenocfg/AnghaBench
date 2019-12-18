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
struct TYPE_2__ {unsigned int id; } ;
struct mm_struct {TYPE_1__ context; } ;

/* Variables and functions */
 unsigned int ASID_FIRST_VERSION ; 
 unsigned int ASID_MASK ; 
 int /*<<< orphan*/  __flush_icache_all () ; 
 int /*<<< orphan*/  cpu_asid_lock ; 
 unsigned int cpu_last_asid ; 
 int /*<<< orphan*/  cpumask_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_of (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsb () ; 
 int /*<<< orphan*/  flush_tlb_all () ; 
 scalar_t__ icache_is_vivt_asid_tagged () ; 
 int /*<<< orphan*/  isb () ; 
 int /*<<< orphan*/  mm_cpumask (struct mm_struct*) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

void __new_context(struct mm_struct *mm)
{
	unsigned int asid;

	spin_lock(&cpu_asid_lock);
	asid = ++cpu_last_asid;
	if (asid == 0)
		asid = cpu_last_asid = ASID_FIRST_VERSION;

	/*
	 * If we've used up all our ASIDs, we need
	 * to start a new version and flush the TLB.
	 */
	if (unlikely((asid & ~ASID_MASK) == 0)) {
		asid = ++cpu_last_asid;
		/* set the reserved ASID before flushing the TLB */
		asm("mcr	p15, 0, %0, c13, c0, 1	@ set reserved context ID\n"
		    :
		    : "r" (0));
		isb();
		flush_tlb_all();
		if (icache_is_vivt_asid_tagged()) {
			__flush_icache_all();
			dsb();
		}
	}
	spin_unlock(&cpu_asid_lock);

	cpumask_copy(mm_cpumask(mm), cpumask_of(smp_processor_id()));
	mm->context.id = asid;
}