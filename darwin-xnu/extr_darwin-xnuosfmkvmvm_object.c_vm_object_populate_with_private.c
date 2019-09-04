#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_size_t ;
typedef  TYPE_1__* vm_page_t ;
typedef  TYPE_2__* vm_object_t ;
typedef  int vm_object_offset_t ;
typedef  scalar_t__ ppnum_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_16__ {int vo_shadow_offset; scalar_t__ vo_size; scalar_t__ paging_offset; int /*<<< orphan*/  phys_contiguous; int /*<<< orphan*/  private; } ;
struct TYPE_15__ {void* vmp_busy; void* vmp_unusual; void* vmp_fictitious; void* vmp_private; scalar_t__ vmp_pmapped; } ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 void* TRUE ; 
 scalar_t__ VM_PAGE_GET_PHYS_PAGE (TYPE_1__*) ; 
 TYPE_1__* VM_PAGE_NULL ; 
 int /*<<< orphan*/  VM_PAGE_SET_PHYS_PAGE (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  panic (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  pmap_disconnect (scalar_t__) ; 
 int trunc_page_64 (int) ; 
 int /*<<< orphan*/  vm_object_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_object_unlock (TYPE_2__*) ; 
 TYPE_1__* vm_page_grab_fictitious () ; 
 scalar_t__ vm_page_guard_addr ; 
 int /*<<< orphan*/  vm_page_insert (TYPE_1__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  vm_page_lockspin_queues () ; 
 TYPE_1__* vm_page_lookup (TYPE_2__*,int) ; 
 int /*<<< orphan*/  vm_page_more_fictitious () ; 
 int /*<<< orphan*/  vm_page_unlock_queues () ; 

kern_return_t
vm_object_populate_with_private(
		vm_object_t		object,
		vm_object_offset_t	offset,
		ppnum_t			phys_page,
		vm_size_t		size)
{
	ppnum_t			base_page;
	vm_object_offset_t	base_offset;


	if (!object->private)
		return KERN_FAILURE;

	base_page = phys_page;

	vm_object_lock(object);

	if (!object->phys_contiguous) {
		vm_page_t	m;

		if ((base_offset = trunc_page_64(offset)) != offset) {
			vm_object_unlock(object);
			return KERN_FAILURE;
		}
		base_offset += object->paging_offset;

		while (size) {
			m = vm_page_lookup(object, base_offset);

			if (m != VM_PAGE_NULL) {
				if (m->vmp_fictitious) {
					if (VM_PAGE_GET_PHYS_PAGE(m) != vm_page_guard_addr) {

						vm_page_lockspin_queues();
						m->vmp_private = TRUE;
						vm_page_unlock_queues();

						m->vmp_fictitious = FALSE;
						VM_PAGE_SET_PHYS_PAGE(m, base_page);
					}
				} else if (VM_PAGE_GET_PHYS_PAGE(m) != base_page) {

				        if ( !m->vmp_private) {
						/*
						 * we'd leak a real page... that can't be right
						 */
						panic("vm_object_populate_with_private - %p not private", m);
					}
					if (m->vmp_pmapped) {
					        /*
						 * pmap call to clear old mapping
						 */
					        pmap_disconnect(VM_PAGE_GET_PHYS_PAGE(m));
					}
					VM_PAGE_SET_PHYS_PAGE(m, base_page);
				}

			} else {
				while ((m = vm_page_grab_fictitious()) == VM_PAGE_NULL)
                			vm_page_more_fictitious();	

				/*
				 * private normally requires lock_queues but since we
				 * are initializing the page, its not necessary here
				 */
				m->vmp_private = TRUE;
				m->vmp_fictitious = FALSE;
				VM_PAGE_SET_PHYS_PAGE(m, base_page);
				m->vmp_unusual = TRUE;
				m->vmp_busy = FALSE;

	    			vm_page_insert(m, object, base_offset);
			}
			base_page++;									/* Go to the next physical page */
			base_offset += PAGE_SIZE;
			size -= PAGE_SIZE;
		}
	} else {
		/* NOTE: we should check the original settings here */
		/* if we have a size > zero a pmap call should be made */
		/* to disable the range */	

		/* pmap_? */
		
		/* shadows on contiguous memory are not allowed */
		/* we therefore can use the offset field */
		object->vo_shadow_offset = (vm_object_offset_t)phys_page << PAGE_SHIFT;
		object->vo_size = size;
	}
	vm_object_unlock(object);

	return KERN_SUCCESS;
}