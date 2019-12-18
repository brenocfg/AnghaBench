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
struct task_struct {int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_COMM_LEN ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_event_comm (struct task_struct*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  task_lock (struct task_struct*) ; 
 int /*<<< orphan*/  task_unlock (struct task_struct*) ; 
 int /*<<< orphan*/  wmb () ; 

void set_task_comm(struct task_struct *tsk, char *buf)
{
	task_lock(tsk);

	/*
	 * Threads may access current->comm without holding
	 * the task lock, so write the string carefully.
	 * Readers without a lock may see incomplete new
	 * names but are safe from non-terminating string reads.
	 */
	memset(tsk->comm, 0, TASK_COMM_LEN);
	wmb();
	strlcpy(tsk->comm, buf, sizeof(tsk->comm));
	task_unlock(tsk);
	perf_event_comm(tsk);
}