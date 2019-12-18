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
 TYPE_1__* current ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  update_dtlb (unsigned long,int /*<<< orphan*/ ) ; 

void update_mmu_cache(struct vm_area_struct *vma,
		      unsigned long address, pte_t pte)
{
	unsigned long flags;

	/* ptrace may call this routine */
	if (vma && current->active_mm != vma->vm_mm)
		return;

	local_irq_save(flags);
	update_dtlb(address, pte);
	local_irq_restore(flags);
}