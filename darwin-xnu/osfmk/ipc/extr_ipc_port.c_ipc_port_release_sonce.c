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
typedef  TYPE_1__* ipc_port_t ;
struct TYPE_9__ {scalar_t__ ip_sorights; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IPC_PORT_ADJUST_SR_NONE ; 
 int /*<<< orphan*/  IP_VALID (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ip_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_release (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  ipc_port_adjust_special_reply_port (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,TYPE_1__*) ; 

void
ipc_port_release_sonce(
	ipc_port_t	port)
{
	if (!IP_VALID(port))
		return;

	ipc_port_adjust_special_reply_port(port, IPC_PORT_ADJUST_SR_NONE, FALSE);

	ip_lock(port);

	assert(port->ip_sorights > 0);
	if (port->ip_sorights == 0) {
		panic("Over-release of port %p send-once right!", port);
	}

	port->ip_sorights--;

	ip_unlock(port);
	ip_release(port);
}