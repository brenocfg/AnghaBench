#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ mach_port_mscount_t ;
typedef  TYPE_1__* ipc_port_t ;
struct TYPE_9__ {scalar_t__ ip_mscount; scalar_t__ ip_srights; struct TYPE_9__* ip_nsrequest; } ;

/* Variables and functions */
 TYPE_1__* IP_NULL ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_active (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  ipc_notify_no_senders (TYPE_1__*,scalar_t__) ; 

void
ipc_port_nsrequest(
	ipc_port_t		port,
	mach_port_mscount_t	sync,
	ipc_port_t		notify,
	ipc_port_t		*previousp)
{
	ipc_port_t previous;
	mach_port_mscount_t mscount;

	assert(ip_active(port));

	previous = port->ip_nsrequest;
	mscount = port->ip_mscount;

	if ((port->ip_srights == 0) && (sync <= mscount) &&
	    (notify != IP_NULL)) {
		port->ip_nsrequest = IP_NULL;
		ip_unlock(port);
		ipc_notify_no_senders(notify, mscount);
	} else {
		port->ip_nsrequest = notify;
		ip_unlock(port);
	}

	*previousp = previous;
}