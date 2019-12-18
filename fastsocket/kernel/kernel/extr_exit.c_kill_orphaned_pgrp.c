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
struct task_struct {struct task_struct* real_parent; } ;
struct pid {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEND_SIG_PRIV ; 
 int /*<<< orphan*/  SIGCONT ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  __kill_pgrp_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pid*) ; 
 scalar_t__ has_stopped_jobs (struct pid*) ; 
 struct pid* task_pgrp (struct task_struct*) ; 
 scalar_t__ task_session (struct task_struct*) ; 
 scalar_t__ will_become_orphaned_pgrp (struct pid*,struct task_struct*) ; 

__attribute__((used)) static void
kill_orphaned_pgrp(struct task_struct *tsk, struct task_struct *parent)
{
	struct pid *pgrp = task_pgrp(tsk);
	struct task_struct *ignored_task = tsk;

	if (!parent)
		 /* exit: our father is in a different pgrp than
		  * we are and we were the only connection outside.
		  */
		parent = tsk->real_parent;
	else
		/* reparent: our child is in a different pgrp than
		 * we are, and it was the only connection outside.
		 */
		ignored_task = NULL;

	if (task_pgrp(parent) != pgrp &&
	    task_session(parent) == task_session(tsk) &&
	    will_become_orphaned_pgrp(pgrp, ignored_task) &&
	    has_stopped_jobs(pgrp)) {
		__kill_pgrp_info(SIGHUP, SEND_SIG_PRIV, pgrp);
		__kill_pgrp_info(SIGCONT, SEND_SIG_PRIV, pgrp);
	}
}