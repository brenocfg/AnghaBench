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
struct ftrace_ops {struct ftrace_ops* next; int /*<<< orphan*/  (* func ) (unsigned long,unsigned long) ;} ;

/* Variables and functions */
 struct ftrace_ops ftrace_list_end ; 
 struct ftrace_ops* ftrace_ops_list ; 
 scalar_t__ ftrace_ops_test (struct ftrace_ops*,unsigned long) ; 
 int /*<<< orphan*/  preempt_disable_notrace () ; 
 int /*<<< orphan*/  preempt_enable_notrace () ; 
 int /*<<< orphan*/  read_barrier_depends () ; 
 int /*<<< orphan*/  stub1 (unsigned long,unsigned long) ; 

__attribute__((used)) static void
ftrace_ops_list_func(unsigned long ip, unsigned long parent_ip)
{
	struct ftrace_ops *op;

	/*
	 * Some of the ops may be dynamically allocated,
	 * they must be freed after a synchronize_sched().
	 */
	preempt_disable_notrace();
	op = ftrace_ops_list;
	read_barrier_depends();
	while (op != &ftrace_list_end) {
		if (ftrace_ops_test(op, ip))
			op->func(ip, parent_ip);
		op = op->next;
		read_barrier_depends();
	};
	preempt_enable_notrace();
}