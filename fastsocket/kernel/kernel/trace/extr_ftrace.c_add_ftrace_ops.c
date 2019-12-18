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
 int /*<<< orphan*/  rcu_assign_pointer (struct ftrace_ops*,struct ftrace_ops*) ; 

__attribute__((used)) static void add_ftrace_ops(struct ftrace_ops **list, struct ftrace_ops *ops)
{
	ops->next = *list;
	/*
	 * We are entering ops into the list but another
	 * CPU might be walking that list. We need to make sure
	 * the ops->next pointer is valid before another CPU sees
	 * the ops pointer included into the list.
	 */
	rcu_assign_pointer(*list, ops);
}