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
 unsigned long ASID_MASK ; 
 unsigned long KSEG1 ; 
 int TLBSIZE ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  pectx_set (int /*<<< orphan*/ ) ; 
 unsigned long pevn_get () ; 
 int /*<<< orphan*/  pevn_set (unsigned long) ; 
 int /*<<< orphan*/  tlb_write_indexed () ; 
 int tlblock_get () ; 
 int /*<<< orphan*/  tlbpt_set (int) ; 

void local_flush_tlb_all(void)
{
	unsigned long flags;
	unsigned long old_ASID;
	int entry;

	local_irq_save(flags);
	old_ASID = pevn_get() & ASID_MASK;
	pectx_set(0);			/* invalid */
	entry = tlblock_get();		/* skip locked entries*/

	for (; entry < TLBSIZE; entry++) {
		tlbpt_set(entry);
		pevn_set(KSEG1);
		barrier();
		tlb_write_indexed();
	}
	pevn_set(old_ASID);
	local_irq_restore(flags);
}