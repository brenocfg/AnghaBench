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
struct mm_struct {scalar_t__ context; } ;
typedef  int /*<<< orphan*/  smpfunc_t ;
typedef  int /*<<< orphan*/  cpumask_t ;

/* Variables and functions */
 scalar_t__ BTFIXUP_CALL (int /*<<< orphan*/  (*) (struct vm_area_struct*,unsigned long,unsigned long)) ; 
 scalar_t__ NO_CONTEXT ; 
 int /*<<< orphan*/  cpu_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpus_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_flush_tlb_range (struct vm_area_struct*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/ * mm_cpumask (struct mm_struct*) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  xc3 (int /*<<< orphan*/ ,unsigned long,unsigned long,unsigned long) ; 

void smp_flush_tlb_range(struct vm_area_struct *vma, unsigned long start,
			 unsigned long end)
{
	struct mm_struct *mm = vma->vm_mm;

	if (mm->context != NO_CONTEXT) {
		cpumask_t cpu_mask = *mm_cpumask(mm);
		cpu_clear(smp_processor_id(), cpu_mask);
		if (!cpus_empty(cpu_mask))
			xc3((smpfunc_t) BTFIXUP_CALL(local_flush_tlb_range), (unsigned long) vma, start, end);
		local_flush_tlb_range(vma, start, end);
	}
}