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
struct mm_struct {int dummy; } ;
struct TYPE_2__ {scalar_t__ mm; struct mm_struct* active_mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLB_FLUSH_ALL ; 
 scalar_t__ cpumask_any_but (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  flush_tlb_others (int /*<<< orphan*/ ,struct mm_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  leave_mm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_flush_tlb () ; 
 int /*<<< orphan*/  mm_cpumask (struct mm_struct*) ; 
 scalar_t__ nr_cpu_ids ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  smp_processor_id () ; 

void flush_tlb_mm(struct mm_struct *mm)
{
	preempt_disable();

	if (current->active_mm == mm) {
		if (current->mm)
			local_flush_tlb();
		else
			leave_mm(smp_processor_id());
	}
	if (cpumask_any_but(mm_cpumask(mm), smp_processor_id()) < nr_cpu_ids)
		flush_tlb_others(mm_cpumask(mm), mm, TLB_FLUSH_ALL);

	preempt_enable();
}