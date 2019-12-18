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
struct ftrace_ops {struct ftrace_ops* next; } ;

/* Variables and functions */
 struct ftrace_ops ftrace_list_end ; 

__attribute__((used)) static int remove_ftrace_ops(struct ftrace_ops **list, struct ftrace_ops *ops)
{
	struct ftrace_ops **p;

	/*
	 * If we are removing the last function, then simply point
	 * to the ftrace_stub.
	 */
	if (*list == ops && ops->next == &ftrace_list_end) {
		*list = &ftrace_list_end;
		return 0;
	}

	for (p = list; *p != &ftrace_list_end; p = &(*p)->next)
		if (*p == ops)
			break;

	if (*p != ops)
		return -1;

	*p = (*p)->next;
	return 0;
}