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
struct utrace {int /*<<< orphan*/  lock; scalar_t__ vfork_stop; } ;
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UTRACE_RESUME ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct utrace* task_utrace_struct (struct task_struct*) ; 
 int /*<<< orphan*/  utrace_stop (struct task_struct*,struct utrace*,int /*<<< orphan*/ ) ; 

void utrace_finish_vfork(struct task_struct *task)
{
	struct utrace *utrace = task_utrace_struct(task);

	if (utrace->vfork_stop) {
		spin_lock(&utrace->lock);
		utrace->vfork_stop = 0;
		spin_unlock(&utrace->lock);
		utrace_stop(task, utrace, UTRACE_RESUME); /* XXX */
	}
}