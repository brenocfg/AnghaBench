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
typedef  TYPE_1__* thread_t ;
typedef  int /*<<< orphan*/  sched_mode_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_7__ {int sched_flags; int /*<<< orphan*/  saved_mode; scalar_t__ policy_reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCHED_TAILQ ; 
 int TH_SFLAG_DEMOTED_MASK ; 
 int /*<<< orphan*/  sched_set_thread_mode (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_recompute_priority (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_run_queue_reinsert (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ thread_run_queue_remove (TYPE_1__*) ; 

__attribute__((used)) static void
thread_set_user_sched_mode_and_recompute_pri(thread_t thread, sched_mode_t mode)
{
	if (thread->policy_reset)
		return;

	boolean_t removed = thread_run_queue_remove(thread);

	/*
	 * TODO: Instead of having saved mode, have 'user mode' and 'true mode'.
	 * That way there's zero confusion over which the user wants
	 * and which the kernel wants.
	 */
	if (thread->sched_flags & TH_SFLAG_DEMOTED_MASK)
		thread->saved_mode = mode;
	else
		sched_set_thread_mode(thread, mode);

	thread_recompute_priority(thread);

	if (removed)
		thread_run_queue_reinsert(thread, SCHED_TAILQ);
}