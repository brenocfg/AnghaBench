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
typedef  size_t ppnum_t ;

/* Variables and functions */
 int /*<<< orphan*/  IS_MANAGED_PAGE (size_t) ; 
 unsigned int PHYS_MODIFIED ; 
 unsigned int PHYS_REFERENCED ; 
 unsigned int PMAP_OPTIONS_NOREFMOD ; 
 unsigned int VM_MEM_MODIFIED ; 
 unsigned int VM_MEM_REFERENCED ; 
 int /*<<< orphan*/  pmap_assert (int) ; 
 int /*<<< orphan*/  pmap_page_protect_options (size_t,int /*<<< orphan*/ ,unsigned int,void*) ; 
 unsigned int* pmap_phys_attributes ; 
 size_t vm_page_fictitious_addr ; 
 size_t vm_page_guard_addr ; 

unsigned int
pmap_disconnect_options(ppnum_t pa, unsigned int options, void *arg)
{
	unsigned refmod, vmrefmod = 0;

	pmap_page_protect_options(pa, 0, options, arg);		/* disconnect the page */

	pmap_assert(pa != vm_page_fictitious_addr);
	if ((pa == vm_page_guard_addr) || !IS_MANAGED_PAGE(pa) || (options & PMAP_OPTIONS_NOREFMOD))
		return 0;
	refmod = pmap_phys_attributes[pa] & (PHYS_MODIFIED | PHYS_REFERENCED);
	
	if (refmod & PHYS_MODIFIED)
	        vmrefmod |= VM_MEM_MODIFIED;
	if (refmod & PHYS_REFERENCED)
	        vmrefmod |= VM_MEM_REFERENCED;

	return vmrefmod;
}