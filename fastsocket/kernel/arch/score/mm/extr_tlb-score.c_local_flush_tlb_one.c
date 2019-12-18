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
 int PAGE_MASK ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  pectx_set (int /*<<< orphan*/ ) ; 
 int pevn_get () ; 
 int /*<<< orphan*/  pevn_set (int) ; 
 int /*<<< orphan*/  tlb_probe () ; 
 int /*<<< orphan*/  tlb_write_indexed () ; 
 int tlbpt_get () ; 

void local_flush_tlb_one(unsigned long page)
{
	unsigned long flags;
	int oldpid, idx;

	local_irq_save(flags);
	oldpid = pevn_get();
	page &= (PAGE_MASK << 1);
	pevn_set(page);
	barrier();
	tlb_probe();
	idx = tlbpt_get();
	pectx_set(0);
	if (idx >= 0) {
		/* Make sure all entries differ. */
		pevn_set(KSEG1);
		barrier();
		tlb_write_indexed();
	}
	pevn_set(oldpid);
	local_irq_restore(flags);
}