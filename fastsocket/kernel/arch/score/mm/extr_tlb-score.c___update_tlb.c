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
struct vm_area_struct {scalar_t__ vm_mm; } ;
typedef  int /*<<< orphan*/  pte_t ;
struct TYPE_2__ {scalar_t__ active_mm; } ;

/* Variables and functions */
 int ASID_MASK ; 
 unsigned long PAGE_MASK ; 
 int /*<<< orphan*/  barrier () ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  pectx_set (int /*<<< orphan*/ ) ; 
 int pevn_get () ; 
 int /*<<< orphan*/  pevn_set (int) ; 
 int /*<<< orphan*/  pte_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlb_probe () ; 
 int /*<<< orphan*/  tlb_write_indexed () ; 
 int /*<<< orphan*/  tlb_write_random () ; 
 int tlbpt_get () ; 

void __update_tlb(struct vm_area_struct *vma, unsigned long address, pte_t pte)
{
	unsigned long flags;
	int idx, pid;

	/*
	 * Handle debugger faulting in for debugee.
	 */
	if (current->active_mm != vma->vm_mm)
		return;

	pid = pevn_get() & ASID_MASK;

	local_irq_save(flags);
	address &= PAGE_MASK;
	pevn_set(address | pid);
	barrier();
	tlb_probe();
	idx = tlbpt_get();
	pectx_set(pte_val(pte));
	pevn_set(address | pid);
	if (idx < 0)
		tlb_write_random();
	else
		tlb_write_indexed();

	pevn_set(pid);
	local_irq_restore(flags);
}