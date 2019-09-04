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
struct socket_filter_entry {struct socket_filter_entry* sfe_next_oncleanup; int /*<<< orphan*/  sfe_refcount; } ;
typedef  int SInt32 ;

/* Variables and functions */
 int OSDecrementAtomic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kernel_thread_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  sflt_cleanup_thread ; 
 struct socket_filter_entry* sock_filter_cleanup_entries ; 
 int /*<<< orphan*/  sock_filter_cleanup_lock ; 
 int /*<<< orphan*/ * sock_filter_cleanup_thread ; 
 int /*<<< orphan*/  wakeup (struct socket_filter_entry**) ; 

__attribute__((used)) static void
sflt_entry_release(struct socket_filter_entry *entry)
{
	SInt32 old = OSDecrementAtomic(&entry->sfe_refcount);
	if (old == 1) {
		/* That was the last reference */

		/* Take the cleanup lock */
		lck_mtx_lock(sock_filter_cleanup_lock);

		/* Put this item on the cleanup list */
		entry->sfe_next_oncleanup = sock_filter_cleanup_entries;
		sock_filter_cleanup_entries = entry;

		/* If the item is the first item in the list */
		if (entry->sfe_next_oncleanup == NULL) {
			if (sock_filter_cleanup_thread == NULL) {
				/* Create a thread */
				kernel_thread_start(sflt_cleanup_thread,
				    NULL, &sock_filter_cleanup_thread);
			} else {
				/* Wakeup the thread */
				wakeup(&sock_filter_cleanup_entries);
			}
		}

		/* Drop the cleanup lock */
		lck_mtx_unlock(sock_filter_cleanup_lock);
	} else if (old <= 0) {
		panic("sflt_entry_release - sfe_refcount (%d) <= 0\n",
		    (int)old);
		/* NOTREACHED */
	}
}