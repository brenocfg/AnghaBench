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
struct TYPE_10__ {int /*<<< orphan*/  ip_srights; int /*<<< orphan*/  ip_mscount; } ;

/* Variables and functions */
 TYPE_1__* IP_DEAD ; 
 int /*<<< orphan*/  IP_VALID (TYPE_1__*) ; 
 scalar_t__ ip_active (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_reference (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_unlock (TYPE_1__*) ; 

ipc_port_t
ipc_port_make_send(
	ipc_port_t	port)
{
	
	if (!IP_VALID(port))
		return port;

	ip_lock(port);
	if (ip_active(port)) {
		port->ip_mscount++;
		port->ip_srights++;
		ip_reference(port);
		ip_unlock(port);
		return port;
	}
	ip_unlock(port);
	return IP_DEAD;
}