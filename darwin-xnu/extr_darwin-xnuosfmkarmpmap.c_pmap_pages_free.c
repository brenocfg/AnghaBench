#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_page_t ;
typedef  scalar_t__ pmap_paddr_t ;
struct TYPE_3__ {struct TYPE_3__* next; } ;
typedef  TYPE_1__ page_free_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  OSAddAtomic (unsigned int,int /*<<< orphan*/ *) ; 
 unsigned int PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ VM_PAGE_NULL ; 
 int VM_PAGE_WIRED (scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ gPhysBase ; 
 int /*<<< orphan*/  inuse_pmap_pages_count ; 
 scalar_t__ phystokv (scalar_t__) ; 
 int /*<<< orphan*/  pmap_object ; 
 int /*<<< orphan*/  pmap_pages_lock ; 
 TYPE_1__* pmap_pages_reclaim_list ; 
 scalar_t__ pmap_pages_request_count ; 
 int /*<<< orphan*/  pmap_simple_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmap_simple_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_object_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_free (scalar_t__) ; 
 int /*<<< orphan*/  vm_page_lock_queues () ; 
 scalar_t__ vm_page_lookup (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vm_page_unlock_queues () ; 

__attribute__((used)) static void
pmap_pages_free(
	pmap_paddr_t	pa,
	unsigned	size)
{
	pmap_simple_lock(&pmap_pages_lock);

	if (pmap_pages_request_count != 0) {
		page_free_entry_t	*page_entry;

		pmap_pages_request_count--;
		page_entry = (page_free_entry_t *)phystokv(pa);
		page_entry->next = pmap_pages_reclaim_list;
		pmap_pages_reclaim_list = page_entry;
		pmap_simple_unlock(&pmap_pages_lock);

		return;
	}

	pmap_simple_unlock(&pmap_pages_lock);

	vm_page_t       m;
	pmap_paddr_t	pa_max;

	OSAddAtomic(-(size>>PAGE_SHIFT), &inuse_pmap_pages_count);

	for (pa_max = pa + size; pa < pa_max; pa = pa + PAGE_SIZE) {
		vm_object_lock(pmap_object);
		m = vm_page_lookup(pmap_object, (pa - gPhysBase));
		assert(m != VM_PAGE_NULL);
		assert(VM_PAGE_WIRED(m));
		vm_page_lock_queues();
		vm_page_free(m);
		vm_page_unlock_queues();
		vm_object_unlock(pmap_object);
	}
}