#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  TYPE_1__* thread_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_7__ {int sched_flags; scalar_t__ saved_mode; scalar_t__ sched_mode; scalar_t__ policy_reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCHED_TAILQ ; 
 scalar_t__ TH_MODE_NONE ; 
 int /*<<< orphan*/  TH_MODE_TIMESHARE ; 
 int TH_SFLAG_DEMOTED_MASK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sched_set_thread_mode (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_recompute_priority (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_run_queue_reinsert (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ thread_run_queue_remove (TYPE_1__*) ; 

void
sched_thread_mode_demote(thread_t thread, uint32_t reason)
{
	assert(reason & TH_SFLAG_DEMOTED_MASK);
	assert((thread->sched_flags & reason) != reason);

	if (thread->policy_reset)
		return;

	if (thread->sched_flags & TH_SFLAG_DEMOTED_MASK) {
		/* Another demotion reason is already active */
		thread->sched_flags |= reason;
		return;
	}

	assert(thread->saved_mode == TH_MODE_NONE);

	boolean_t removed = thread_run_queue_remove(thread);

	thread->sched_flags |= reason;

	thread->saved_mode = thread->sched_mode;

	sched_set_thread_mode(thread, TH_MODE_TIMESHARE);

	thread_recompute_priority(thread);

	if (removed)
		thread_run_queue_reinsert(thread, SCHED_TAILQ);
}