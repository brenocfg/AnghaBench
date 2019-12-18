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
struct uthread {scalar_t__ uu_ucred; } ;
struct proc {int dummy; } ;
typedef  struct proc* proc_t ;
typedef  scalar_t__ kauth_cred_t ;

/* Variables and functions */
 scalar_t__ NOCRED ; 
 int /*<<< orphan*/  current_thread () ; 
 scalar_t__ get_bsdtask_info (int /*<<< orphan*/ ) ; 
 struct uthread* get_bsdthread_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_threadtask (int /*<<< orphan*/ ) ; 
 scalar_t__ kauth_cred_proc_ref (struct proc*) ; 
 int /*<<< orphan*/  panic (char*) ; 

kauth_cred_t
kauth_cred_get(void)
{
	struct proc *p;
	struct uthread *uthread;

	uthread = get_bsdthread_info(current_thread());
	/* sanity */
	if (uthread == NULL)
		panic("thread wants credential but has no BSD thread info");
	/*
	 * We can lazy-bind credentials to threads, as long as their processes
	 * have them.
	 *
	 * XXX If we later inline this function, the code in this block
	 * XXX should probably be called out in a function.
	 */
	if (uthread->uu_ucred == NOCRED) {
		if ((p = (proc_t) get_bsdtask_info(get_threadtask(current_thread()))) == NULL)
			panic("thread wants credential but has no BSD process");
		uthread->uu_ucred = kauth_cred_proc_ref(p);
	}
	return(uthread->uu_ucred);
}