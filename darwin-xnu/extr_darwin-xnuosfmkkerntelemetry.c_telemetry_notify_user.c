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
typedef  int /*<<< orphan*/  mach_port_t ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  IPC_PORT_VALID (int /*<<< orphan*/ ) ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  MACH_PORT_NULL ; 
 scalar_t__ host_get_telemetry_port (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  host_priv_self () ; 
 int /*<<< orphan*/  ipc_port_release_send (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  telemetry_notification (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
telemetry_notify_user(void)
{
	mach_port_t user_port = MACH_PORT_NULL;

	kern_return_t kr = host_get_telemetry_port(host_priv_self(), &user_port);
	if ((kr != KERN_SUCCESS) || !IPC_PORT_VALID(user_port)) {
		return;
	}

	telemetry_notification(user_port, 0);
	ipc_port_release_send(user_port);
}