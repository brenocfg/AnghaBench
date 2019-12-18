#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  TYPE_1__* ipc_port_t ;
struct TYPE_3__ {scalar_t__ ip_in_pset; int /*<<< orphan*/  ip_messages; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_NOT_IN_SET ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  ipc_mqueue_remove_from_all (int /*<<< orphan*/ *) ; 

kern_return_t
ipc_pset_remove_from_all(
	ipc_port_t	port)
{
	if (port->ip_in_pset == 0)
		return KERN_NOT_IN_SET;

	/* 
	 * Remove the port's mqueue from all sets
	 */
	ipc_mqueue_remove_from_all(&port->ip_messages);
	return KERN_SUCCESS;
}