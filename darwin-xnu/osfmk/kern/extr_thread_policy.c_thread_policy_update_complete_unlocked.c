#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* thread_t ;
typedef  TYPE_3__* task_pend_token_t ;
struct TYPE_10__ {scalar_t__ tpt_update_thread_sfi; scalar_t__ tpt_update_throttle; scalar_t__ tpt_update_sockets; } ;
struct TYPE_9__ {int /*<<< orphan*/  uthread; TYPE_1__* task; } ;
struct TYPE_8__ {int /*<<< orphan*/  bsd_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  proc_apply_task_networkbg (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  rethrottle_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfi_reevaluate (TYPE_2__*) ; 

void
thread_policy_update_complete_unlocked(thread_t thread, task_pend_token_t pend_token)
{
#ifdef MACH_BSD
	if (pend_token->tpt_update_sockets)
		proc_apply_task_networkbg(thread->task->bsd_info, thread);
#endif /* MACH_BSD */

	if (pend_token->tpt_update_throttle)
		rethrottle_thread(thread->uthread);

	if (pend_token->tpt_update_thread_sfi)
		sfi_reevaluate(thread);
}