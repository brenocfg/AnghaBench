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
typedef  int vm_size_t ;
typedef  scalar_t__ vm_address_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {struct TYPE_5__* next; } ;
typedef  TYPE_1__ tt_free_entry_t ;
typedef  int /*<<< orphan*/  tt_entry_t ;
typedef  scalar_t__ pmap_t ;
typedef  int /*<<< orphan*/  pmap_paddr_t ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 scalar_t__ KERN_RESOURCE_SHORTAGE ; 
 int /*<<< orphan*/  OSAddAtomic (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAddAtomic64 (int,int /*<<< orphan*/ *) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PMAP_PAGES_ALLOCATE_NOWAIT ; 
 int PMAP_ROOT_ALLOC_SIZE ; 
 unsigned int PMAP_TT_ALLOCATE_NOWAIT ; 
 int /*<<< orphan*/  alloc_tteroot_count ; 
 scalar_t__ free_page_size_tt_count ; 
 TYPE_1__* free_page_size_tt_list ; 
 scalar_t__ free_tt_count ; 
 TYPE_1__* free_tt_list ; 
 scalar_t__ free_tt_max ; 
 scalar_t__ free_two_page_size_tt_count ; 
 TYPE_1__* free_two_page_size_tt_list ; 
 int /*<<< orphan*/  inuse_kernel_tteroot_count ; 
 int /*<<< orphan*/  inuse_user_tteroot_count ; 
 scalar_t__ kernel_pmap ; 
 int phystokv (int /*<<< orphan*/ ) ; 
 scalar_t__ pmap_pages_alloc (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_simple_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmap_simple_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmap_tt_ledger_credit (scalar_t__,int) ; 
 int /*<<< orphan*/  pmaps_lock ; 

__attribute__((used)) static tt_entry_t *
pmap_tt1_allocate(
	pmap_t		pmap,
	vm_size_t	size,
	unsigned	option)
{
	tt_entry_t		*tt1;
	tt_free_entry_t	*tt1_free;
	pmap_paddr_t	pa;
	vm_address_t	va;
	vm_address_t	va_end;
	kern_return_t	ret;

	pmap_simple_lock(&pmaps_lock);
	if ((size == PAGE_SIZE) && (free_page_size_tt_count != 0)) {
			free_page_size_tt_count--;
			tt1 = (tt_entry_t *)free_page_size_tt_list;
			free_page_size_tt_list = ((tt_free_entry_t *)tt1)->next;
			pmap_simple_unlock(&pmaps_lock);
			pmap_tt_ledger_credit(pmap, size);
			return (tt_entry_t *)tt1;
	};
	if ((size == 2*PAGE_SIZE) && (free_two_page_size_tt_count != 0)) {
			free_two_page_size_tt_count--;
			tt1 = (tt_entry_t *)free_two_page_size_tt_list;
			free_two_page_size_tt_list = ((tt_free_entry_t *)tt1)->next;
			pmap_simple_unlock(&pmaps_lock);
			pmap_tt_ledger_credit(pmap, size);
			return (tt_entry_t *)tt1;
	};
	if (free_tt_count != 0) {
			free_tt_count--;
			tt1 = (tt_entry_t *)free_tt_list;
			free_tt_list = (tt_free_entry_t *)((tt_free_entry_t *)tt1)->next;
			pmap_simple_unlock(&pmaps_lock);
			pmap_tt_ledger_credit(pmap, size);
			return (tt_entry_t *)tt1;
	}

	pmap_simple_unlock(&pmaps_lock);

	ret = pmap_pages_alloc(&pa, (unsigned)((size < PAGE_SIZE)? PAGE_SIZE : size), ((option & PMAP_TT_ALLOCATE_NOWAIT)? PMAP_PAGES_ALLOCATE_NOWAIT : 0));

	if(ret ==  KERN_RESOURCE_SHORTAGE)
		return (tt_entry_t *)0;


	if (size < PAGE_SIZE) {
		pmap_simple_lock(&pmaps_lock);

		for (va_end = phystokv(pa) + PAGE_SIZE, va = phystokv(pa) + size; va < va_end; va = va+size) {
			tt1_free = (tt_free_entry_t *)va;
			tt1_free->next = free_tt_list;
			free_tt_list = tt1_free;
			free_tt_count++;
		}
		if (free_tt_count > free_tt_max)
			free_tt_max = free_tt_count;

		pmap_simple_unlock(&pmaps_lock);
	}

	/* Always report root allocations in units of PMAP_ROOT_ALLOC_SIZE, which can be obtained by sysctl arm_pt_root_size.
	 * Depending on the device, this can vary between 512b and 16K. */
	OSAddAtomic((uint32_t)(size / PMAP_ROOT_ALLOC_SIZE), (pmap == kernel_pmap ? &inuse_kernel_tteroot_count : &inuse_user_tteroot_count));
	OSAddAtomic64(size / PMAP_ROOT_ALLOC_SIZE, &alloc_tteroot_count);
	pmap_tt_ledger_credit(pmap, size);

	return (tt_entry_t *) phystokv(pa);
}