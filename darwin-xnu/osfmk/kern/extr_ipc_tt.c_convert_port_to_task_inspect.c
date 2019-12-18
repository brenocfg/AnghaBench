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
typedef  scalar_t__ task_inspect_t ;
typedef  TYPE_1__* ipc_port_t ;
struct TYPE_8__ {scalar_t__ ip_kobject; } ;

/* Variables and functions */
 scalar_t__ IKOT_TASK ; 
 scalar_t__ IP_VALID (TYPE_1__*) ; 
 scalar_t__ TASK_INSPECT_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ip_active (TYPE_1__*) ; 
 scalar_t__ ip_kotype (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  task_reference_internal (scalar_t__) ; 

task_inspect_t
convert_port_to_task_inspect(
	ipc_port_t		port)
{
	task_inspect_t task = TASK_INSPECT_NULL;

	if (IP_VALID(port)) {
		ip_lock(port);

		if (ip_active(port)	&&
		    ip_kotype(port) == IKOT_TASK) {
			task = (task_inspect_t)port->ip_kobject;
			assert(task != TASK_INSPECT_NULL);

			task_reference_internal(task);
		}

		ip_unlock(port);
	}

	return (task);
}