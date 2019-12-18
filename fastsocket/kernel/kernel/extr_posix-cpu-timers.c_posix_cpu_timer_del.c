#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct task_struct {TYPE_3__* sighand; int /*<<< orphan*/ * signal; } ;
struct TYPE_4__ {int /*<<< orphan*/  entry; scalar_t__ firing; struct task_struct* task; } ;
struct TYPE_5__ {TYPE_1__ cpu; } ;
struct k_itimer {TYPE_2__ it; } ;
struct TYPE_6__ {int /*<<< orphan*/  siglock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int TIMER_RETRY ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklist_lock ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int posix_cpu_timer_del(struct k_itimer *timer)
{
	struct task_struct *p = timer->it.cpu.task;
	int ret = 0;

	if (likely(p != NULL)) {
		read_lock(&tasklist_lock);
		if (unlikely(p->signal == NULL)) {
			/*
			 * We raced with the reaping of the task.
			 * The deletion should have cleared us off the list.
			 */
			BUG_ON(!list_empty(&timer->it.cpu.entry));
		} else {
			spin_lock(&p->sighand->siglock);
			if (timer->it.cpu.firing)
				ret = TIMER_RETRY;
			else
				list_del(&timer->it.cpu.entry);
			spin_unlock(&p->sighand->siglock);
		}
		read_unlock(&tasklist_lock);

		if (!ret)
			put_task_struct(p);
	}

	return ret;
}