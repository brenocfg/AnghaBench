#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  TYPE_1__* ipc_pset_t ;
typedef  TYPE_2__* ipc_port_t ;
struct TYPE_7__ {scalar_t__ ip_in_pset; int /*<<< orphan*/  ip_messages; } ;
struct TYPE_6__ {int /*<<< orphan*/  ips_messages; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_NOT_IN_SET ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_active (TYPE_2__*) ; 
 int /*<<< orphan*/  ipc_mqueue_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

kern_return_t
ipc_pset_remove(
	ipc_pset_t	  pset,
	ipc_port_t	  port)
{
	kern_return_t kr;

	assert(ip_active(port));
	
	if (port->ip_in_pset == 0)
		return KERN_NOT_IN_SET;

	kr = ipc_mqueue_remove(&port->ip_messages, &pset->ips_messages);

	return kr;
}