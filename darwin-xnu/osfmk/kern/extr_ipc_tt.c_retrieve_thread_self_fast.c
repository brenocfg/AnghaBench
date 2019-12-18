#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
typedef  TYPE_2__* ipc_port_t ;
struct TYPE_15__ {int /*<<< orphan*/  ip_srights; } ;
struct TYPE_14__ {scalar_t__ ith_self; TYPE_2__* ith_sself; } ;

/* Variables and functions */
 scalar_t__ IP_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* current_thread () ; 
 int ip_active (TYPE_2__*) ; 
 int /*<<< orphan*/  ip_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  ip_reference (TYPE_2__*) ; 
 int /*<<< orphan*/  ip_unlock (TYPE_2__*) ; 
 TYPE_2__* ipc_port_copy_send (TYPE_2__*) ; 
 int /*<<< orphan*/  thread_mtx_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_mtx_unlock (TYPE_1__*) ; 

ipc_port_t
retrieve_thread_self_fast(
	thread_t		thread)
{
	ipc_port_t port;

	assert(thread == current_thread());

	thread_mtx_lock(thread);

	assert(thread->ith_self != IP_NULL);

	if ((port = thread->ith_sself) == thread->ith_self) {
		/* no interposing */

		ip_lock(port);
		assert(ip_active(port));
		ip_reference(port);
		port->ip_srights++;
		ip_unlock(port);
	}
	else
		port = ipc_port_copy_send(port);

	thread_mtx_unlock(thread);

	return port;
}