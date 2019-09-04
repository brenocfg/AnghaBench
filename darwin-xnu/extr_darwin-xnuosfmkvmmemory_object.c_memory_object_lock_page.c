#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_prot_t ;
typedef  TYPE_1__* vm_page_t ;
typedef  int /*<<< orphan*/  memory_object_return_t ;
typedef  int /*<<< orphan*/  memory_object_lock_result_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_9__ {int /*<<< orphan*/  vmp_fictitious; scalar_t__ vmp_error; scalar_t__ vmp_restart; scalar_t__ vmp_absent; scalar_t__ vmp_laundry; scalar_t__ vmp_cleaning; scalar_t__ vmp_busy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MEMORY_OBJECT_LOCK_RESULT_DONE ; 
 int /*<<< orphan*/  MEMORY_OBJECT_LOCK_RESULT_MUST_BLOCK ; 
 int /*<<< orphan*/  MEMORY_OBJECT_LOCK_RESULT_MUST_FREE ; 
 int /*<<< orphan*/  MEMORY_OBJECT_LOCK_RESULT_MUST_RETURN ; 
 int /*<<< orphan*/  SET_PAGE_DIRTY (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int VM_MEM_MODIFIED ; 
 int /*<<< orphan*/  VM_PAGE_GET_PHYS_PAGE (TYPE_1__*) ; 
 scalar_t__ VM_PAGE_WIRED (TYPE_1__*) ; 
 int VM_PROT_ALL ; 
 int VM_PROT_NO_CHANGE ; 
 int /*<<< orphan*/  XPR (int /*<<< orphan*/ ,char*,TYPE_1__*,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XPR_MEMORY_OBJECT ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ memory_object_should_return_page (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int pmap_disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_page_protect (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vm_pageout_steal_laundry (TYPE_1__*,int /*<<< orphan*/ ) ; 

memory_object_lock_result_t
memory_object_lock_page(
	vm_page_t		m,
	memory_object_return_t	should_return,
	boolean_t		should_flush,
	vm_prot_t		prot)
{
        XPR(XPR_MEMORY_OBJECT,
            "m_o_lock_page, page 0x%X rtn %d flush %d prot %d\n",
            m, should_return, should_flush, prot, 0);


	if (m->vmp_busy || m->vmp_cleaning)
		return (MEMORY_OBJECT_LOCK_RESULT_MUST_BLOCK);

	if (m->vmp_laundry)
		vm_pageout_steal_laundry(m, FALSE);

	/*
	 *	Don't worry about pages for which the kernel
	 *	does not have any data.
	 */
	if (m->vmp_absent || m->vmp_error || m->vmp_restart) {
		if (m->vmp_error && should_flush && !VM_PAGE_WIRED(m)) {
			/*
			 * dump the page, pager wants us to
			 * clean it up and there is no
			 * relevant data to return
			 */
			return (MEMORY_OBJECT_LOCK_RESULT_MUST_FREE);
		}
		return (MEMORY_OBJECT_LOCK_RESULT_DONE);
	}
	assert(!m->vmp_fictitious);

	if (VM_PAGE_WIRED(m)) {
		/*
		 * The page is wired... just clean or return the page if needed.
		 * Wired pages don't get flushed or disconnected from the pmap.
		 */
		if (memory_object_should_return_page(m, should_return))
			return (MEMORY_OBJECT_LOCK_RESULT_MUST_RETURN);

		return (MEMORY_OBJECT_LOCK_RESULT_DONE);
	}		

	if (should_flush) {
		/*
		 * must do the pmap_disconnect before determining the 
		 * need to return the page... otherwise it's possible
		 * for the page to go from the clean to the dirty state
		 * after we've made our decision
		 */
		if (pmap_disconnect(VM_PAGE_GET_PHYS_PAGE(m)) & VM_MEM_MODIFIED) {
			SET_PAGE_DIRTY(m, FALSE);
		}
	} else {
		/*
		 * If we are decreasing permission, do it now;
		 * let the fault handler take care of increases
		 * (pmap_page_protect may not increase protection).
		 */
		if (prot != VM_PROT_NO_CHANGE)
			pmap_page_protect(VM_PAGE_GET_PHYS_PAGE(m), VM_PROT_ALL & ~prot);
	}
	/*
	 *	Handle returning dirty or precious pages
	 */
	if (memory_object_should_return_page(m, should_return)) {
		/*
		 * we use to do a pmap_disconnect here in support
		 * of memory_object_lock_request, but that routine
		 * no longer requires this...  in any event, in
		 * our world, it would turn into a big noop since
		 * we don't lock the page in any way and as soon
		 * as we drop the object lock, the page can be
		 * faulted back into an address space
		 *
		 *	if (!should_flush)
		 *		pmap_disconnect(VM_PAGE_GET_PHYS_PAGE(m));
		 */
		return (MEMORY_OBJECT_LOCK_RESULT_MUST_RETURN);
	}

	/*
	 *	Handle flushing clean pages
	 */
	if (should_flush)
		return (MEMORY_OBJECT_LOCK_RESULT_MUST_FREE);

	/*
	 * we use to deactivate clean pages at this point,
	 * but we do not believe that an msync should change
	 * the 'age' of a page in the cache... here is the
	 * original comment and code concerning this...
	 *
	 *	XXX Make clean but not flush a paging hint,
	 *	and deactivate the pages.  This is a hack
	 *	because it overloads flush/clean with
	 *	implementation-dependent meaning.  This only
	 *	happens to pages that are already clean.
	 *
	 *   if (vm_page_deactivate_hint && (should_return != MEMORY_OBJECT_RETURN_NONE))
	 *	return (MEMORY_OBJECT_LOCK_RESULT_MUST_DEACTIVATE);
	 */

	return (MEMORY_OBJECT_LOCK_RESULT_DONE);
}