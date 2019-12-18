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
struct kernel_ipmi_msg {int netfn; scalar_t__ data_len; int /*<<< orphan*/ * data; int /*<<< orphan*/  cmd; } ;
struct ipmi_system_interface_addr {scalar_t__ lun; int /*<<< orphan*/  channel; int /*<<< orphan*/  addr_type; } ;
struct ipmi_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPMI_BMC_CHANNEL ; 
 int /*<<< orphan*/  IPMI_SYSTEM_INTERFACE_ADDR_TYPE ; 
 int /*<<< orphan*/  IPMI_WDOG_RESET_TIMER ; 
 scalar_t__ WDOG_TIMEOUT_NONE ; 
 int /*<<< orphan*/  atomic_add (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_sub (int,int /*<<< orphan*/ *) ; 
 int ipmi_request_supply_msgs (int /*<<< orphan*/ ,struct ipmi_addr*,int /*<<< orphan*/ ,struct kernel_ipmi_msg*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ipmi_watchdog_state ; 
 int /*<<< orphan*/  panic_done_count ; 
 int /*<<< orphan*/  panic_halt_heartbeat_recv_msg ; 
 int /*<<< orphan*/  panic_halt_heartbeat_smi_msg ; 
 int /*<<< orphan*/  watchdog_user ; 

__attribute__((used)) static void panic_halt_ipmi_heartbeat(void)
{
	struct kernel_ipmi_msg             msg;
	struct ipmi_system_interface_addr addr;
	int rv;

	/*
	 * Don't reset the timer if we have the timer turned off, that
	 * re-enables the watchdog.
	 */
	if (ipmi_watchdog_state == WDOG_TIMEOUT_NONE)
		return;

	addr.addr_type = IPMI_SYSTEM_INTERFACE_ADDR_TYPE;
	addr.channel = IPMI_BMC_CHANNEL;
	addr.lun = 0;

	msg.netfn = 0x06;
	msg.cmd = IPMI_WDOG_RESET_TIMER;
	msg.data = NULL;
	msg.data_len = 0;
	atomic_add(2, &panic_done_count);
	rv = ipmi_request_supply_msgs(watchdog_user,
				      (struct ipmi_addr *) &addr,
				      0,
				      &msg,
				      NULL,
				      &panic_halt_heartbeat_smi_msg,
				      &panic_halt_heartbeat_recv_msg,
				      1);
	if (rv)
		atomic_sub(2, &panic_done_count);
}