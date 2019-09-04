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
typedef  TYPE_1__* thread_call_group_t ;
struct TYPE_4__ {int /*<<< orphan*/  idle_waitq; int /*<<< orphan*/  dealloc_timer; int /*<<< orphan*/ * delayed_timers; int /*<<< orphan*/ * delayed_queues; int /*<<< orphan*/  pending_queue; } ;

/* Variables and functions */
 int SYNC_POLICY_DISABLE_IRQ ; 
 int SYNC_POLICY_REVERSED ; 
 size_t TCF_ABSOLUTE ; 
 size_t TCF_CONTINUOUS ; 
 int /*<<< orphan*/  queue_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_call_dealloc_timer ; 
 int /*<<< orphan*/  thread_call_delayed_timer ; 
 int /*<<< orphan*/  timer_call_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  waitq_init (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
thread_call_group_setup(thread_call_group_t group)
{
	queue_init(&group->pending_queue);
	queue_init(&group->delayed_queues[TCF_ABSOLUTE]);
	queue_init(&group->delayed_queues[TCF_CONTINUOUS]);

	/* TODO: Consolidate to one hard timer for each group */
	timer_call_setup(&group->delayed_timers[TCF_ABSOLUTE],   thread_call_delayed_timer, group);
	timer_call_setup(&group->delayed_timers[TCF_CONTINUOUS], thread_call_delayed_timer, group);
	timer_call_setup(&group->dealloc_timer, thread_call_dealloc_timer, group);

	/* Reverse the wait order so we re-use the most recently parked thread from the pool */
	waitq_init(&group->idle_waitq, SYNC_POLICY_REVERSED|SYNC_POLICY_DISABLE_IRQ);
}