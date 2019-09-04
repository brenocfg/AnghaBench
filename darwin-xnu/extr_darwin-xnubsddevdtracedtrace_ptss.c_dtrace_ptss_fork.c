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
struct proc {struct dtrace_ptss_page* p_dtrace_ptss_pages; int /*<<< orphan*/  p_mlock; int /*<<< orphan*/  p_dtrace_sprlock; } ;
struct dtrace_ptss_page {struct dtrace_ptss_page* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_NOTOWNED ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  dtrace_ptss_free_page (struct proc*,struct dtrace_ptss_page*) ; 

void
dtrace_ptss_fork(struct proc* parent, struct proc* child) {
	// The child should not have any pages/entries allocated at this point.
	// ASSERT(child->p_dtrace_ptss_pages == NULL);
	// ASSERT(child->p_dtrace_ptss_free_list == NULL);

	/*
	 * The parent's sprlock should be held, to protect its pages list
	 * from changing while the child references it. The child's sprlock
	 * must also be held, because we are modifying its pages list.
	 * Finally, to prevent a deadlock with the fasttrap cleanup code,
	 * neither the parent or child proc_lock should be held.
	 */
	LCK_MTX_ASSERT(&parent->p_dtrace_sprlock, LCK_MTX_ASSERT_OWNED);
	LCK_MTX_ASSERT(&parent->p_mlock, LCK_MTX_ASSERT_NOTOWNED);
	LCK_MTX_ASSERT(&child->p_dtrace_sprlock, LCK_MTX_ASSERT_OWNED);
	LCK_MTX_ASSERT(&child->p_mlock, LCK_MTX_ASSERT_NOTOWNED);

	// Get page list from *PARENT*
	struct dtrace_ptss_page* temp = parent->p_dtrace_ptss_pages;

	while (temp != NULL) {		
		// Freeing the page in the *CHILD*
		dtrace_ptss_free_page(child, temp);

		// Do not free the kernel memory, it belong to the parent.
		temp = temp->next;
	}
}