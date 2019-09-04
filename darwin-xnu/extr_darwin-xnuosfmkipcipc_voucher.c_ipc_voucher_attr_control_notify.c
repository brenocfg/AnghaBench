#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* msgh_remote_port; } ;
struct TYPE_9__ {scalar_t__ not_count; TYPE_1__ not_header; } ;
typedef  TYPE_2__ mach_no_senders_notification_t ;
typedef  int /*<<< orphan*/  mach_msg_header_t ;
typedef  scalar_t__ ipc_voucher_attr_control_t ;
typedef  TYPE_3__* ipc_port_t ;
struct TYPE_10__ {scalar_t__ ip_mscount; scalar_t__ ip_kobject; } ;

/* Variables and functions */
 scalar_t__ IKOT_VOUCHER_ATTR_CONTROL ; 
 int /*<<< orphan*/  assert (int) ; 
 int ip_active (TYPE_3__*) ; 
 scalar_t__ ip_kotype (TYPE_3__*) ; 
 int /*<<< orphan*/  ip_lock (TYPE_3__*) ; 
 int /*<<< orphan*/  ip_unlock (TYPE_3__*) ; 
 int /*<<< orphan*/  ivac_release (scalar_t__) ; 

void
ipc_voucher_attr_control_notify(mach_msg_header_t *msg)
{
	mach_no_senders_notification_t *notification = (void *)msg;
	ipc_port_t port = notification->not_header.msgh_remote_port;
	ipc_voucher_attr_control_t ivac;

	assert(IKOT_VOUCHER_ATTR_CONTROL == ip_kotype(port));
	ip_lock(port);
	assert(ip_active(port));

	/* if no new send rights, drop a control reference */
	if (port->ip_mscount == notification->not_count) {
		ivac = (ipc_voucher_attr_control_t)port->ip_kobject;
		ip_unlock(port);

		ivac_release(ivac);
	} else {
		ip_unlock(port);
	}
}