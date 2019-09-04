#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ipc_port_t ;
typedef  scalar_t__ host_t ;
struct TYPE_6__ {scalar_t__ ip_kobject; } ;

/* Variables and functions */
 scalar_t__ HOST_NULL ; 
 scalar_t__ IKOT_HOST ; 
 scalar_t__ IKOT_HOST_PRIV ; 
 scalar_t__ IP_VALID (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_active (TYPE_1__*) ; 
 scalar_t__ ip_kotype (TYPE_1__*) ; 

host_t
convert_port_to_host(
	ipc_port_t	port)
{
	host_t host = HOST_NULL;

	if (IP_VALID(port)) {
		if (ip_kotype(port) == IKOT_HOST ||
		    ip_kotype(port) == IKOT_HOST_PRIV) {
			host = (host_t) port->ip_kobject;
			assert(ip_active(port));
		}
	}
	return host;
}