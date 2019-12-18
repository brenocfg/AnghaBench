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
typedef  int /*<<< orphan*/  task_t ;

/* Variables and functions */
 int /*<<< orphan*/  fslog_extmod_msgtracer (void*,void*) ; 
 void* get_bsdtask_info (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
extmod_statistics_log(task_t current_task, task_t target)
{
	void *c_proc;
	void *t_proc;

	c_proc = get_bsdtask_info(current_task);
	t_proc = get_bsdtask_info(target);
	if (c_proc && t_proc) {
		fslog_extmod_msgtracer(c_proc, t_proc);
	}
}