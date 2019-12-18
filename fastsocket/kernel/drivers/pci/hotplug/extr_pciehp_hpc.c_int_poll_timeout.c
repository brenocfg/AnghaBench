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
struct controller {int /*<<< orphan*/  poll_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcie_isr (int /*<<< orphan*/ ,struct controller*) ; 
 int pciehp_poll_time ; 
 int /*<<< orphan*/  start_int_poll_timer (struct controller*,int) ; 

__attribute__((used)) static void int_poll_timeout(unsigned long data)
{
	struct controller *ctrl = (struct controller *)data;

	/* Poll for interrupt events.  regs == NULL => polling */
	pcie_isr(0, ctrl);

	init_timer(&ctrl->poll_timer);
	if (!pciehp_poll_time)
		pciehp_poll_time = 2; /* default polling interval is 2 sec */

	start_int_poll_timer(ctrl, pciehp_poll_time);
}