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
struct ftrace_ops {int dummy; } ;

/* Variables and functions */
 int __register_ftrace_function (struct ftrace_ops*) ; 
 int /*<<< orphan*/  ftrace_disabled ; 
 int /*<<< orphan*/  ftrace_lock ; 
 int ftrace_startup (struct ftrace_ops*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int register_ftrace_function(struct ftrace_ops *ops)
{
	int ret = -1;

	mutex_lock(&ftrace_lock);

	if (unlikely(ftrace_disabled))
		goto out_unlock;

	ret = __register_ftrace_function(ops);
	if (!ret)
		ret = ftrace_startup(ops, 0);


 out_unlock:
	mutex_unlock(&ftrace_lock);
	return ret;
}