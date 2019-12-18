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
 int KSEG1 ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int TLBSIZE ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  local_flush_tlb_all () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  pectx_set (int /*<<< orphan*/ ) ; 
 int pevn_get () ; 
 int /*<<< orphan*/  pevn_set (int) ; 
 int /*<<< orphan*/  tlb_probe () ; 
 int /*<<< orphan*/  tlb_write_indexed () ; 
 long tlbpt_get () ; 

void local_flush_tlb_kernel_range(unsigned long start, unsigned long end)
{
	unsigned long flags;
	int size;

	local_irq_save(flags);
	size = (end - start + (PAGE_SIZE - 1)) >> PAGE_SHIFT;
	if (size <= TLBSIZE) {
		int pid = pevn_get();

		start &= PAGE_MASK;
		end += PAGE_SIZE - 1;
		end &= PAGE_MASK;

		while (start < end) {
			long idx;

			pevn_set(start);
			start += PAGE_SIZE;
			tlb_probe();
			idx = tlbpt_get();
			if (idx < 0)
				continue;
			pectx_set(0);
			pevn_set(KSEG1);
			barrier();
			tlb_write_indexed();
		}
		pevn_set(pid);
	} else {
		local_flush_tlb_all();
	}

	local_irq_restore(flags);
}