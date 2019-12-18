#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  scalar_t__ ppnum_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_5__ {int /*<<< orphan*/  vmp_lopage; } ;

/* Variables and functions */
 int VM_MEM_MODIFIED ; 
 int VM_MEM_REFERENCED ; 
 int /*<<< orphan*/  VM_PAGE_SET_PHYS_PAGE (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  assert (scalar_t__) ; 
 int /*<<< orphan*/  panic (char*,scalar_t__) ; 
 int /*<<< orphan*/  pmap_clear_refmod (scalar_t__,int) ; 
 int /*<<< orphan*/  pmap_valid_page (scalar_t__) ; 
 scalar_t__ vm_page_fictitious_addr ; 
 scalar_t__ vm_page_guard_addr ; 
 TYPE_1__ vm_page_template ; 

void
vm_page_init(
	vm_page_t	mem,
	ppnum_t		phys_page,
	boolean_t	lopage)
{
	assert(phys_page);

#if	DEBUG
	if ((phys_page != vm_page_fictitious_addr) && (phys_page != vm_page_guard_addr)) {
		if (!(pmap_valid_page(phys_page))) {
			panic("vm_page_init: non-DRAM phys_page 0x%x\n", phys_page);
		}
	}
#endif
	*mem = vm_page_template;

	VM_PAGE_SET_PHYS_PAGE(mem, phys_page);
#if 0
	/*
	 * we're leaving this turned off for now... currently pages
	 * come off the free list and are either immediately dirtied/referenced
	 * due to zero-fill or COW faults, or are used to read or write files...
	 * in the file I/O case, the UPL mechanism takes care of clearing
	 * the state of the HW ref/mod bits in a somewhat fragile way.
	 * Since we may change the way this works in the future (to toughen it up),
	 * I'm leaving this as a reminder of where these bits could get cleared
	 */

	/*
	 * make sure both the h/w referenced and modified bits are
	 * clear at this point... we are especially dependent on 
	 * not finding a 'stale' h/w modified in a number of spots
	 * once this page goes back into use
	 */
	pmap_clear_refmod(phys_page, VM_MEM_MODIFIED | VM_MEM_REFERENCED);
#endif
	mem->vmp_lopage = lopage;
}