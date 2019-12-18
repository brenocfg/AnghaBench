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
struct unw_frame_info {int dummy; } ;
struct task_struct {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ TASK_RUNNING ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  in_sched_functions (unsigned long) ; 
 int /*<<< orphan*/  unw_get_ip (struct unw_frame_info*,unsigned long*) ; 
 int /*<<< orphan*/  unw_init_from_blocked_task (struct unw_frame_info*,struct task_struct*) ; 
 scalar_t__ unw_unwind (struct unw_frame_info*) ; 

unsigned long
get_wchan (struct task_struct *p)
{
	struct unw_frame_info info;
	unsigned long ip;
	int count = 0;

	if (!p || p == current || p->state == TASK_RUNNING)
		return 0;

	/*
	 * Note: p may not be a blocked task (it could be current or
	 * another process running on some other CPU.  Rather than
	 * trying to determine if p is really blocked, we just assume
	 * it's blocked and rely on the unwind routines to fail
	 * gracefully if the process wasn't really blocked after all.
	 * --davidm 99/12/15
	 */
	unw_init_from_blocked_task(&info, p);
	do {
		if (p->state == TASK_RUNNING)
			return 0;
		if (unw_unwind(&info) < 0)
			return 0;
		unw_get_ip(&info, &ip);
		if (!in_sched_functions(ip))
			return ip;
	} while (count++ < 16);
	return 0;
}