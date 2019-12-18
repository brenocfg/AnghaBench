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
struct usb_hcd {int dummy; } ;
struct musb {int port1_status; } ;

/* Variables and functions */
 struct musb* hcd_to_musb (struct usb_hcd*) ; 

int musb_hub_status_data(struct usb_hcd *hcd, char *buf)
{
	struct musb	*musb = hcd_to_musb(hcd);
	int		retval = 0;

	/* called in_irq() via usb_hcd_poll_rh_status() */
	if (musb->port1_status & 0xffff0000) {
		*buf = 0x02;
		retval = 1;
	}
	return retval;
}