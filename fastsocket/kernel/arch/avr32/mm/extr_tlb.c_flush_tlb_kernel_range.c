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
 int MMU_DTLB_ENTRIES ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  __flush_tlb_page (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  flush_tlb_all () ; 
 unsigned long get_asid () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

void flush_tlb_kernel_range(unsigned long start, unsigned long end)
{
	unsigned long flags;
	int size;

	size = (end - start + (PAGE_SIZE - 1)) >> PAGE_SHIFT;
	if (size > (MMU_DTLB_ENTRIES / 4)) { /* Too many entries to flush */
		flush_tlb_all();
	} else {
		unsigned long asid;

		local_irq_save(flags);
		asid = get_asid();

		start &= PAGE_MASK;
		end += (PAGE_SIZE - 1);
		end &= PAGE_MASK;

		while (start < end) {
			__flush_tlb_page(asid, start);
			start += PAGE_SIZE;
		}
		local_irq_restore(flags);
	}
}