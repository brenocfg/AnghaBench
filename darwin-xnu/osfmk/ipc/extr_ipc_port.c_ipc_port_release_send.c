#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mach_port_mscount_t ;
typedef  TYPE_1__* ipc_port_t ;
struct TYPE_10__ {scalar_t__ ip_srights; scalar_t__ ip_nsrequest; int /*<<< orphan*/  ip_mscount; } ;

/* Variables and functions */
 scalar_t__ IP_NULL ; 
 int /*<<< orphan*/  IP_VALID (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ip_active (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_release (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  ipc_notify_no_senders (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,TYPE_1__*) ; 

void
ipc_port_release_send(
	ipc_port_t	port)
{
	ipc_port_t nsrequest = IP_NULL;
	mach_port_mscount_t mscount;

	if (!IP_VALID(port))
		return;

	ip_lock(port);

	assert(port->ip_srights > 0);
	if (port->ip_srights == 0) {
		panic("Over-release of port %p send right!", port);
	}

	port->ip_srights--;

	if (!ip_active(port)) {
		ip_unlock(port);
		ip_release(port);
		return;
	}

	if (port->ip_srights == 0 &&
	    port->ip_nsrequest != IP_NULL) {
		nsrequest = port->ip_nsrequest;
		port->ip_nsrequest = IP_NULL;
		mscount = port->ip_mscount;
		ip_unlock(port);
		ip_release(port);
		ipc_notify_no_senders(nsrequest, mscount);
	} else {
		ip_unlock(port);
		ip_release(port);
	}
}