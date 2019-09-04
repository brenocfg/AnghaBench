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
typedef  int /*<<< orphan*/  ipc_port_t ;

/* Variables and functions */
#define  IKOT_HOST_NOTIFY 130 
#define  IKOT_NAMED_ENTRY 129 
#define  IKOT_TIMER 128 
 int /*<<< orphan*/  host_notify_port_destroy (int /*<<< orphan*/ ) ; 
 int ip_kotype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mach_destroy_memory_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mk_timer_port_destroy (int /*<<< orphan*/ ) ; 

void
ipc_kobject_destroy(
	ipc_port_t		port)
{
	switch (ip_kotype(port)) {

	case IKOT_TIMER:
		mk_timer_port_destroy(port);
		break;

	case IKOT_NAMED_ENTRY:
		mach_destroy_memory_entry(port);
		break;

	case IKOT_HOST_NOTIFY:
		host_notify_port_destroy(port);
		break;

	default:
		break;
	}
}