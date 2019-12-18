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
struct mm_struct {int /*<<< orphan*/  mm_users; } ;
struct TYPE_2__ {struct mm_struct* active_mm; } ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 
 TYPE_1__* current ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  local_finish_flush_tlb_mm (struct mm_struct*) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  mm_cpumask (struct mm_struct*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  smp_call_function_many (int /*<<< orphan*/ ,void (*) (void*),struct mm_struct*,int) ; 

void
smp_flush_tlb_mm (struct mm_struct *mm)
{
	preempt_disable();
	/* this happens for the common case of a single-threaded fork():  */
	if (likely(mm == current->active_mm && atomic_read(&mm->mm_users) == 1))
	{
		local_finish_flush_tlb_mm(mm);
		preempt_enable();
		return;
	}

	smp_call_function_many(mm_cpumask(mm),
		(void (*)(void *))local_finish_flush_tlb_mm, mm, 1);
	local_irq_disable();
	local_finish_flush_tlb_mm(mm);
	local_irq_enable();
	preempt_enable();
}