#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ipc_port_t ;
typedef  int ipc_kobject_type_t ;
typedef  int /*<<< orphan*/  ipc_kobject_t ;
struct TYPE_4__ {int ip_bits; int /*<<< orphan*/  ip_kobject; } ;

/* Variables and functions */
 int IKOT_NONE ; 
 int IO_BITS_KOTYPE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ip_active (TYPE_1__*) ; 

void
ipc_kobject_set_atomically(
	ipc_port_t			port,
	ipc_kobject_t		kobject,
	ipc_kobject_type_t	type)
{
	assert(type == IKOT_NONE || ip_active(port));
#if	MACH_ASSERT
	port->ip_spares[2] = (port->ip_bits & IO_BITS_KOTYPE);
#endif	/* MACH_ASSERT */
	port->ip_bits = (port->ip_bits &~ IO_BITS_KOTYPE) | type;
	port->ip_kobject = kobject;
}