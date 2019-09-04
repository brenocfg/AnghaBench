#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ semaphore_t ;
struct TYPE_6__ {TYPE_3__* msgh_remote_port; } ;
struct TYPE_7__ {TYPE_1__ not_header; } ;
typedef  TYPE_2__ mach_no_senders_notification_t ;
typedef  int /*<<< orphan*/  mach_msg_header_t ;
typedef  TYPE_3__* ipc_port_t ;
struct TYPE_8__ {scalar_t__ ip_kobject; } ;

/* Variables and functions */
 scalar_t__ IKOT_SEMAPHORE ; 
 int /*<<< orphan*/  assert (int) ; 
 int ip_active (TYPE_3__*) ; 
 scalar_t__ ip_kotype (TYPE_3__*) ; 
 int /*<<< orphan*/  semaphore_dereference (scalar_t__) ; 

void
semaphore_notify(mach_msg_header_t *msg)
{
	mach_no_senders_notification_t *notification = (void *)msg;
	ipc_port_t port = notification->not_header.msgh_remote_port;
	semaphore_t semaphore;

	assert(ip_active(port));
	assert(IKOT_SEMAPHORE == ip_kotype(port));
	semaphore = (semaphore_t)port->ip_kobject;

	semaphore_dereference(semaphore);
}