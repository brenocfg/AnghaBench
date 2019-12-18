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
typedef  TYPE_1__* ipc_port_t ;
typedef  scalar_t__ ipc_kobject_type_t ;
typedef  int /*<<< orphan*/ * io_object_t ;
struct TYPE_8__ {scalar_t__ ip_kobject; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP_VALID (TYPE_1__*) ; 
 int /*<<< orphan*/  iokit_add_reference (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  iokit_lock_port (TYPE_1__*) ; 
 int /*<<< orphan*/  iokit_unlock_port (TYPE_1__*) ; 
 scalar_t__ ip_active (TYPE_1__*) ; 
 scalar_t__ ip_kotype (TYPE_1__*) ; 

__attribute__((used)) static io_object_t
iokit_lookup_io_object(ipc_port_t port, ipc_kobject_type_t type)
{
	io_object_t	obj;

	if (!IP_VALID(port))
	    return (NULL);

	iokit_lock_port(port);
	if (ip_active(port) && (ip_kotype(port) == type)) {
	    obj = (io_object_t) port->ip_kobject;
	    iokit_add_reference( obj, type );
	}
	else
	    obj = NULL;

	iokit_unlock_port(port);

	return( obj );
}