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
struct ubi_device {int /*<<< orphan*/  bgt_name; scalar_t__ thread_enabled; int /*<<< orphan*/  wl_lock; scalar_t__ ro_mode; int /*<<< orphan*/  works; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  WL_MAX_FAILURES ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  dbg_wl (char*,int /*<<< orphan*/ ) ; 
 int do_work (struct ubi_device*) ; 
 scalar_t__ kthread_should_stop () ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_freezable () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_pid_nr (int /*<<< orphan*/ ) ; 
 scalar_t__ try_to_freeze () ; 
 int /*<<< orphan*/  ubi_err (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ubi_msg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubi_ro_mode (struct ubi_device*) ; 

int ubi_thread(void *u)
{
	int failures = 0;
	struct ubi_device *ubi = u;

	ubi_msg("background thread \"%s\" started, PID %d",
		ubi->bgt_name, task_pid_nr(current));

	set_freezable();
	for (;;) {
		int err;

		if (kthread_should_stop())
			break;

		if (try_to_freeze())
			continue;

		spin_lock(&ubi->wl_lock);
		if (list_empty(&ubi->works) || ubi->ro_mode ||
			       !ubi->thread_enabled) {
			set_current_state(TASK_INTERRUPTIBLE);
			spin_unlock(&ubi->wl_lock);
			schedule();
			continue;
		}
		spin_unlock(&ubi->wl_lock);

		err = do_work(ubi);
		if (err) {
			ubi_err("%s: work failed with error code %d",
				ubi->bgt_name, err);
			if (failures++ > WL_MAX_FAILURES) {
				/*
				 * Too many failures, disable the thread and
				 * switch to read-only mode.
				 */
				ubi_msg("%s: %d consecutive failures",
					ubi->bgt_name, WL_MAX_FAILURES);
				ubi_ro_mode(ubi);
				ubi->thread_enabled = 0;
				continue;
			}
		} else
			failures = 0;

		cond_resched();
	}

	dbg_wl("background thread \"%s\" is killed", ubi->bgt_name);
	return 0;
}