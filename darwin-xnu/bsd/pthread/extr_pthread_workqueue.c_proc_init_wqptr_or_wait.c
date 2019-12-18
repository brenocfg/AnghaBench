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
struct proc {struct workqueue* p_wqptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  THREAD_CONTINUE_NULL ; 
 int /*<<< orphan*/  THREAD_UNINT ; 
 struct workqueue* WQPTR_IS_INITING_VALUE ; 
 int /*<<< orphan*/  assert_wait (struct workqueue**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_lock (struct proc*) ; 
 int /*<<< orphan*/  proc_unlock (struct proc*) ; 
 int /*<<< orphan*/  thread_block (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
proc_init_wqptr_or_wait(struct proc *p)
{
	struct workqueue *wq;

	proc_lock(p);
	wq = p->p_wqptr;

	if (wq == NULL) {
		p->p_wqptr = WQPTR_IS_INITING_VALUE;
		proc_unlock(p);
		return true;
	}

	if (wq == WQPTR_IS_INITING_VALUE) {
		assert_wait(&p->p_wqptr, THREAD_UNINT);
		proc_unlock(p);
		thread_block(THREAD_CONTINUE_NULL);
	} else {
		proc_unlock(p);
	}
	return false;
}