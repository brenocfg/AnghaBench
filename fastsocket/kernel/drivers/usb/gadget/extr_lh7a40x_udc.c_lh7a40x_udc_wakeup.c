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
struct usb_gadget {int dummy; } ;

/* Variables and functions */
 int ENOTSUPP ; 

__attribute__((used)) static int lh7a40x_udc_wakeup(struct usb_gadget *_gadget)
{
	/* host may not have enabled remote wakeup */
	/*if ((UDCCS0 & UDCCS0_DRWF) == 0)
	   return -EHOSTUNREACH;
	   udc_set_mask_UDCCR(UDCCR_RSM); */
	return -ENOTSUPP;
}