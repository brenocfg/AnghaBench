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
struct workqueue {int dummy; } ;
struct proc {int /*<<< orphan*/  p_wqptr; } ;

/* Variables and functions */
 struct workqueue* WQPTR_IS_INITING_VALUE ; 
 struct workqueue* os_atomic_xchg (int /*<<< orphan*/ *,struct workqueue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_lock (struct proc*) ; 
 int /*<<< orphan*/  proc_unlock (struct proc*) ; 
 int /*<<< orphan*/  release ; 
 int /*<<< orphan*/  thread_wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
proc_set_wqptr(struct proc *p, struct workqueue *wq)
{
	wq = os_atomic_xchg(&p->p_wqptr, wq, release);
	if (wq == WQPTR_IS_INITING_VALUE) {
		proc_lock(p);
		thread_wakeup(&p->p_wqptr);
		proc_unlock(p);
	}
}