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
struct utrace_engine_ops {int dummy; } ;
struct utrace_engine {int dummy; } ;
struct task_struct {int dummy; } ;
struct pid {int dummy; } ;

/* Variables and functions */
 struct utrace_engine* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESRCH ; 
 int /*<<< orphan*/  PIDTYPE_PID ; 
 struct task_struct* get_pid_task (struct pid*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 struct utrace_engine* utrace_attach_task (struct task_struct*,int,struct utrace_engine_ops const*,void*) ; 

struct utrace_engine *utrace_attach_pid(
	struct pid *pid, int flags,
	const struct utrace_engine_ops *ops, void *data)
{
	struct utrace_engine *engine = ERR_PTR(-ESRCH);
	struct task_struct *task = get_pid_task(pid, PIDTYPE_PID);
	if (task) {
		engine = utrace_attach_task(task, flags, ops, data);
		put_task_struct(task);
	}
	return engine;
}