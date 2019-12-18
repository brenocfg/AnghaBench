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
struct mm_struct {int dummy; } ;

/* Variables and functions */
 long CKSEG0 ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int TFP_TLB_SIZE ; 
 int cpu_asid (int,struct mm_struct*) ; 
 int /*<<< orphan*/  cpu_context (int,struct mm_struct*) ; 
 int /*<<< orphan*/  drop_mmu_context (struct mm_struct*,int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int read_c0_entryhi () ; 
 long read_c0_tlbset () ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  tlb_probe () ; 
 int /*<<< orphan*/  tlb_write () ; 
 int /*<<< orphan*/  write_c0_entryhi (int) ; 
 int /*<<< orphan*/  write_c0_entrylo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_vaddr (unsigned long) ; 

void local_flush_tlb_range(struct vm_area_struct *vma, unsigned long start,
	unsigned long end)
{
	struct mm_struct *mm = vma->vm_mm;
	int cpu = smp_processor_id();
	unsigned long flags;
	int oldpid, newpid, size;

	if (!cpu_context(cpu, mm))
		return;

	size = (end - start + (PAGE_SIZE - 1)) >> PAGE_SHIFT;
	size = (size + 1) >> 1;

	local_irq_save(flags);

	if (size > TFP_TLB_SIZE / 2) {
		drop_mmu_context(mm, cpu);
		goto out_restore;
	}

	oldpid = read_c0_entryhi();
	newpid = cpu_asid(cpu, mm);

	write_c0_entrylo(0);

	start &= PAGE_MASK;
	end += (PAGE_SIZE - 1);
	end &= PAGE_MASK;
	while (start < end) {
		signed long idx;

		write_c0_vaddr(start);
		write_c0_entryhi(start);
		start += PAGE_SIZE;
		tlb_probe();
		idx = read_c0_tlbset();
		if (idx < 0)
			continue;

		write_c0_entryhi(CKSEG0 + (idx << (PAGE_SHIFT + 1)));
		tlb_write();
	}
	write_c0_entryhi(oldpid);

out_restore:
	local_irq_restore(flags);
}