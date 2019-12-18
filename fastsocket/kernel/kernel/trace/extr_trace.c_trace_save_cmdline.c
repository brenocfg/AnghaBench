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
struct task_struct {size_t pid; int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 unsigned int NO_CMDLINE_MAP ; 
 size_t PID_MAX_DEFAULT ; 
 int SAVED_CMDLINES ; 
 int /*<<< orphan*/  TASK_COMM_LEN ; 
 int /*<<< orphan*/  __raw_spin_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __raw_spin_unlock (int /*<<< orphan*/ *) ; 
 int cmdline_idx ; 
 unsigned int* map_cmdline_to_pid ; 
 unsigned int* map_pid_to_cmdline ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * saved_cmdlines ; 
 int /*<<< orphan*/  trace_cmdline_lock ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void trace_save_cmdline(struct task_struct *tsk)
{
	unsigned pid, idx;

	if (!tsk->pid || unlikely(tsk->pid > PID_MAX_DEFAULT))
		return;

	/*
	 * It's not the end of the world if we don't get
	 * the lock, but we also don't want to spin
	 * nor do we want to disable interrupts,
	 * so if we miss here, then better luck next time.
	 */
	if (!__raw_spin_trylock(&trace_cmdline_lock))
		return;

	idx = map_pid_to_cmdline[tsk->pid];
	if (idx == NO_CMDLINE_MAP) {
		idx = (cmdline_idx + 1) % SAVED_CMDLINES;

		/*
		 * Check whether the cmdline buffer at idx has a pid
		 * mapped. We are going to overwrite that entry so we
		 * need to clear the map_pid_to_cmdline. Otherwise we
		 * would read the new comm for the old pid.
		 */
		pid = map_cmdline_to_pid[idx];
		if (pid != NO_CMDLINE_MAP)
			map_pid_to_cmdline[pid] = NO_CMDLINE_MAP;

		map_cmdline_to_pid[idx] = tsk->pid;
		map_pid_to_cmdline[tsk->pid] = idx;

		cmdline_idx = idx;
	}

	memcpy(&saved_cmdlines[idx], tsk->comm, TASK_COMM_LEN);

	__raw_spin_unlock(&trace_cmdline_lock);
}