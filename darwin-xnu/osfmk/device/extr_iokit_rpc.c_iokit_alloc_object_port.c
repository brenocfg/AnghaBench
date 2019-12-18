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
typedef  int /*<<< orphan*/  ipc_kobject_t ;
typedef  scalar_t__ io_object_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ IP_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  gIOKitPortCount ; 
 int /*<<< orphan*/  ip_lock (scalar_t__) ; 
 int /*<<< orphan*/  ipc_kobject_set (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ipc_port_alloc_kernel () ; 
 scalar_t__ ipc_port_make_sonce_locked (scalar_t__) ; 
 int /*<<< orphan*/  ipc_port_nsrequest (scalar_t__,int,scalar_t__,scalar_t__*) ; 

ipc_port_t
iokit_alloc_object_port( io_object_t obj, ipc_kobject_type_t type )
{
    ipc_port_t		notify;
    ipc_port_t		port;

    do {

	/* Allocate port, keeping a reference for it. */
        port = ipc_port_alloc_kernel();
        if( port == IP_NULL)
            continue;

        /* set kobject & type */
	ipc_kobject_set( port, (ipc_kobject_t) obj, type);

        /* Request no-senders notifications on the port. */
        ip_lock( port);
        notify = ipc_port_make_sonce_locked( port);
        ipc_port_nsrequest( port, 1, notify, &notify);
	/* port unlocked */
        assert( notify == IP_NULL);
	gIOKitPortCount++;

    } while( FALSE);

    return( port );
}