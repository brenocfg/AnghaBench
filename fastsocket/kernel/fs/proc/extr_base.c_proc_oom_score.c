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

/* Variables and functions */
 unsigned long oom_badness (struct task_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ pid_alive (struct task_struct*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int sprintf (char*,char*,unsigned long) ; 
 int /*<<< orphan*/  tasklist_lock ; 
 scalar_t__ total_swap_pages ; 
 scalar_t__ totalram_pages ; 

__attribute__((used)) static int proc_oom_score(struct task_struct *task, char *buffer)
{
	unsigned long points = 0;

	read_lock(&tasklist_lock);
	if (pid_alive(task))
		points = oom_badness(task, NULL, NULL,
					totalram_pages + total_swap_pages);
	read_unlock(&tasklist_lock);
	return sprintf(buffer, "%lu\n", points);
}