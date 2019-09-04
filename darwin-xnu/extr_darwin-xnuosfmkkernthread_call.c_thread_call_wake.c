#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_call_group_t ;
struct TYPE_5__ {scalar_t__ active_count; scalar_t__ idle_count; int flags; int /*<<< orphan*/  dealloc_timer; int /*<<< orphan*/  idle_waitq; } ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  NO_EVENT64 ; 
 int TCG_DEALLOC_ACTIVE ; 
 int /*<<< orphan*/  THREAD_AWAKENED ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WAITQ_ALL_PRIORITIES ; 
 int /*<<< orphan*/  daemon_waitq ; 
 scalar_t__ group_isparallel (TYPE_1__*) ; 
 scalar_t__ thread_call_daemon_awake ; 
 scalar_t__ thread_call_group_should_add_thread (TYPE_1__*) ; 
 scalar_t__ timer_call_cancel (int /*<<< orphan*/ *) ; 
 scalar_t__ waitq_wakeup64_one (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ void
thread_call_wake(
	thread_call_group_t		group)
{
	/* 
	 * New behavior: use threads if you've got 'em.
	 * Traditional behavior: wake only if no threads running.
	 */
	if (group_isparallel(group) || group->active_count == 0) {
		if (waitq_wakeup64_one(&group->idle_waitq, NO_EVENT64,
				       THREAD_AWAKENED, WAITQ_ALL_PRIORITIES) == KERN_SUCCESS) {
			group->idle_count--; group->active_count++;

			if (group->idle_count == 0 && (group->flags & TCG_DEALLOC_ACTIVE) == TCG_DEALLOC_ACTIVE) {
				if (timer_call_cancel(&group->dealloc_timer) == TRUE) {
					group->flags &= ~TCG_DEALLOC_ACTIVE;
				}
			}
		} else {
			if (!thread_call_daemon_awake && thread_call_group_should_add_thread(group)) {
				thread_call_daemon_awake = TRUE;
				waitq_wakeup64_one(&daemon_waitq, NO_EVENT64,
						   THREAD_AWAKENED, WAITQ_ALL_PRIORITIES);
			}
		}
	}
}