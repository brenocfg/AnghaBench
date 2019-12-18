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
typedef  scalar_t__ mach_port_name_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  ipc_space_t ;
typedef  TYPE_1__* ipc_port_t ;
typedef  int /*<<< orphan*/  ipc_object_t ;
typedef  scalar_t__ ipc_kobject_type_t ;
typedef  int /*<<< orphan*/ * io_object_t ;
struct TYPE_10__ {scalar_t__ ip_kobject; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP_VALID (TYPE_1__*) ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  MACH_PORT_RIGHT_SEND ; 
 scalar_t__ MACH_PORT_VALID (scalar_t__) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iokit_add_reference (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  iokit_lock_port (TYPE_1__*) ; 
 int /*<<< orphan*/  iokit_unlock_port (TYPE_1__*) ; 
 scalar_t__ ip_active (TYPE_1__*) ; 
 scalar_t__ ip_kotype (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_reference (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_release (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_unlock (TYPE_1__*) ; 
 scalar_t__ ipc_object_translate (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static io_object_t
iokit_lookup_object_in_space_with_port_name(mach_port_name_t name, ipc_kobject_type_t type, ipc_space_t space)
{
	io_object_t obj = NULL;

	if (name && MACH_PORT_VALID(name)) {
		ipc_port_t port;
		kern_return_t kr;

		kr = ipc_object_translate(space, name, MACH_PORT_RIGHT_SEND, (ipc_object_t *)&port);

		if (kr == KERN_SUCCESS) {
			assert(IP_VALID(port));

			ip_reference(port);
			ip_unlock(port);

			iokit_lock_port(port);
			if (ip_active(port) && (ip_kotype(port) == type)) {
				obj = (io_object_t) port->ip_kobject;
				iokit_add_reference(obj, type);
			}
			iokit_unlock_port(port);

			ip_release(port);
		}
	}

	return obj;
}