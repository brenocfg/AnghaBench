#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct fileglob {int dummy; } ;
struct TYPE_10__ {TYPE_3__* msgh_remote_port; } ;
struct TYPE_11__ {TYPE_1__ not_header; } ;
typedef  TYPE_2__ mach_no_senders_notification_t ;
typedef  int /*<<< orphan*/  mach_msg_header_t ;
typedef  TYPE_3__* ipc_port_t ;
struct TYPE_12__ {scalar_t__ ip_srights; scalar_t__ ip_kobject; } ;

/* Variables and functions */
 scalar_t__ IKOT_FILEPORT ; 
 int /*<<< orphan*/  IP_VALID (TYPE_3__*) ; 
 int /*<<< orphan*/  fileport_releasefg (struct fileglob*) ; 
 int /*<<< orphan*/  ip_active (TYPE_3__*) ; 
 scalar_t__ ip_kotype (TYPE_3__*) ; 
 int /*<<< orphan*/  ip_lock (TYPE_3__*) ; 
 int /*<<< orphan*/  ip_unlock (TYPE_3__*) ; 
 int /*<<< orphan*/  ipc_port_dealloc_kernel (TYPE_3__*) ; 
 int /*<<< orphan*/  panic (char*) ; 

void
fileport_notify(mach_msg_header_t *msg)
{
	mach_no_senders_notification_t *notification = (void *)msg;
	ipc_port_t port = notification->not_header.msgh_remote_port;
	struct fileglob *fg = NULL;

	if (!IP_VALID(port))
		panic("Invalid port passed to fileport_notify()\n");

	ip_lock(port);

	fg = (struct fileglob *)port->ip_kobject;

	if (!ip_active(port)) 
		panic("Inactive port passed to fileport_notify()\n");
	if (ip_kotype(port) != IKOT_FILEPORT) 
		panic("Port of type other than IKOT_FILEPORT passed to fileport_notify()\n");
	if (fg == NULL) 
		panic("fileport without an assocated fileglob\n");

	if (port->ip_srights == 0) {
		ip_unlock(port);

		fileport_releasefg(fg);
		ipc_port_dealloc_kernel(port);
	} else {
		ip_unlock(port);
	}
}