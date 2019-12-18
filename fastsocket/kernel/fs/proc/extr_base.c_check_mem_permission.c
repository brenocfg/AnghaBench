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
struct task_struct {int /*<<< orphan*/  cred_guard_mutex; } ;
struct mm_struct {int dummy; } ;

/* Variables and functions */
 struct mm_struct* ERR_PTR (int) ; 
 struct mm_struct* __check_mem_permission (struct task_struct*) ; 
 int mutex_lock_killable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mm_struct *check_mem_permission(struct task_struct *task)
{
	struct mm_struct *mm;
	int err;

	/*
	 * Avoid racing if task exec's as we might get a new mm but validate
	 * against old credentials.
	 */
	err = mutex_lock_killable(&task->cred_guard_mutex);
	if (err)
		return ERR_PTR(err);

	mm = __check_mem_permission(task);
	mutex_unlock(&task->cred_guard_mutex);

	return mm;
}