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
struct TYPE_2__ {int tlbsize; } ;

/* Variables and functions */
 unsigned long ASID_MASK ; 
 int /*<<< orphan*/  BARRIER ; 
 TYPE_1__ current_cpu_data ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  printk (char*) ; 
 scalar_t__ r3k_have_wired_reg ; 
 unsigned long read_c0_entryhi () ; 
 int read_c0_wired () ; 
 int /*<<< orphan*/  tlb_write_indexed () ; 
 int /*<<< orphan*/  write_c0_entryhi (unsigned long) ; 
 int /*<<< orphan*/  write_c0_entrylo0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_index (int) ; 

void local_flush_tlb_all(void)
{
	unsigned long flags;
	unsigned long old_ctx;
	int entry;

#ifdef DEBUG_TLB
	printk("[tlball]");
#endif

	local_irq_save(flags);
	old_ctx = read_c0_entryhi() & ASID_MASK;
	write_c0_entrylo0(0);
	entry = r3k_have_wired_reg ? read_c0_wired() : 8;
	for (; entry < current_cpu_data.tlbsize; entry++) {
		write_c0_index(entry << 8);
		write_c0_entryhi((entry | 0x80000) << 12);
		BARRIER;
		tlb_write_indexed();
	}
	write_c0_entryhi(old_ctx);
	local_irq_restore(flags);
}