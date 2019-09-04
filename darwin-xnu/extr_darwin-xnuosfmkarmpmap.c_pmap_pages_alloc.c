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
typedef  scalar_t__ vm_page_t ;
typedef  int /*<<< orphan*/  vm_object_offset_t ;
typedef  scalar_t__ pmap_paddr_t ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 scalar_t__ KERN_RESOURCE_SHORTAGE ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ NEXT_PAGE (scalar_t__) ; 
 scalar_t__* NEXT_PAGE_PTR (scalar_t__) ; 
 int /*<<< orphan*/  OSAddAtomic (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAddAtomic64 (unsigned int,int /*<<< orphan*/ *) ; 
 unsigned int PAGE_SHIFT ; 
 unsigned int PAGE_SIZE ; 
 unsigned int PMAP_PAGES_ALLOCATE_NOWAIT ; 
 unsigned int PMAP_PAGES_RECLAIM_NOWAIT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_PTE ; 
 int /*<<< orphan*/  VM_PAGE_GET_PHYS_PAGE (scalar_t__) ; 
 scalar_t__ VM_PAGE_NULL ; 
 int /*<<< orphan*/  VM_PAGE_WAIT () ; 
 int /*<<< orphan*/  alloc_pmap_pages_count ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ cpm_allocate (unsigned int,scalar_t__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gPhysBase ; 
 int /*<<< orphan*/  inuse_pmap_pages_count ; 
 int /*<<< orphan*/  pmap_object ; 
 scalar_t__ pmap_pages_reclaim () ; 
 scalar_t__ ptoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ vm_page_grab () ; 
 int /*<<< orphan*/  vm_page_insert_wired (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_lock_queues () ; 
 int /*<<< orphan*/  vm_page_unlock_queues () ; 
 int /*<<< orphan*/  vm_page_wire (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static kern_return_t
pmap_pages_alloc(
	pmap_paddr_t	*pa,
	unsigned		size,
	unsigned		option)
{
	vm_page_t       m = VM_PAGE_NULL, m_prev;

	if(option & PMAP_PAGES_RECLAIM_NOWAIT) {
		assert(size == PAGE_SIZE);
		*pa = pmap_pages_reclaim();
		return KERN_SUCCESS;
	}
	if (size == PAGE_SIZE) {
		while ((m = vm_page_grab()) == VM_PAGE_NULL) {
			if(option & PMAP_PAGES_ALLOCATE_NOWAIT) {
				return KERN_RESOURCE_SHORTAGE;
			}

			VM_PAGE_WAIT();
		}
		vm_page_lock_queues();
		vm_page_wire(m, VM_KERN_MEMORY_PTE, TRUE);
		vm_page_unlock_queues();
	}
	if (size == 2*PAGE_SIZE) {
		while (cpm_allocate(size, &m, 0, 1, TRUE, 0) != KERN_SUCCESS) {
			if(option & PMAP_PAGES_ALLOCATE_NOWAIT)
				return KERN_RESOURCE_SHORTAGE;

			VM_PAGE_WAIT();
		}
	}

	*pa = (pmap_paddr_t)ptoa(VM_PAGE_GET_PHYS_PAGE(m));

	vm_object_lock(pmap_object);
	while (m != VM_PAGE_NULL) {
		vm_page_insert_wired(m, pmap_object, (vm_object_offset_t) ((ptoa(VM_PAGE_GET_PHYS_PAGE(m))) - gPhysBase), VM_KERN_MEMORY_PTE);
		m_prev = m;
		m = NEXT_PAGE(m_prev);
		*(NEXT_PAGE_PTR(m_prev)) = VM_PAGE_NULL;
	}
	vm_object_unlock(pmap_object);

	OSAddAtomic(size>>PAGE_SHIFT, &inuse_pmap_pages_count);
	OSAddAtomic64(size>>PAGE_SHIFT, &alloc_pmap_pages_count);

	return KERN_SUCCESS;
}