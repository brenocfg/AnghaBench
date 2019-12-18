#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {int /*<<< orphan*/  vm_mm; } ;
typedef  int /*<<< orphan*/  pte_t ;
struct TYPE_3__ {int /*<<< orphan*/ * regs; } ;
struct TYPE_4__ {TYPE_1__ thread; } ;

/* Variables and functions */
 unsigned long TASK_SIZE ; 
 unsigned long TRAP (int /*<<< orphan*/ *) ; 
 unsigned long _PAGE_EXEC ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  hash_preload (int /*<<< orphan*/ ,unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  pte_young (int /*<<< orphan*/ ) ; 

void update_mmu_cache(struct vm_area_struct *vma, unsigned long address,
		      pte_t pte)
{
#ifdef CONFIG_PPC_STD_MMU
	unsigned long access = 0, trap;

	/* We only want HPTEs for linux PTEs that have _PAGE_ACCESSED set */
	if (!pte_young(pte) || address >= TASK_SIZE)
		return;

	/* We try to figure out if we are coming from an instruction
	 * access fault and pass that down to __hash_page so we avoid
	 * double-faulting on execution of fresh text. We have to test
	 * for regs NULL since init will get here first thing at boot
	 *
	 * We also avoid filling the hash if not coming from a fault
	 */
	if (current->thread.regs == NULL)
		return;
	trap = TRAP(current->thread.regs);
	if (trap == 0x400)
		access |= _PAGE_EXEC;
	else if (trap != 0x300)
		return;
	hash_preload(vma->vm_mm, address, access, trap);
#endif /* CONFIG_PPC_STD_MMU */
}