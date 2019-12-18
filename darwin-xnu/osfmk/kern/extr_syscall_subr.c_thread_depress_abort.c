#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
typedef  int /*<<< orphan*/  spl_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_6__ {int sched_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_NOT_DEPRESSED ; 
 int TH_SFLAG_DEPRESSED_MASK ; 
 int TH_SFLAG_POLLDEPRESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  splsched () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_depress_abort_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_unlock (TYPE_1__*) ; 

kern_return_t
thread_depress_abort(thread_t thread)
{
	kern_return_t result = KERN_NOT_DEPRESSED;

	spl_t s = splsched();
	thread_lock(thread);

	assert((thread->sched_flags & TH_SFLAG_DEPRESSED_MASK) != TH_SFLAG_DEPRESSED_MASK);

	/*
	 * User-triggered depress-aborts should not get out
	 * of the poll-depress, but they should cancel a regular depress.
	 */
	if ((thread->sched_flags & TH_SFLAG_POLLDEPRESS) == 0) {
		result = thread_depress_abort_locked(thread);
	}

	thread_unlock(thread);
	splx(s);

	return result;
}