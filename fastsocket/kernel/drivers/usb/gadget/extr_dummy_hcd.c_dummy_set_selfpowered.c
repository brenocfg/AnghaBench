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
struct dummy {int devstatus; } ;

/* Variables and functions */
 int USB_DEVICE_SELF_POWERED ; 
 struct dummy* gadget_to_dummy (struct usb_gadget*) ; 

__attribute__((used)) static int dummy_set_selfpowered (struct usb_gadget *_gadget, int value)
{
	struct dummy	*dum;

	dum = gadget_to_dummy (_gadget);
	if (value)
		dum->devstatus |= (1 << USB_DEVICE_SELF_POWERED);
	else
		dum->devstatus &= ~(1 << USB_DEVICE_SELF_POWERED);
	return 0;
}