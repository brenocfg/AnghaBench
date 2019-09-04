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
typedef  TYPE_1__* ipc_port_t ;
struct TYPE_10__ {scalar_t__ ip_receiver_name; struct TYPE_10__* ip_destination; } ;

/* Variables and functions */
 TYPE_1__* IP_NULL ; 
 int /*<<< orphan*/  IP_VALID (TYPE_1__*) ; 
 scalar_t__ MACH_PORT_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 int ip_active (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_release (TYPE_1__*) ; 
 int /*<<< orphan*/  ipc_port_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  ipc_port_send_turnstile_complete (TYPE_1__*) ; 

void
ipc_port_release_receive(
	ipc_port_t	port)
{
	ipc_port_t dest;

	if (!IP_VALID(port))
		return;

	ip_lock(port);
	assert(ip_active(port));
	assert(port->ip_receiver_name == MACH_PORT_NULL);
	dest = port->ip_destination;

	ipc_port_destroy(port); /* consumes ref, unlocks */

	if (dest != IP_NULL) {
		ipc_port_send_turnstile_complete(dest);
		ip_release(dest);
	}
}