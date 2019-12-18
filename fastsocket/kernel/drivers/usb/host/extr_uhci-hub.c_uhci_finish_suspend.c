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
struct uhci_hcd {int /*<<< orphan*/  resuming_ports; int /*<<< orphan*/  port_c_suspend; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLR_RH_PORTSTAT (int) ; 
 int SUSPEND_BITS ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ *) ; 
 int inw (unsigned long) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void uhci_finish_suspend(struct uhci_hcd *uhci, int port,
		unsigned long port_addr)
{
	int status;
	int i;

	if (inw(port_addr) & SUSPEND_BITS) {
		CLR_RH_PORTSTAT(SUSPEND_BITS);
		if (test_bit(port, &uhci->resuming_ports))
			set_bit(port, &uhci->port_c_suspend);

		/* The controller won't actually turn off the RD bit until
		 * it has had a chance to send a low-speed EOP sequence,
		 * which is supposed to take 3 bit times (= 2 microseconds).
		 * Experiments show that some controllers take longer, so
		 * we'll poll for completion. */
		for (i = 0; i < 10; ++i) {
			if (!(inw(port_addr) & SUSPEND_BITS))
				break;
			udelay(1);
		}
	}
	clear_bit(port, &uhci->resuming_ports);
}