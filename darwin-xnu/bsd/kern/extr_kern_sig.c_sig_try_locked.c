#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  thread_t ;
typedef  TYPE_1__* proc_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_4__ {int /*<<< orphan*/  p_mlock; int /*<<< orphan*/  sigwait_thread; scalar_t__ exit_thread; scalar_t__ sigwait; } ;

/* Variables and functions */
 int PCATCH ; 
 int PDROP ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_lock (TYPE_1__*) ; 
 scalar_t__ thread_should_abort (int /*<<< orphan*/ ) ; 

int
sig_try_locked(proc_t p)
{
	thread_t	self = current_thread();

	while (p->sigwait || p->exit_thread) {
		if (p->exit_thread) {
			return(0);
		}
		msleep((caddr_t)&p->sigwait_thread, &p->p_mlock, PCATCH | PDROP, 0, 0);
		if (thread_should_abort(self)) {
			/*
			 * Terminate request - clean up.
			 */
			proc_lock(p);
			return -1;
		}
		proc_lock(p);
	}
	return 1;
}