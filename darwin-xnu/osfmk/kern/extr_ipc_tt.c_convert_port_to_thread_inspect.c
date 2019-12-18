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
typedef  int /*<<< orphan*/  thread_t ;
typedef  scalar_t__ thread_inspect_t ;
typedef  TYPE_1__* ipc_port_t ;
struct TYPE_8__ {scalar_t__ ip_kobject; } ;

/* Variables and functions */
 scalar_t__ IKOT_THREAD ; 
 scalar_t__ IP_VALID (TYPE_1__*) ; 
 scalar_t__ THREAD_INSPECT_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ip_active (TYPE_1__*) ; 
 scalar_t__ ip_kotype (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_reference_internal (int /*<<< orphan*/ ) ; 

thread_inspect_t
convert_port_to_thread_inspect(
	ipc_port_t		port)
{
	thread_inspect_t thread = THREAD_INSPECT_NULL;

	if (IP_VALID(port)) {
		ip_lock(port);

		if (ip_active(port) &&
		    ip_kotype(port) == IKOT_THREAD) {
			thread = (thread_inspect_t)port->ip_kobject;
			assert(thread != THREAD_INSPECT_NULL);
			thread_reference_internal((thread_t)thread);
		}
		ip_unlock(port);
	}

	return thread;
}