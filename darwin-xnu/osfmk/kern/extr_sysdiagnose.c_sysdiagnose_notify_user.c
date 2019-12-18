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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  mach_port_t ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 int DBG_FUNC_START ; 
 int /*<<< orphan*/  DBG_MACH_SYSDIAGNOSE ; 
 int /*<<< orphan*/  IPC_PORT_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ KERN_SUCCESS ; 
 int MACHDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYSDIAGNOSE_NOTIFY_USER ; 
 scalar_t__ host_get_sysdiagnose_port (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  host_priv_self () ; 
 int /*<<< orphan*/  ipc_port_release_send (int /*<<< orphan*/ ) ; 
 scalar_t__ send_sysdiagnose_notification (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t
sysdiagnose_notify_user(uint32_t keycode)
{
	mach_port_t user_port;
	kern_return_t kr;

	kr = host_get_sysdiagnose_port(host_priv_self(), &user_port);
	if ((kr != KERN_SUCCESS) || !IPC_PORT_VALID(user_port)) {
		return kr;
	}

	KERNEL_DEBUG_CONSTANT(MACHDBG_CODE(DBG_MACH_SYSDIAGNOSE, SYSDIAGNOSE_NOTIFY_USER) | DBG_FUNC_START, 0, 0, 0, 0, 0);

	kr = send_sysdiagnose_notification(user_port, keycode);
	ipc_port_release_send(user_port);
	return kr;
}