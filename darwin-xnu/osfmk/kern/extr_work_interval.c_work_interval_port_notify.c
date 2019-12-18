#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct work_interval {int /*<<< orphan*/  wi_port; } ;
struct TYPE_11__ {TYPE_3__* msgh_remote_port; } ;
struct TYPE_12__ {scalar_t__ not_count; TYPE_1__ not_header; } ;
typedef  TYPE_2__ mach_no_senders_notification_t ;
typedef  int /*<<< orphan*/  mach_msg_header_t ;
typedef  TYPE_3__* ipc_port_t ;
struct TYPE_13__ {scalar_t__ ip_mscount; scalar_t__ ip_srights; scalar_t__ ip_kobject; } ;

/* Variables and functions */
 int /*<<< orphan*/  IKOT_NONE ; 
 scalar_t__ IKOT_WORK_INTERVAL ; 
 int /*<<< orphan*/  IKO_NULL ; 
 int /*<<< orphan*/  IP_VALID (TYPE_3__*) ; 
 int /*<<< orphan*/  MACH_PORT_NULL ; 
 int /*<<< orphan*/  ip_active (TYPE_3__*) ; 
 scalar_t__ ip_kotype (TYPE_3__*) ; 
 int /*<<< orphan*/  ip_lock (TYPE_3__*) ; 
 int /*<<< orphan*/  ip_unlock (TYPE_3__*) ; 
 int /*<<< orphan*/  ipc_kobject_set_atomically (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_port_dealloc_kernel (TYPE_3__*) ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 int /*<<< orphan*/  wi_release (struct work_interval*) ; 

void
work_interval_port_notify(mach_msg_header_t *msg)
{
	mach_no_senders_notification_t *notification = (void *)msg;
	ipc_port_t port = notification->not_header.msgh_remote_port;
	struct work_interval *work_interval = NULL;

	if (!IP_VALID(port))
		panic("work_interval_port_notify(): invalid port");

	ip_lock(port);

	if (!ip_active(port))
		panic("work_interval_port_notify(): inactive port %p", port);

	if (ip_kotype(port) != IKOT_WORK_INTERVAL)
		panic("work_interval_port_notify(): not the right kobject: %p, %d\n",
		      port, ip_kotype(port));

	if (port->ip_mscount != notification->not_count)
		panic("work_interval_port_notify(): unexpected make-send count: %p, %d, %d",
		      port, port->ip_mscount, notification->not_count);

	if (port->ip_srights != 0)
		panic("work_interval_port_notify(): unexpected send right count: %p, %d",
		      port, port->ip_srights);

	work_interval = (struct work_interval *)port->ip_kobject;

	if (work_interval == NULL)
		panic("work_interval_port_notify(): missing kobject: %p", port);

	ipc_kobject_set_atomically(port, IKO_NULL, IKOT_NONE);

	work_interval->wi_port = MACH_PORT_NULL;

	ip_unlock(port);

	ipc_port_dealloc_kernel(port);
	wi_release(work_interval);
}