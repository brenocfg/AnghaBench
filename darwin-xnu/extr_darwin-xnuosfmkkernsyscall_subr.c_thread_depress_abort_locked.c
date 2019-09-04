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
typedef  TYPE_1__* thread_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_4__ {int sched_flags; int /*<<< orphan*/  depress_timer_active; int /*<<< orphan*/  depress_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_NOT_DEPRESSED ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  SETPRI_LAZY ; 
 int TH_SFLAG_DEPRESSED_MASK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  thread_recompute_sched_pri (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ timer_call_cancel (int /*<<< orphan*/ *) ; 

kern_return_t
thread_depress_abort_locked(thread_t thread)
{
	if ((thread->sched_flags & TH_SFLAG_DEPRESSED_MASK) == 0)
		return KERN_NOT_DEPRESSED;

	assert((thread->sched_flags & TH_SFLAG_DEPRESSED_MASK) != TH_SFLAG_DEPRESSED_MASK);

	thread->sched_flags &= ~TH_SFLAG_DEPRESSED_MASK;

	thread_recompute_sched_pri(thread, SETPRI_LAZY);

	if (timer_call_cancel(&thread->depress_timer))
		thread->depress_timer_active--;

	return KERN_SUCCESS;
}