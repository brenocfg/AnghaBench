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

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ audit_backlog_limit ; 
 int /*<<< orphan*/  audit_backlog_wait ; 
 int /*<<< orphan*/  audit_skb_queue ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_timeout (unsigned long) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static void wait_for_auditd(unsigned long sleep_time)
{
	DECLARE_WAITQUEUE(wait, current);
	set_current_state(TASK_UNINTERRUPTIBLE);
	add_wait_queue(&audit_backlog_wait, &wait);

	if (audit_backlog_limit &&
	    skb_queue_len(&audit_skb_queue) > audit_backlog_limit)
		schedule_timeout(sleep_time);

	__set_current_state(TASK_RUNNING);
	remove_wait_queue(&audit_backlog_wait, &wait);
}