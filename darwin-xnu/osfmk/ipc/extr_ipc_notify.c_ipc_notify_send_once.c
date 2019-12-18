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
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IPC_PORT_ADJUST_SR_NONE ; 
 int /*<<< orphan*/  ipc_port_adjust_special_reply_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mach_notify_send_once (int /*<<< orphan*/ ) ; 

void
ipc_notify_send_once(
	ipc_port_t	port)
{
	ipc_port_adjust_special_reply_port(port, IPC_PORT_ADJUST_SR_NONE, FALSE);

	(void)mach_notify_send_once(port);
	/* send-once right consumed */
}