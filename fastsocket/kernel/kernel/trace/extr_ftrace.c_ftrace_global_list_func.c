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
 struct ftrace_ops* ftrace_global_list ; 
 struct ftrace_ops ftrace_list_end ; 
 int /*<<< orphan*/  read_barrier_depends () ; 
 int /*<<< orphan*/  stub1 (unsigned long,unsigned long) ; 

__attribute__((used)) static void ftrace_global_list_func(unsigned long ip,
				    unsigned long parent_ip)
{
	struct ftrace_ops *op = ftrace_global_list;

	/* in case someone actually ports this to alpha! */
	read_barrier_depends();

	while (op != &ftrace_list_end) {
		/* silly alpha */
		read_barrier_depends();
		op->func(ip, parent_ip);
		op = op->next;
	};
}