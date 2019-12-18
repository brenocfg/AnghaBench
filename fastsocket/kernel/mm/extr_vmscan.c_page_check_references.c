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
struct scan_control {int /*<<< orphan*/  target_mem_cgroup; } ;
struct page {int dummy; } ;
struct mem_cgroup_zone {int dummy; } ;
typedef  enum page_references { ____Placeholder_page_references } page_references ;

/* Variables and functions */
 int PAGEREF_ACTIVATE ; 
 int PAGEREF_KEEP ; 
 int PAGEREF_RECLAIM ; 
 int PAGEREF_RECLAIM_CLEAN ; 
 scalar_t__ PageAnon (struct page*) ; 
 int /*<<< orphan*/  SetPageReferenced (struct page*) ; 
 int TestClearPageReferenced (struct page*) ; 
 unsigned long VM_LOCKED ; 
 int page_referenced (struct page*,int,int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static enum page_references page_check_references(struct page *page,
						  struct mem_cgroup_zone *mz,
						  struct scan_control *sc)
{
	int referenced_ptes, referenced_page;
	unsigned long vm_flags;

	referenced_ptes = page_referenced(page, 1, sc->target_mem_cgroup,
					  &vm_flags);
	referenced_page = TestClearPageReferenced(page);

	/*
	 * Mlock lost the isolation race with us.  Let try_to_unmap()
	 * move the page to the unevictable list.
	 */
	if (vm_flags & VM_LOCKED)
		return PAGEREF_RECLAIM;

	if (referenced_ptes) {
		if (PageAnon(page))
			return PAGEREF_ACTIVATE;
		/*
		 * All mapped pages start out with page table
		 * references from the instantiating fault, so we need
		 * to look twice if a mapped file page is used more
		 * than once.
		 *
		 * Mark it and spare it for another trip around the
		 * inactive list.  Another page table reference will
		 * lead to its activation.
		 *
		 * Note: the mark is set for activated pages as well
		 * so that recently deactivated but used pages are
		 * quickly recovered.
		 */
		SetPageReferenced(page);

		if (referenced_page)
			return PAGEREF_ACTIVATE;

		return PAGEREF_KEEP;
	}

	/* Reclaim if clean, defer dirty pages to writeback */
	if (referenced_page)
		return PAGEREF_RECLAIM_CLEAN;

	return PAGEREF_RECLAIM;
}