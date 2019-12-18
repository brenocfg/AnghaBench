#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  task_t ;
typedef  scalar_t__ task_inspect_t ;
typedef  TYPE_1__* ipc_port_t ;
struct TYPE_8__ {scalar_t__ ip_kobject; } ;

/* Variables and functions */
 scalar_t__ IKOT_TASK ; 
 scalar_t__ IP_VALID (TYPE_1__*) ; 
 scalar_t__ TASK_INSPECT_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ip_active (TYPE_1__*) ; 
 scalar_t__ ip_kotype (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_pause (int) ; 
 scalar_t__ task_lock_try (int /*<<< orphan*/ ) ; 

task_inspect_t
convert_port_to_locked_task_inspect(ipc_port_t port)
{
        int try_failed_count = 0;

	while (IP_VALID(port)) {
		task_inspect_t task;

		ip_lock(port);
		if (!ip_active(port) || (ip_kotype(port) != IKOT_TASK)) {
			ip_unlock(port);
			return TASK_INSPECT_NULL;
		}
		task = (task_inspect_t)port->ip_kobject;
		assert(task != TASK_INSPECT_NULL);
		/*
		 * Normal lock ordering puts task_lock() before ip_lock().
		 * Attempt out-of-order locking here.
		 */
		if (task_lock_try((task_t)task)) {
			ip_unlock(port);
			return task;
		}
		try_failed_count++;

		ip_unlock(port);
		mutex_pause(try_failed_count);
	}
	return TASK_INSPECT_NULL;
}