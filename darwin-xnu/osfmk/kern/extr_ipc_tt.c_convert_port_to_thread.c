#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
typedef  TYPE_2__* ipc_port_t ;
struct TYPE_13__ {scalar_t__ ip_kobject; } ;
struct TYPE_12__ {int /*<<< orphan*/  task; } ;

/* Variables and functions */
 scalar_t__ IKOT_THREAD ; 
 scalar_t__ IP_VALID (TYPE_2__*) ; 
 scalar_t__ KERN_SUCCESS ; 
 TYPE_1__* THREAD_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  current_task () ; 
 scalar_t__ ip_active (TYPE_2__*) ; 
 scalar_t__ ip_kotype (TYPE_2__*) ; 
 int /*<<< orphan*/  ip_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  ip_unlock (TYPE_2__*) ; 
 scalar_t__ task_conversion_eval (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_reference_internal (TYPE_1__*) ; 

thread_t
convert_port_to_thread(
	ipc_port_t		port)
{
	thread_t	thread = THREAD_NULL;

	if (IP_VALID(port)) {
		ip_lock(port);

		if (ip_active(port) &&
		    ip_kotype(port) == IKOT_THREAD) {
			thread = (thread_t)port->ip_kobject;
			assert(thread != THREAD_NULL);

			/* Use task conversion rules for thread control conversions */
			if (task_conversion_eval(current_task(), thread->task) != KERN_SUCCESS) {
				ip_unlock(port);
				return THREAD_NULL;
			}

			thread_reference_internal(thread);
		}

		ip_unlock(port);
	}

	return (thread);
}