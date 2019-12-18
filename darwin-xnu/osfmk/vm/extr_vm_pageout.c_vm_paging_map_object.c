#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  TYPE_1__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_object_t ;
typedef  scalar_t__ vm_object_offset_t ;
typedef  int vm_map_size_t ;
typedef  scalar_t__ vm_map_offset_t ;
typedef  int pmap_paddr_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  event_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_7__ {int vmp_busy; scalar_t__ vmp_pmapped; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ KERN_MEMORY_ERROR ; 
 scalar_t__ KERN_NOT_SUPPORTED ; 
 scalar_t__ KERN_SUCCESS ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int PAGE_SIZE_64 ; 
 scalar_t__ PHYSMAP_PTOV (int) ; 
 int /*<<< orphan*/  PMAP_ENTER (int /*<<< orphan*/ ,scalar_t__,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  THREAD_CONTINUE_NULL ; 
 int /*<<< orphan*/  THREAD_UNINT ; 
 scalar_t__ THREAD_WAITING ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  VM_FLAGS_ANYWHERE ; 
 int /*<<< orphan*/  VM_INHERIT_NONE ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_NONE ; 
 int /*<<< orphan*/  VM_MAP_KERNEL_FLAGS_NONE ; 
 int /*<<< orphan*/  VM_MAP_PAGE_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_MAP_REMOVE_NO_FLAGS ; 
 scalar_t__ VM_PAGE_GET_PHYS_PAGE (TYPE_1__*) ; 
 TYPE_1__* VM_PAGE_NULL ; 
 int VM_PAGING_NUM_PAGES ; 
 int /*<<< orphan*/  VM_PROT_ALL ; 
 int /*<<< orphan*/  VM_PROT_NONE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ assert_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kasan_notify_address (scalar_t__,int) ; 
 int /*<<< orphan*/  kernel_map ; 
 int /*<<< orphan*/  kernel_pmap ; 
 scalar_t__ phystokv (int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  simple_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ thread_block (int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_enter (int /*<<< orphan*/ ,scalar_t__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_remove (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int vm_map_round_page (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_deallocate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_reference_locked (int /*<<< orphan*/ ) ; 
 scalar_t__ vm_object_trunc_page (scalar_t__) ; 
 int /*<<< orphan*/  vm_object_unlock (int /*<<< orphan*/ ) ; 
 TYPE_1__* vm_page_lookup (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ vm_paging_base_address ; 
 int /*<<< orphan*/  vm_paging_lock ; 
 int vm_paging_max_index ; 
 int /*<<< orphan*/  vm_paging_no_kernel_page ; 
 int /*<<< orphan*/  vm_paging_objects_mapped ; 
 int /*<<< orphan*/  vm_paging_objects_mapped_slow ; 
 scalar_t__* vm_paging_page_inuse ; 
 int /*<<< orphan*/  vm_paging_page_waiter ; 
 int /*<<< orphan*/  vm_paging_page_waiter_total ; 
 int /*<<< orphan*/  vm_paging_pages_mapped ; 
 unsigned long vm_paging_pages_mapped_slow ; 

kern_return_t
vm_paging_map_object(
	vm_page_t		page,
	vm_object_t		object,
	vm_object_offset_t	offset,
	vm_prot_t		protection,
	boolean_t		can_unlock_object,
	vm_map_size_t		*size,		/* IN/OUT */
	vm_map_offset_t		*address,	/* OUT */
	boolean_t		*need_unmap)	/* OUT */
{
	kern_return_t		kr;
	vm_map_offset_t		page_map_offset;
	vm_map_size_t		map_size;
	vm_object_offset_t	object_offset;
	int			i;

	if (page != VM_PAGE_NULL && *size == PAGE_SIZE) {
		/* use permanent 1-to-1 kernel mapping of physical memory ? */
#if __x86_64__
		*address = (vm_map_offset_t)
			PHYSMAP_PTOV((pmap_paddr_t)VM_PAGE_GET_PHYS_PAGE(page) <<
				     PAGE_SHIFT);
		*need_unmap = FALSE;
		return KERN_SUCCESS;
#elif __arm__ || __arm64__
		*address = (vm_map_offset_t)
			phystokv((pmap_paddr_t)VM_PAGE_GET_PHYS_PAGE(page) << PAGE_SHIFT);
		*need_unmap = FALSE;
		return KERN_SUCCESS;
#else
#warn "vm_paging_map_object: no 1-to-1 kernel mapping of physical memory..."
#endif

		assert(page->vmp_busy);
		/*
		 * Use one of the pre-allocated kernel virtual addresses
		 * and just enter the VM page in the kernel address space
		 * at that virtual address.
		 */
		simple_lock(&vm_paging_lock);

		/*
		 * Try and find an available kernel virtual address
		 * from our pre-allocated pool.
		 */
		page_map_offset = 0;
		for (;;) {
			for (i = 0; i < VM_PAGING_NUM_PAGES; i++) {
				if (vm_paging_page_inuse[i] == FALSE) {
					page_map_offset =
						vm_paging_base_address +
						(i * PAGE_SIZE);
					break;
				}
			}
			if (page_map_offset != 0) {
				/* found a space to map our page ! */
				break;
			}

			if (can_unlock_object) {
				/*
				 * If we can afford to unlock the VM object,
				 * let's take the slow path now...
				 */
				break;
			}
			/*
			 * We can't afford to unlock the VM object, so
			 * let's wait for a space to become available...
			 */
			vm_paging_page_waiter_total++;
			vm_paging_page_waiter++;
			kr = assert_wait((event_t)&vm_paging_page_waiter, THREAD_UNINT);
			if (kr == THREAD_WAITING) {
				simple_unlock(&vm_paging_lock);
				kr = thread_block(THREAD_CONTINUE_NULL);
				simple_lock(&vm_paging_lock);
			}
			vm_paging_page_waiter--;
			/* ... and try again */
		}

		if (page_map_offset != 0) {
			/*
			 * We found a kernel virtual address;
			 * map the physical page to that virtual address.
			 */
			if (i > vm_paging_max_index) {
				vm_paging_max_index = i;
			}
			vm_paging_page_inuse[i] = TRUE;
			simple_unlock(&vm_paging_lock);

			page->vmp_pmapped = TRUE;

			/*
			 * Keep the VM object locked over the PMAP_ENTER
			 * and the actual use of the page by the kernel,
			 * or this pmap mapping might get undone by a
			 * vm_object_pmap_protect() call...
			 */
			PMAP_ENTER(kernel_pmap,
				   page_map_offset,
				   page,
				   protection,
				   VM_PROT_NONE,
				   0,
				   TRUE,
				   kr);
			assert(kr == KERN_SUCCESS);
			vm_paging_objects_mapped++;
			vm_paging_pages_mapped++;
			*address = page_map_offset;
			*need_unmap = TRUE;

#if KASAN
			kasan_notify_address(page_map_offset, PAGE_SIZE);
#endif

			/* all done and mapped, ready to use ! */
			return KERN_SUCCESS;
		}

		/*
		 * We ran out of pre-allocated kernel virtual
		 * addresses.  Just map the page in the kernel
		 * the slow and regular way.
		 */
		vm_paging_no_kernel_page++;
		simple_unlock(&vm_paging_lock);
	}

	if (! can_unlock_object) {
		*address = 0;
		*size = 0;
		*need_unmap = FALSE;
		return KERN_NOT_SUPPORTED;
	}

	object_offset = vm_object_trunc_page(offset);
	map_size = vm_map_round_page(*size,
				     VM_MAP_PAGE_MASK(kernel_map));

	/*
	 * Try and map the required range of the object
	 * in the kernel_map
	 */

	vm_object_reference_locked(object);	/* for the map entry */
	vm_object_unlock(object);

	kr = vm_map_enter(kernel_map,
			  address,
			  map_size,
			  0,
			  VM_FLAGS_ANYWHERE,
			  VM_MAP_KERNEL_FLAGS_NONE,
			  VM_KERN_MEMORY_NONE,
			  object,
			  object_offset,
			  FALSE,
			  protection,
			  VM_PROT_ALL,
			  VM_INHERIT_NONE);
	if (kr != KERN_SUCCESS) {
		*address = 0;
		*size = 0;
		*need_unmap = FALSE;
		vm_object_deallocate(object);	/* for the map entry */
		vm_object_lock(object);
		return kr;
	}

	*size = map_size;

	/*
	 * Enter the mapped pages in the page table now.
	 */
	vm_object_lock(object);
	/*
	 * VM object must be kept locked from before PMAP_ENTER()
	 * until after the kernel is done accessing the page(s).
	 * Otherwise, the pmap mappings in the kernel could be
	 * undone by a call to vm_object_pmap_protect().
	 */

	for (page_map_offset = 0;
	     map_size != 0;
	     map_size -= PAGE_SIZE_64, page_map_offset += PAGE_SIZE_64) {

		page = vm_page_lookup(object, offset + page_map_offset);
		if (page == VM_PAGE_NULL) {
			printf("vm_paging_map_object: no page !?");
			vm_object_unlock(object);
			kr = vm_map_remove(kernel_map, *address, *size,
					   VM_MAP_REMOVE_NO_FLAGS);
			assert(kr == KERN_SUCCESS);
			*address = 0;
			*size = 0;
			*need_unmap = FALSE;
			vm_object_lock(object);
			return KERN_MEMORY_ERROR;
		}
		page->vmp_pmapped = TRUE;

		//assert(pmap_verify_free(VM_PAGE_GET_PHYS_PAGE(page)));
		PMAP_ENTER(kernel_pmap,
			   *address + page_map_offset,
			   page,
			   protection,
			   VM_PROT_NONE,
			   0,
			   TRUE,
			   kr);
		assert(kr == KERN_SUCCESS);
#if KASAN
		kasan_notify_address(*address + page_map_offset, PAGE_SIZE);
#endif
	}

	vm_paging_objects_mapped_slow++;
	vm_paging_pages_mapped_slow += (unsigned long) (map_size / PAGE_SIZE_64);

	*need_unmap = TRUE;

	return KERN_SUCCESS;
}