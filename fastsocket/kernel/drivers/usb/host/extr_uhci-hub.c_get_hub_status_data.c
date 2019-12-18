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
struct uhci_hcd {int rh_numports; int /*<<< orphan*/  port_c_suspend; scalar_t__ io_addr; } ;

/* Variables and functions */
 int RWC_BITS ; 
 scalar_t__ USBPORTSC1 ; 
 int USBPORTSC_OCC ; 
 scalar_t__ ignore_oc ; 
 int inw (scalar_t__) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int get_hub_status_data(struct uhci_hcd *uhci, char *buf)
{
	int port;
	int mask = RWC_BITS;

	/* Some boards (both VIA and Intel apparently) report bogus
	 * overcurrent indications, causing massive log spam unless
	 * we completely ignore them.  This doesn't seem to be a problem
	 * with the chipset so much as with the way it is connected on
	 * the motherboard; if the overcurrent input is left to float
	 * then it may constantly register false positives. */
	if (ignore_oc)
		mask &= ~USBPORTSC_OCC;

	*buf = 0;
	for (port = 0; port < uhci->rh_numports; ++port) {
		if ((inw(uhci->io_addr + USBPORTSC1 + port * 2) & mask) ||
				test_bit(port, &uhci->port_c_suspend))
			*buf |= (1 << (port + 1));
	}
	return !!*buf;
}