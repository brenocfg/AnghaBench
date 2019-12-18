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
struct task_struct {int dummy; } ;
typedef  void pid_namespace ;

/* Variables and functions */
 void* get_pid_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  task_active_pid_ns (struct task_struct*) ; 

__attribute__((used)) static void *pidns_get(struct task_struct *task)
{
	struct pid_namespace *ns;

	rcu_read_lock();
	ns = get_pid_ns(task_active_pid_ns(task));
	rcu_read_unlock();

	return ns;
}