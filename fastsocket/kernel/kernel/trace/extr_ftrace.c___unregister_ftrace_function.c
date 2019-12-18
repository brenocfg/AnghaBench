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
struct ftrace_ops {int flags; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 int FTRACE_OPS_FL_DYNAMIC ; 
 int FTRACE_OPS_FL_ENABLED ; 
 int FTRACE_OPS_FL_GLOBAL ; 
 scalar_t__ FTRACE_WARN_ON (int) ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ ftrace_disabled ; 
 scalar_t__ ftrace_enabled ; 
 int /*<<< orphan*/ * ftrace_global_list ; 
 int /*<<< orphan*/  ftrace_list_end ; 
 int /*<<< orphan*/ * ftrace_ops_list ; 
 struct ftrace_ops global_ops ; 
 int remove_ftrace_ops (int /*<<< orphan*/ **,struct ftrace_ops*) ; 
 int /*<<< orphan*/  synchronize_sched () ; 
 int /*<<< orphan*/  update_ftrace_function () ; 

__attribute__((used)) static int __unregister_ftrace_function(struct ftrace_ops *ops)
{
	int ret;

	if (ftrace_disabled)
		return -ENODEV;

	if (WARN_ON(!(ops->flags & FTRACE_OPS_FL_ENABLED)))
		return -EBUSY;

	if (FTRACE_WARN_ON(ops == &global_ops))
		return -EINVAL;

	if (ops->flags & FTRACE_OPS_FL_GLOBAL) {
		ret = remove_ftrace_ops(&ftrace_global_list, ops);
		if (!ret && ftrace_global_list == &ftrace_list_end)
			ret = remove_ftrace_ops(&ftrace_ops_list, &global_ops);
		if (!ret)
			ops->flags &= ~FTRACE_OPS_FL_ENABLED;
	} else
		ret = remove_ftrace_ops(&ftrace_ops_list, ops);

	if (ret < 0)
		return ret;

	if (ftrace_enabled)
		update_ftrace_function();

	/*
	 * Dynamic ops may be freed, we must make sure that all
	 * callers are done before leaving this function.
	 */
	if (ops->flags & FTRACE_OPS_FL_DYNAMIC)
		synchronize_sched();

	return 0;
}