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
struct task_struct {int /*<<< orphan*/  cred_guard_mutex; } ;
struct mm_struct {int dummy; } ;
struct TYPE_2__ {struct mm_struct* mm; } ;

/* Variables and functions */
 int EACCES ; 
 struct mm_struct* ERR_PTR (int) ; 
 int /*<<< orphan*/  PTRACE_MODE_READ ; 
 TYPE_1__* current ; 
 struct mm_struct* get_task_mm (struct task_struct*) ; 
 int /*<<< orphan*/  mmput (struct mm_struct*) ; 
 int mutex_lock_killable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptrace_may_access (struct task_struct*,int /*<<< orphan*/ ) ; 

struct mm_struct *mm_for_maps(struct task_struct *task)
{
	struct mm_struct *mm;
	int err;

	err =  mutex_lock_killable(&task->cred_guard_mutex);
	if (err)
		return ERR_PTR(err);

	mm = get_task_mm(task);
	if (mm && mm != current->mm &&
			!ptrace_may_access(task, PTRACE_MODE_READ)) {
		mmput(mm);
		mm = ERR_PTR(-EACCES);
	}
	mutex_unlock(&task->cred_guard_mutex);

	return mm;
}