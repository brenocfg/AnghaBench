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
struct md_thread {int /*<<< orphan*/  tsk; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct md_thread*) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pers_lock ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_pid_nr (int /*<<< orphan*/ ) ; 

void md_unregister_thread(struct md_thread **threadp)
{
	struct md_thread *thread = *threadp;
	if (!thread)
		return;
	pr_debug("interrupting MD-thread pid %d\n", task_pid_nr(thread->tsk));
	/* Locking ensures that mddev_unlock does not wake_up a
	 * non-existent thread
	 */
	spin_lock(&pers_lock);
	*threadp = NULL;
	spin_unlock(&pers_lock);

	kthread_stop(thread->tsk);
	kfree(thread);
}