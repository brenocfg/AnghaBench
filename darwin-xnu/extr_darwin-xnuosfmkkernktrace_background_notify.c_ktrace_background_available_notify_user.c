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
 scalar_t__ KERN_FAILURE ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ host_get_ktrace_background_port (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  host_priv_self () ; 
 int /*<<< orphan*/  ipc_port_release_send (int /*<<< orphan*/ ) ; 
 scalar_t__ send_ktrace_background_available (int /*<<< orphan*/ ) ; 

kern_return_t
ktrace_background_available_notify_user(void)
{
	mach_port_t user_port;
	kern_return_t kr;

	kr = host_get_ktrace_background_port(host_priv_self(), &user_port);
	if (kr != KERN_SUCCESS || !IPC_PORT_VALID(user_port)) {
		return KERN_FAILURE;
	}

	kr = send_ktrace_background_available(user_port);
	ipc_port_release_send(user_port);
	return kr;
}