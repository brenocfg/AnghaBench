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
struct task_struct {int dummy; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct mm_struct* get_task_mm (struct task_struct*) ; 

__attribute__((used)) static struct mm_struct *take_tasks_mm(struct task_struct *task)
{
	struct mm_struct *mm = get_task_mm(task);
	if (mm)
		down_read(&mm->mmap_sem);
	return mm;
}