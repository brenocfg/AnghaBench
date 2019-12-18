#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct task_struct {scalar_t__ state; } ;
struct TYPE_3__ {scalar_t__ ksp; } ;
struct TYPE_4__ {TYPE_1__ pcb; } ;

/* Variables and functions */
 scalar_t__ TASK_RUNNING ; 
 struct task_struct* current ; 
 scalar_t__ in_sched_functions (unsigned long) ; 
 TYPE_2__* task_thread_info (struct task_struct*) ; 
 unsigned long thread_saved_pc (struct task_struct*) ; 

unsigned long
get_wchan(struct task_struct *p)
{
	unsigned long schedule_frame;
	unsigned long pc;
	if (!p || p == current || p->state == TASK_RUNNING)
		return 0;
	/*
	 * This one depends on the frame size of schedule().  Do a
	 * "disass schedule" in gdb to find the frame size.  Also, the
	 * code assumes that sleep_on() follows immediately after
	 * interruptible_sleep_on() and that add_timer() follows
	 * immediately after interruptible_sleep().  Ugly, isn't it?
	 * Maybe adding a wchan field to task_struct would be better,
	 * after all...
	 */

	pc = thread_saved_pc(p);
	if (in_sched_functions(pc)) {
		schedule_frame = ((unsigned long *)task_thread_info(p)->pcb.ksp)[6];
		return ((unsigned long *)schedule_frame)[12];
	}
	return pc;
}