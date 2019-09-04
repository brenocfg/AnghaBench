#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  TYPE_1__* vm_object_t ;
typedef  TYPE_2__* vm_map_t ;
typedef  scalar_t__ vm_map_offset_t ;
typedef  TYPE_3__* vm_map_entry_t ;
typedef  scalar_t__ vm_fault_return_t ;
typedef  scalar_t__ upl_size_t ;
struct vm_object_fault_info {int /*<<< orphan*/  user_tag; scalar_t__ cluster_size; int /*<<< orphan*/  stealth; int /*<<< orphan*/  no_cache; scalar_t__ hi_offset; scalar_t__ lo_offset; int /*<<< orphan*/  pmap_options; int /*<<< orphan*/  behavior; int /*<<< orphan*/  interruptible; } ;
typedef  scalar_t__ pmap_t ;
typedef  int boolean_t ;
struct TYPE_20__ {scalar_t__ vme_end; scalar_t__ vme_start; scalar_t__ zero_wired_pages; int /*<<< orphan*/  no_cache; int /*<<< orphan*/  use_pmap; scalar_t__ is_sub_map; scalar_t__ iokit_acct; int /*<<< orphan*/  behavior; } ;
struct TYPE_19__ {int /*<<< orphan*/  no_zero_fill; } ;
struct TYPE_18__ {int /*<<< orphan*/  alive; scalar_t__ phys_contiguous; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PAGE_WAKEUP_DONE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_OPTIONS_ALT_ACCT ; 
 int /*<<< orphan*/  THREAD_UNINT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VME_ALIAS (TYPE_3__*) ; 
 TYPE_1__* VME_OBJECT (TYPE_3__*) ; 
 scalar_t__ VME_OFFSET (TYPE_3__*) ; 
 scalar_t__ VM_FAULT_MEMORY_ERROR ; 
 scalar_t__ VM_FAULT_RETRY ; 
 scalar_t__ VM_FAULT_SUCCESS ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_NONE ; 
 TYPE_1__* VM_OBJECT_NULL ; 
 int /*<<< orphan*/  VM_PAGE_FREE (int /*<<< orphan*/ ) ; 
 scalar_t__ VM_PAGE_GET_PHYS_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_PAGE_NULL ; 
 TYPE_1__* VM_PAGE_OBJECT (int /*<<< orphan*/ ) ; 
 scalar_t__ VM_PAGE_WIRED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_PROT_NONE ; 
 int /*<<< orphan*/  XPR (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XPR_VM_FAULT ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* kernel_object ; 
 scalar_t__ os_sub_overflow (scalar_t__,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pmap_change_wiring (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pmap_disconnect (scalar_t__) ; 
 int /*<<< orphan*/  pmap_pageable (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_zero_page (scalar_t__) ; 
 int /*<<< orphan*/  ptoa_64 (unsigned int) ; 
 int /*<<< orphan*/  vm_fault (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  vm_fault_cleanup (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_fault_page (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,struct vm_object_fault_info*) ; 
 int /*<<< orphan*/  vm_object_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_object_paging_begin (TYPE_1__*) ; 
 scalar_t__ vm_page_fictitious_addr ; 
 scalar_t__ vm_page_guard_addr ; 
 int /*<<< orphan*/  vm_page_lockspin_queues () ; 
 int /*<<< orphan*/  vm_page_unlock_queues () ; 
 int /*<<< orphan*/  vm_page_unwire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_tag_update_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
vm_fault_unwire(
	vm_map_t	map,
	vm_map_entry_t	entry,
	boolean_t	deallocate,
	pmap_t		pmap,
	vm_map_offset_t	pmap_addr)
{
	vm_map_offset_t	va;
	vm_map_offset_t	end_addr = entry->vme_end;
	vm_object_t		object;
	struct vm_object_fault_info fault_info = {};
	unsigned int    unwired_pages;

	object = (entry->is_sub_map) ? VM_OBJECT_NULL : VME_OBJECT(entry);

	/*
	 * If it's marked phys_contiguous, then vm_fault_wire() didn't actually
	 * do anything since such memory is wired by default.  So we don't have
	 * anything to undo here.
	 */

	if (object != VM_OBJECT_NULL && object->phys_contiguous)
		return;

	fault_info.interruptible = THREAD_UNINT;
	fault_info.behavior = entry->behavior;
	fault_info.user_tag = VME_ALIAS(entry);
	if (entry->iokit_acct ||
	    (!entry->is_sub_map && !entry->use_pmap)) {
		fault_info.pmap_options |= PMAP_OPTIONS_ALT_ACCT;
	}
	fault_info.lo_offset = VME_OFFSET(entry);
	fault_info.hi_offset = (entry->vme_end - entry->vme_start) + VME_OFFSET(entry);
	fault_info.no_cache = entry->no_cache;
	fault_info.stealth = TRUE;

	unwired_pages = 0;

	/*
	 *	Since the pages are wired down, we must be able to
	 *	get their mappings from the physical map system.
	 */

	for (va = entry->vme_start; va < end_addr; va += PAGE_SIZE) {

		if (object == VM_OBJECT_NULL) {
			if (pmap) {
				pmap_change_wiring(pmap,
						   pmap_addr + (va - entry->vme_start), FALSE);
			}
			(void) vm_fault(map, va, VM_PROT_NONE,
					TRUE, VM_KERN_MEMORY_NONE, THREAD_UNINT, pmap, pmap_addr);
		} else {
		 	vm_prot_t	prot;
			vm_page_t	result_page;
			vm_page_t	top_page;
			vm_object_t	result_object;
			vm_fault_return_t result;

			/* cap cluster size at maximum UPL size */
			upl_size_t cluster_size;
			if (os_sub_overflow(end_addr, va, &cluster_size)) {
				cluster_size = 0 - (upl_size_t)PAGE_SIZE;
			}
			fault_info.cluster_size = cluster_size;

			do {
				prot = VM_PROT_NONE;

				vm_object_lock(object);
				vm_object_paging_begin(object);
				XPR(XPR_VM_FAULT,
					"vm_fault_unwire -> vm_fault_page\n",
					0,0,0,0,0);
				result_page = VM_PAGE_NULL;
			 	result = vm_fault_page(
					object,
					(VME_OFFSET(entry) +
					 (va - entry->vme_start)),
					VM_PROT_NONE, TRUE,
					FALSE, /* page not looked up */
					&prot, &result_page, &top_page,
					(int *)0,
					NULL, map->no_zero_fill,
					FALSE, &fault_info);
			} while (result == VM_FAULT_RETRY);

			/*
			 * If this was a mapping to a file on a device that has been forcibly
			 * unmounted, then we won't get a page back from vm_fault_page().  Just
			 * move on to the next one in case the remaining pages are mapped from
			 * different objects.  During a forced unmount, the object is terminated
			 * so the alive flag will be false if this happens.  A forced unmount will
			 * will occur when an external disk is unplugged before the user does an
			 * eject, so we don't want to panic in that situation.
			 */

			if (result == VM_FAULT_MEMORY_ERROR && !object->alive)
				continue;

			if (result == VM_FAULT_MEMORY_ERROR &&
			    object == kernel_object) {
				/*
				 * This must have been allocated with
				 * KMA_KOBJECT and KMA_VAONLY and there's
				 * no physical page at this offset.
				 * We're done (no page to free).
				 */
				assert(deallocate);
				continue;
			}

			if (result != VM_FAULT_SUCCESS)
				panic("vm_fault_unwire: failure");

			result_object = VM_PAGE_OBJECT(result_page);

			if (deallocate) {
				assert(VM_PAGE_GET_PHYS_PAGE(result_page) !=
				       vm_page_fictitious_addr);
				pmap_disconnect(VM_PAGE_GET_PHYS_PAGE(result_page));
				if (VM_PAGE_WIRED(result_page)) {
					unwired_pages++;
				}
				VM_PAGE_FREE(result_page);
			} else {
				if ((pmap) && (VM_PAGE_GET_PHYS_PAGE(result_page) != vm_page_guard_addr))
					pmap_change_wiring(pmap,
					    pmap_addr + (va - entry->vme_start), FALSE);


				if (VM_PAGE_WIRED(result_page)) {
					vm_page_lockspin_queues();
					vm_page_unwire(result_page, TRUE);
					vm_page_unlock_queues();
					unwired_pages++;
				}
				if(entry->zero_wired_pages) {
					pmap_zero_page(VM_PAGE_GET_PHYS_PAGE(result_page));
					entry->zero_wired_pages = FALSE;
				}

				PAGE_WAKEUP_DONE(result_page);
			}
			vm_fault_cleanup(result_object, top_page);
		}
	}

	/*
	 *	Inform the physical mapping system that the range
	 *	of addresses may fault, so that page tables and
	 *	such may be unwired themselves.
	 */

	pmap_pageable(pmap, pmap_addr,
		pmap_addr + (end_addr - entry->vme_start), TRUE);

	if (kernel_object == object) {
	    vm_tag_update_size(fault_info.user_tag, -ptoa_64(unwired_pages));
	}
}