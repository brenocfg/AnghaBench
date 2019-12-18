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
struct seq_file {int dummy; } ;
struct pid_namespace {int dummy; } ;
struct pid {int dummy; } ;
struct mm_struct {int dummy; } ;

/* Variables and functions */
 struct mm_struct* get_task_mm (struct task_struct*) ; 
 int /*<<< orphan*/  mmput (struct mm_struct*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,int,int,int,int,int,int /*<<< orphan*/ ) ; 
 int task_statm (struct mm_struct*,int*,int*,int*,int*) ; 

int proc_pid_statm(struct seq_file *m, struct pid_namespace *ns,
			struct pid *pid, struct task_struct *task)
{
	int size = 0, resident = 0, shared = 0, text = 0, lib = 0, data = 0;
	struct mm_struct *mm = get_task_mm(task);

	if (mm) {
		size = task_statm(mm, &shared, &text, &data, &resident);
		mmput(mm);
	}
	seq_printf(m, "%d %d %d %d %d %d %d\n",
			size, resident, shared, text, lib, data, 0);

	return 0;
}