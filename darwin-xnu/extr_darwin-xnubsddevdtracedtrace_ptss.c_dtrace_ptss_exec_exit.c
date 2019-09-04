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
struct proc {struct dtrace_ptss_page* p_dtrace_ptss_pages; int /*<<< orphan*/ * p_dtrace_ptss_free_list; int /*<<< orphan*/  p_mlock; int /*<<< orphan*/  p_dtrace_sprlock; } ;
struct dtrace_ptss_page {struct dtrace_ptss_page* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_NOTOWNED ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  _FREE (struct dtrace_ptss_page*,int /*<<< orphan*/ ) ; 

void
dtrace_ptss_exec_exit(struct proc* p) {
	/*
	 * Should hold sprlock to touch the pages list. Must not
	 * hold the proc lock to avoid deadlock.
	 */
	LCK_MTX_ASSERT(&p->p_dtrace_sprlock, LCK_MTX_ASSERT_OWNED);
	LCK_MTX_ASSERT(&p->p_mlock, LCK_MTX_ASSERT_NOTOWNED);

	p->p_dtrace_ptss_free_list = NULL;

	struct dtrace_ptss_page* temp = p->p_dtrace_ptss_pages;
	p->p_dtrace_ptss_pages = NULL;

	while (temp != NULL) {
		struct dtrace_ptss_page* next = temp->next;
		
		// Do we need to specifically mach_vm_deallocate the user pages?
		// This can be called when the process is exiting, I believe the proc's
		// vm_map_t may already be toast.
		
		// Must be certain to free the kernel memory!
		_FREE(temp, M_TEMP);
		temp = next;
	}
}