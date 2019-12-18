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
struct vm_area_struct {int /*<<< orphan*/  vm_mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER_CRITICAL (unsigned long) ; 
 int /*<<< orphan*/  EXIT_CRITICAL (unsigned long) ; 
 int /*<<< orphan*/  FLUSH_ITLB_VM (struct vm_area_struct*) ; 
 int PAGE_MASK ; 
 int UNIQUE_ENTRYHI (int) ; 
 int cpu_asid (int,int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_context (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtc0_tlbw_hazard () ; 
 int read_c0_entryhi () ; 
 int read_c0_index () ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  tlb_probe () ; 
 int /*<<< orphan*/  tlb_probe_hazard () ; 
 int /*<<< orphan*/  tlb_write_indexed () ; 
 int /*<<< orphan*/  tlbw_use_hazard () ; 
 int /*<<< orphan*/  write_c0_entryhi (int) ; 
 int /*<<< orphan*/  write_c0_entrylo0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_entrylo1 (int /*<<< orphan*/ ) ; 

void local_flush_tlb_page(struct vm_area_struct *vma, unsigned long page)
{
	int cpu = smp_processor_id();

	if (cpu_context(cpu, vma->vm_mm) != 0) {
		unsigned long flags;
		int oldpid, newpid, idx;

		newpid = cpu_asid(cpu, vma->vm_mm);
		page &= (PAGE_MASK << 1);
		ENTER_CRITICAL(flags);
		oldpid = read_c0_entryhi();
		write_c0_entryhi(page | newpid);
		mtc0_tlbw_hazard();
		tlb_probe();
		tlb_probe_hazard();
		idx = read_c0_index();
		write_c0_entrylo0(0);
		write_c0_entrylo1(0);
		if (idx < 0)
			goto finish;
		/* Make sure all entries differ. */
		write_c0_entryhi(UNIQUE_ENTRYHI(idx));
		mtc0_tlbw_hazard();
		tlb_write_indexed();
		tlbw_use_hazard();

	finish:
		write_c0_entryhi(oldpid);
		FLUSH_ITLB_VM(vma);
		EXIT_CRITICAL(flags);
	}
}