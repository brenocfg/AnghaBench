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
typedef  scalar_t__ task_suspension_token_t ;
typedef  TYPE_1__* ipc_port_t ;
struct TYPE_8__ {scalar_t__ ip_kobject; } ;

/* Variables and functions */
 scalar_t__ IKOT_TASK_RESUME ; 
 scalar_t__ IP_VALID (TYPE_1__*) ; 
 scalar_t__ TASK_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ip_active (TYPE_1__*) ; 
 scalar_t__ ip_kotype (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  task_reference_internal (scalar_t__) ; 

task_suspension_token_t
convert_port_to_task_suspension_token(
	ipc_port_t		port)
{
	task_suspension_token_t		task = TASK_NULL;

	if (IP_VALID(port)) {
		ip_lock(port);

		if (	ip_active(port)					&&
				ip_kotype(port) == IKOT_TASK_RESUME) {
			task = (task_suspension_token_t)port->ip_kobject;
			assert(task != TASK_NULL);

			task_reference_internal(task);
		}

		ip_unlock(port);
	}

	return (task);
}