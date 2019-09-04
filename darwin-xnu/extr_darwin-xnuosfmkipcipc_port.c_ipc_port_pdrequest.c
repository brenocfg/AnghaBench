#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ipc_port_t ;
struct TYPE_7__ {struct TYPE_7__* ip_pdrequest; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_active (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_unlock (TYPE_1__*) ; 

void
ipc_port_pdrequest(
	ipc_port_t	port,
	ipc_port_t	notify,
	ipc_port_t	*previousp)
{
	ipc_port_t previous;

	assert(ip_active(port));

	previous = port->ip_pdrequest;
	port->ip_pdrequest = notify;
	ip_unlock(port);

	*previousp = previous;
}