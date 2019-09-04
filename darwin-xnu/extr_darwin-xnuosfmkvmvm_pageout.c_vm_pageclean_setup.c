#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_object_t ;
typedef  int /*<<< orphan*/  vm_object_offset_t ;
struct TYPE_12__ {int vmp_fictitious; void* vmp_busy; int /*<<< orphan*/  vmp_wanted; void* vmp_free_when_done; void* vmp_private; void* vmp_precious; void* vmp_cleaning; int /*<<< orphan*/  vmp_offset; } ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  SET_PAGE_DIRTY (TYPE_1__*,void*) ; 
 void* TRUE ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_NONE ; 
 scalar_t__ VM_PAGE_GET_PHYS_PAGE (TYPE_1__*) ; 
 int /*<<< orphan*/  VM_PAGE_OBJECT (TYPE_1__*) ; 
 int /*<<< orphan*/  VM_PAGE_SET_PHYS_PAGE (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  XPR (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XPR_VM_PAGEOUT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pmap_clear_modify (scalar_t__) ; 
 scalar_t__ vm_page_fictitious_addr ; 
 int /*<<< orphan*/  vm_page_insert_wired (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_lockspin_queues () ; 
 int /*<<< orphan*/  vm_page_unlock_queues () ; 
 int /*<<< orphan*/  vm_page_wire (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void
vm_pageclean_setup(
	vm_page_t		m,
	vm_page_t		new_m,
	vm_object_t		new_object,
	vm_object_offset_t	new_offset)
{
	assert(!m->vmp_busy);
#if 0
	assert(!m->vmp_cleaning);
#endif

	XPR(XPR_VM_PAGEOUT,
	    "vm_pageclean_setup, obj 0x%X off 0x%X page 0x%X new 0x%X new_off 0x%X\n",
		VM_PAGE_OBJECT(m), m->vmp_offset, m,
		new_m, new_offset);

	pmap_clear_modify(VM_PAGE_GET_PHYS_PAGE(m));

	/*
	 * Mark original page as cleaning in place.
	 */
	m->vmp_cleaning = TRUE;
	SET_PAGE_DIRTY(m, FALSE);
	m->vmp_precious = FALSE;

	/*
	 * Convert the fictitious page to a private shadow of
	 * the real page.
	 */
	assert(new_m->vmp_fictitious);
	assert(VM_PAGE_GET_PHYS_PAGE(new_m) == vm_page_fictitious_addr);
	new_m->vmp_fictitious = FALSE;
	new_m->vmp_private = TRUE;
	new_m->vmp_free_when_done = TRUE;
	VM_PAGE_SET_PHYS_PAGE(new_m, VM_PAGE_GET_PHYS_PAGE(m));

	vm_page_lockspin_queues();
	vm_page_wire(new_m, VM_KERN_MEMORY_NONE, TRUE);
	vm_page_unlock_queues();

	vm_page_insert_wired(new_m, new_object, new_offset, VM_KERN_MEMORY_NONE);
	assert(!new_m->vmp_wanted);
	new_m->vmp_busy = FALSE;
}