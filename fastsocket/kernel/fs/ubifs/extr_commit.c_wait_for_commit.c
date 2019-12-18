#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ubifs_info {scalar_t__ cmt_state; int /*<<< orphan*/  cmt_wq; } ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 scalar_t__ COMMIT_RUNNING_BACKGROUND ; 
 scalar_t__ COMMIT_RUNNING_REQUIRED ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  dbg_cmt (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wait_for_commit(struct ubifs_info *c)
{
	dbg_cmt("pid %d goes sleep", current->pid);

	/*
	 * The following sleeps if the condition is false, and will be woken
	 * when the commit ends. It is possible, although very unlikely, that we
	 * will wake up and see the subsequent commit running, rather than the
	 * one we were waiting for, and go back to sleep.  However, we will be
	 * woken again, so there is no danger of sleeping forever.
	 */
	wait_event(c->cmt_wq, c->cmt_state != COMMIT_RUNNING_BACKGROUND &&
			      c->cmt_state != COMMIT_RUNNING_REQUIRED);
	dbg_cmt("commit finished, pid %d woke up", current->pid);
	return 0;
}