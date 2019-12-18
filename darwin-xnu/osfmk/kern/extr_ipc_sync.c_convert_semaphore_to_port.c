#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* semaphore_t ;
typedef  TYPE_2__* ipc_port_t ;
typedef  scalar_t__ ipc_kobject_t ;
struct TYPE_25__ {scalar_t__ ip_kobject; int ip_srights; int /*<<< orphan*/  ip_mscount; struct TYPE_25__* ip_nsrequest; } ;
struct TYPE_24__ {TYPE_2__* port; } ;

/* Variables and functions */
 scalar_t__ IKOT_SEMAPHORE ; 
 TYPE_2__* IP_NULL ; 
 int IP_VALID (TYPE_2__*) ; 
 int /*<<< orphan*/  OSCompareAndSwapPtr (TYPE_2__*,TYPE_2__*,TYPE_2__**) ; 
 TYPE_1__* SEMAPHORE_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 int ip_active (TYPE_2__*) ; 
 scalar_t__ ip_kotype (TYPE_2__*) ; 
 int /*<<< orphan*/  ip_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  ip_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  ipc_kobject_set_atomically (TYPE_2__*,scalar_t__,scalar_t__) ; 
 TYPE_2__* ipc_port_alloc_kernel () ; 
 int /*<<< orphan*/  ipc_port_dealloc_kernel (TYPE_2__*) ; 
 TYPE_2__* ipc_port_make_send_locked (TYPE_2__*) ; 
 int /*<<< orphan*/  ipc_port_make_sonce_locked (TYPE_2__*) ; 
 int /*<<< orphan*/  ipc_port_nsrequest (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  semaphore_dereference (TYPE_1__*) ; 

ipc_port_t
convert_semaphore_to_port (semaphore_t semaphore)
{
	ipc_port_t port, send;

	if (semaphore == SEMAPHORE_NULL)
		return (IP_NULL);

	/* caller is donating a reference */
	port = semaphore->port;

	if (!IP_VALID(port)) {
		port = ipc_port_alloc_kernel();
		assert(IP_VALID(port));
		ipc_kobject_set_atomically(port, (ipc_kobject_t) semaphore, IKOT_SEMAPHORE);

		/* If we lose the race, deallocate and pick up the other guy's port */
		if (!OSCompareAndSwapPtr(IP_NULL, port, &semaphore->port)) {
			ipc_port_dealloc_kernel(port);
			port = semaphore->port;
			assert(ip_kotype(port) == IKOT_SEMAPHORE);
			assert(port->ip_kobject == (ipc_kobject_t)semaphore);
		}
	}

	ip_lock(port);
	assert(ip_active(port));
	send = ipc_port_make_send_locked(port);

	if (1 == port->ip_srights) {
		ipc_port_t old_notify;

		/* transfer our ref to the port, and arm the no-senders notification */
		assert(IP_NULL == port->ip_nsrequest);
		ipc_port_nsrequest(port, port->ip_mscount, ipc_port_make_sonce_locked(port), &old_notify);
		/* port unlocked */
		assert(IP_NULL == old_notify);
	} else {
		/* piggyback on the existing port reference, so consume ours */
		ip_unlock(port);
		semaphore_dereference(semaphore);
	}
	return (send);
}