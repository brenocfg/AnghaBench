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
struct uhci_hcd {unsigned int rh_numports; int io_addr; scalar_t__ ports_timeout; int /*<<< orphan*/  resuming_ports; scalar_t__ wait_for_hp; } ;
struct TYPE_2__ {int /*<<< orphan*/  rh_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLR_RH_PORTSTAT (int) ; 
 int /*<<< orphan*/  SET_RH_PORTSTAT (int /*<<< orphan*/ ) ; 
 int USBPORTSC1 ; 
 int USBPORTSC_CSC ; 
 int /*<<< orphan*/  USBPORTSC_PE ; 
 int USBPORTSC_PEC ; 
 int USBPORTSC_PR ; 
 int USBPORTSC_RD ; 
 int inw (unsigned long) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  set_bit (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ time_after_eq (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  uhci_finish_suspend (struct uhci_hcd*,unsigned int,unsigned long) ; 
 TYPE_1__* uhci_to_hcd (struct uhci_hcd*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wait_for_HP (unsigned long) ; 

__attribute__((used)) static void uhci_check_ports(struct uhci_hcd *uhci)
{
	unsigned int port;
	unsigned long port_addr;
	int status;

	for (port = 0; port < uhci->rh_numports; ++port) {
		port_addr = uhci->io_addr + USBPORTSC1 + 2 * port;
		status = inw(port_addr);
		if (unlikely(status & USBPORTSC_PR)) {
			if (time_after_eq(jiffies, uhci->ports_timeout)) {
				CLR_RH_PORTSTAT(USBPORTSC_PR);
				udelay(10);

				/* HP's server management chip requires
				 * a longer delay. */
				if (uhci->wait_for_hp)
					wait_for_HP(port_addr);

				/* If the port was enabled before, turning
				 * reset on caused a port enable change.
				 * Turning reset off causes a port connect
				 * status change.  Clear these changes. */
				CLR_RH_PORTSTAT(USBPORTSC_CSC | USBPORTSC_PEC);
				SET_RH_PORTSTAT(USBPORTSC_PE);
			}
		}
		if (unlikely(status & USBPORTSC_RD)) {
			if (!test_bit(port, &uhci->resuming_ports)) {

				/* Port received a wakeup request */
				set_bit(port, &uhci->resuming_ports);
				uhci->ports_timeout = jiffies +
						msecs_to_jiffies(25);

				/* Make sure we see the port again
				 * after the resuming period is over. */
				mod_timer(&uhci_to_hcd(uhci)->rh_timer,
						uhci->ports_timeout);
			} else if (time_after_eq(jiffies,
						uhci->ports_timeout)) {
				uhci_finish_suspend(uhci, port, port_addr);
			}
		}
	}
}