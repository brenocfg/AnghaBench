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
typedef  unsigned int vm_size_t ;
typedef  scalar_t__ vm_page_t ;
typedef  int /*<<< orphan*/  ppnum_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  event_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_NO_SPACE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  VM_CHECK_MEMORYSTATUS ; 
 scalar_t__ VM_PAGE_NULL ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_wakeup (int /*<<< orphan*/ ) ; 
 scalar_t__ vm_page_find_contiguous (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ vm_page_free_count ; 
 scalar_t__ vm_page_free_min ; 
 int /*<<< orphan*/  vm_page_free_wanted ; 
 int /*<<< orphan*/  vm_page_verify_contiguous (scalar_t__,unsigned int) ; 

kern_return_t
cpm_allocate(
	vm_size_t	size,
	vm_page_t	*list,
	ppnum_t		max_pnum,
	ppnum_t		pnum_mask,
	boolean_t	wire,
	int		flags)
{
	vm_page_t		pages;
	unsigned int		npages;

	if (size % PAGE_SIZE != 0)
		return KERN_INVALID_ARGUMENT;

	npages = (unsigned int) (size / PAGE_SIZE);
	if (npages != size / PAGE_SIZE) {
		/* 32-bit overflow */
		return KERN_INVALID_ARGUMENT;
	}

	/*
	 *	Obtain a pointer to a subset of the free
	 *	list large enough to satisfy the request;
	 *	the region will be physically contiguous.
	 */
	pages = vm_page_find_contiguous(npages, max_pnum, pnum_mask, wire, flags);

	if (pages == VM_PAGE_NULL)
		return KERN_NO_SPACE;
	/*
	 * determine need for wakeups
	 */
	if (vm_page_free_count < vm_page_free_min)
	        thread_wakeup((event_t) &vm_page_free_wanted);
		
	VM_CHECK_MEMORYSTATUS;
	
	/*
	 *	The CPM pages should now be available and
	 *	ordered by ascending physical address.
	 */
	assert(vm_page_verify_contiguous(pages, npages));

	*list = pages;
	return KERN_SUCCESS;
}