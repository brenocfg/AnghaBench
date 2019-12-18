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
typedef  TYPE_1__* task_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  scalar_t__ kern_return_t ;
typedef  scalar_t__ ipc_port_t ;
typedef  int /*<<< orphan*/  ipc_object_t ;
typedef  int /*<<< orphan*/  ipc_kobject_type_t ;
typedef  int /*<<< orphan*/ * io_object_t ;
struct TYPE_3__ {int /*<<< orphan*/  itk_space; } ;

/* Variables and functions */
 scalar_t__ IP_DEAD ; 
 scalar_t__ IP_NULL ; 
 scalar_t__ IP_VALID (scalar_t__) ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  MACH_MSG_TYPE_PORT_SEND ; 
 int /*<<< orphan*/  MACH_PORT_DEAD ; 
 int /*<<< orphan*/  MACH_PORT_NULL ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ iokit_port_for_object (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iokit_release_port (scalar_t__) ; 
 scalar_t__ ipc_object_copyout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ipc_port_make_send (scalar_t__) ; 
 int /*<<< orphan*/  ipc_port_release_send (scalar_t__) ; 

mach_port_name_t
iokit_make_send_right( task_t task, io_object_t obj, ipc_kobject_type_t type )
{
    ipc_port_t		port;
    ipc_port_t		sendPort;
    mach_port_name_t	name = 0;

    if( obj == NULL)
        return MACH_PORT_NULL;

    port = iokit_port_for_object( obj, type );
    if( port) {
	sendPort = ipc_port_make_send( port);
	iokit_release_port( port );
    } else
	sendPort = IP_NULL;

    if (IP_VALID( sendPort )) {
    	kern_return_t	kr;
    	kr = ipc_object_copyout( task->itk_space, (ipc_object_t) sendPort,
				MACH_MSG_TYPE_PORT_SEND, TRUE, &name);
	if ( kr != KERN_SUCCESS) {
	    ipc_port_release_send( sendPort );
	    name = MACH_PORT_NULL;
	}
    } else if ( sendPort == IP_NULL)
        name = MACH_PORT_NULL;
    else if ( sendPort == IP_DEAD)
    	name = MACH_PORT_DEAD;

    return( name );
}