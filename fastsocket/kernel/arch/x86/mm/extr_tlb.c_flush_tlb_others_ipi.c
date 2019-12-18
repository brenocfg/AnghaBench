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
union smp_flush_state {unsigned long flush_va; int /*<<< orphan*/  tlbstate_lock; struct mm_struct* flush_mm; int /*<<< orphan*/  flush_cpumask; } ;
struct mm_struct {int dummy; } ;
struct cpumask {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* send_IPI_mask ) (int /*<<< orphan*/ ,scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ INVALIDATE_TLB_VECTOR_START ; 
 unsigned int NUM_INVALIDATE_TLB_VECTORS ; 
 TYPE_1__* apic ; 
 int /*<<< orphan*/  cpu_relax () ; 
 scalar_t__ cpumask_andnot (int /*<<< orphan*/ ,struct cpumask const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_of (unsigned int) ; 
 union smp_flush_state* flush_state ; 
 unsigned int smp_processor_id () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  to_cpumask (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void flush_tlb_others_ipi(const struct cpumask *cpumask,
				 struct mm_struct *mm, unsigned long va)
{
	unsigned int sender;
	union smp_flush_state *f;

	/* Caller has disabled preemption */
	sender = smp_processor_id() % NUM_INVALIDATE_TLB_VECTORS;
	f = &flush_state[sender];

	/*
	 * Could avoid this lock when
	 * num_online_cpus() <= NUM_INVALIDATE_TLB_VECTORS, but it is
	 * probably not worth checking this for a cache-hot lock.
	 */
	spin_lock(&f->tlbstate_lock);

	f->flush_mm = mm;
	f->flush_va = va;
	if (cpumask_andnot(to_cpumask(f->flush_cpumask), cpumask, cpumask_of(smp_processor_id()))) {
		/*
		 * We have to send the IPI only to
		 * CPUs affected.
		 */
		apic->send_IPI_mask(to_cpumask(f->flush_cpumask),
			      INVALIDATE_TLB_VECTOR_START + sender);

		while (!cpumask_empty(to_cpumask(f->flush_cpumask)))
			cpu_relax();
	}

	f->flush_mm = NULL;
	f->flush_va = 0;
	spin_unlock(&f->tlbstate_lock);
}