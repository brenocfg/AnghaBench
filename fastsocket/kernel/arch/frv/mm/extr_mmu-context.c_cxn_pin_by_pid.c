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
struct task_struct {struct mm_struct* mm; } ;
struct mm_struct {int /*<<< orphan*/  context; int /*<<< orphan*/  mm_users; } ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int EINVAL ; 
 int ESRCH ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cxn_owners_lock ; 
 int cxn_pinned ; 
 struct task_struct* find_task_by_vpid (scalar_t__) ; 
 int get_cxn (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmput (struct mm_struct*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_lock (struct task_struct*) ; 
 int /*<<< orphan*/  task_unlock (struct task_struct*) ; 
 int /*<<< orphan*/  tasklist_lock ; 

int cxn_pin_by_pid(pid_t pid)
{
	struct task_struct *tsk;
	struct mm_struct *mm = NULL;
	int ret;

	/* unpin if pid is zero */
	if (pid == 0) {
		cxn_pinned = -1;
		return 0;
	}

	ret = -ESRCH;

	/* get a handle on the mm_struct */
	read_lock(&tasklist_lock);
	tsk = find_task_by_vpid(pid);
	if (tsk) {
		ret = -EINVAL;

		task_lock(tsk);
		if (tsk->mm) {
			mm = tsk->mm;
			atomic_inc(&mm->mm_users);
			ret = 0;
		}
		task_unlock(tsk);
	}
	read_unlock(&tasklist_lock);

	if (ret < 0)
		return ret;

	/* make sure it has a CXN and pin it */
	spin_lock(&cxn_owners_lock);
	cxn_pinned = get_cxn(&mm->context);
	spin_unlock(&cxn_owners_lock);

	mmput(mm);
	return 0;
}