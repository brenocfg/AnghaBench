#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ mach_port_mscount_t ;
struct TYPE_20__ {scalar_t__ msgh_remote_port; } ;
struct TYPE_21__ {scalar_t__ not_count; TYPE_1__ not_header; } ;
typedef  TYPE_2__ mach_no_senders_notification_t ;
typedef  TYPE_3__* ipc_port_t ;
typedef  int /*<<< orphan*/  ipc_kobject_type_t ;
typedef  int /*<<< orphan*/ * io_object_t ;
struct TYPE_22__ {scalar_t__ ip_kobject; } ;

/* Variables and functions */
 int /*<<< orphan*/  IKOT_IOKIT_CONNECT ; 
 int /*<<< orphan*/  IKOT_IOKIT_IDENT ; 
 int /*<<< orphan*/  IKOT_IOKIT_OBJECT ; 
 int /*<<< orphan*/  IKOT_NONE ; 
 TYPE_3__* IP_NULL ; 
 scalar_t__ IP_VALID (TYPE_3__*) ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  iokit_add_reference (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ iokit_client_died (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  iokit_lock_port (TYPE_3__*) ; 
 int /*<<< orphan*/  iokit_remove_reference (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iokit_unlock_port (TYPE_3__*) ; 
 scalar_t__ ip_active (TYPE_3__*) ; 
 int /*<<< orphan*/  ip_kotype (TYPE_3__*) ; 
 int /*<<< orphan*/  ip_lock (TYPE_3__*) ; 
 int /*<<< orphan*/  ip_unlock (TYPE_3__*) ; 
 TYPE_3__* ipc_port_make_sonce_locked (TYPE_3__*) ; 
 int /*<<< orphan*/  ipc_port_nsrequest (TYPE_3__*,scalar_t__,TYPE_3__*,TYPE_3__**) ; 
 int /*<<< orphan*/  ipc_port_release_sonce (TYPE_3__*) ; 

__attribute__((used)) static void
iokit_no_senders( mach_no_senders_notification_t * notification )
{
    ipc_port_t		port;
    io_object_t		obj = NULL;
    ipc_kobject_type_t	type = IKOT_NONE;
    ipc_port_t		notify;

    port = (ipc_port_t) notification->not_header.msgh_remote_port;

    // convert a port to io_object_t.
    if( IP_VALID(port)) {
        iokit_lock_port(port);
        if( ip_active(port)) {
            obj = (io_object_t) port->ip_kobject;
	    type = ip_kotype( port );
            if( (IKOT_IOKIT_OBJECT  == type)
	     || (IKOT_IOKIT_CONNECT == type)
	     || (IKOT_IOKIT_IDENT   == type))
                iokit_add_reference( obj, IKOT_IOKIT_OBJECT );
            else
                obj = NULL;
	}
        iokit_unlock_port(port);

        if( obj ) {

	    mach_port_mscount_t mscount = notification->not_count;

            if( KERN_SUCCESS != iokit_client_died( obj, port, type, &mscount ))
	    {
		/* Re-request no-senders notifications on the port (if still active) */
		ip_lock(port);
		if (ip_active(port)) {
			notify = ipc_port_make_sonce_locked(port);
			ipc_port_nsrequest( port, mscount + 1, notify, &notify);
			/* port unlocked */
			if ( notify != IP_NULL)
				ipc_port_release_sonce(notify);
		} else {
			ip_unlock(port);
		}
	    }
            iokit_remove_reference( obj );
        }
    }
}