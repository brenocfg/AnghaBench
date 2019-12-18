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
struct mm_struct {int dummy; } ;

/* Variables and functions */
 int get_dumpable (struct mm_struct*) ; 
 int /*<<< orphan*/  task_lock (struct task_struct*) ; 
 int /*<<< orphan*/  task_unlock (struct task_struct*) ; 

__attribute__((used)) static int task_dumpable(struct task_struct *task)
{
	int dumpable = 0;
	struct mm_struct *mm;

	task_lock(task);
	mm = task->mm;
	if (mm)
		dumpable = get_dumpable(mm);
	task_unlock(task);
	if(dumpable == 1)
		return 1;
	return 0;
}