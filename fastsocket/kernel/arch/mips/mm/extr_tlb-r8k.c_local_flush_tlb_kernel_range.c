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

/* Variables and functions */
 unsigned long CKSEG0 ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int TFP_TLB_SIZE ; 
 int /*<<< orphan*/  local_flush_tlb_all () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 long read_c0_tlbset () ; 
 int /*<<< orphan*/  tlb_probe () ; 
 int /*<<< orphan*/  tlb_write () ; 
 int /*<<< orphan*/  write_c0_entryhi (unsigned long) ; 
 int /*<<< orphan*/  write_c0_entrylo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_vaddr (unsigned long) ; 

void local_flush_tlb_kernel_range(unsigned long start, unsigned long end)
{
	unsigned long size, flags;

	size = (end - start + (PAGE_SIZE - 1)) >> PAGE_SHIFT;
	size = (size + 1) >> 1;

	if (size > TFP_TLB_SIZE / 2) {
		local_flush_tlb_all();
		return;
	}

	local_irq_save(flags);

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

	local_irq_restore(flags);
}