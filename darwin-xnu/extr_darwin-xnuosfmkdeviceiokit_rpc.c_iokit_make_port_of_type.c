#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ ipc_port_t ;
typedef  int /*<<< orphan*/  ipc_kobject_type_t ;
typedef  int /*<<< orphan*/ * io_object_t ;

/* Variables and functions */
 scalar_t__ IP_NULL ; 
 scalar_t__ iokit_port_for_object (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iokit_release_port (scalar_t__) ; 
 int /*<<< orphan*/  iokit_remove_reference (int /*<<< orphan*/ *) ; 
 scalar_t__ ipc_port_make_send (scalar_t__) ; 

__attribute__((used)) static ipc_port_t
iokit_make_port_of_type(io_object_t obj, ipc_kobject_type_t type)
{
    ipc_port_t	port;
    ipc_port_t	sendPort;

    if( obj == NULL)
        return IP_NULL;

    port = iokit_port_for_object( obj, type );
    if( port) {
	sendPort = ipc_port_make_send( port);
	iokit_release_port( port );
    } else
	sendPort = IP_NULL;

    iokit_remove_reference( obj );

    return( sendPort);
}