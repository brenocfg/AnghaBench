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
struct ubifs_info {int /*<<< orphan*/  bgt_name; scalar_t__ need_bgt; } ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cond_resched () ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  dbg_msg (char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  run_bg_commit (struct ubifs_info*) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_freezable () ; 
 scalar_t__ try_to_freeze () ; 
 int ubifs_bg_wbufs_sync (struct ubifs_info*) ; 
 int /*<<< orphan*/  ubifs_ro_mode (struct ubifs_info*,int) ; 

int ubifs_bg_thread(void *info)
{
	int err;
	struct ubifs_info *c = info;

	dbg_msg("background thread \"%s\" started, PID %d",
		c->bgt_name, current->pid);
	set_freezable();

	while (1) {
		if (kthread_should_stop())
			break;

		if (try_to_freeze())
			continue;

		set_current_state(TASK_INTERRUPTIBLE);
		/* Check if there is something to do */
		if (!c->need_bgt) {
			/*
			 * Nothing prevents us from going sleep now and
			 * be never woken up and block the task which
			 * could wait in 'kthread_stop()' forever.
			 */
			if (kthread_should_stop())
				break;
			schedule();
			continue;
		} else
			__set_current_state(TASK_RUNNING);

		c->need_bgt = 0;
		err = ubifs_bg_wbufs_sync(c);
		if (err)
			ubifs_ro_mode(c, err);

		run_bg_commit(c);
		cond_resched();
	}

	dbg_msg("background thread \"%s\" stops", c->bgt_name);
	return 0;
}