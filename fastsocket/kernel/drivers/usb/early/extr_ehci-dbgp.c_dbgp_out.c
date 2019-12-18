#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  pids; int /*<<< orphan*/  address; int /*<<< orphan*/  control; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGP_GO ; 
 int /*<<< orphan*/  DBGP_OUT ; 
 int /*<<< orphan*/  USB_PID_OUT ; 
 int /*<<< orphan*/  dbgp_len_update (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dbgp_pid_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbgp_set_data (char const*,int) ; 
 int dbgp_wait_until_done (int /*<<< orphan*/ ) ; 
 TYPE_1__* ehci_debug ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dbgp_out(u32 addr, const char *bytes, int size)
{
	u32 pids, ctrl;

	pids = readl(&ehci_debug->pids);
	pids = dbgp_pid_update(pids, USB_PID_OUT);

	ctrl = readl(&ehci_debug->control);
	ctrl = dbgp_len_update(ctrl, size);
	ctrl |= DBGP_OUT;
	ctrl |= DBGP_GO;

	dbgp_set_data(bytes, size);
	writel(addr, &ehci_debug->address);
	writel(pids, &ehci_debug->pids);
	return dbgp_wait_until_done(ctrl);
}