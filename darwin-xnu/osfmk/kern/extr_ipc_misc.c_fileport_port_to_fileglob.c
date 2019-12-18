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
struct fileglob {int dummy; } ;
typedef  TYPE_1__* ipc_port_t ;
struct TYPE_8__ {scalar_t__ ip_kobject; } ;

/* Variables and functions */
 scalar_t__ IKOT_FILEPORT ; 
 int /*<<< orphan*/  IP_VALID (TYPE_1__*) ; 
 scalar_t__ ip_active (TYPE_1__*) ; 
 scalar_t__ ip_kotype (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_unlock (TYPE_1__*) ; 

struct fileglob *
fileport_port_to_fileglob(ipc_port_t port)
{
	struct fileglob *fg = NULL;

	if (!IP_VALID(port))
		return NULL;

	ip_lock(port);
	if (ip_active(port) && IKOT_FILEPORT == ip_kotype(port))
		fg = (void *)port->ip_kobject;
	ip_unlock(port);

	return fg;
}