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
 scalar_t__ gadget_is_pxa (struct usb_gadget*) ; 
 scalar_t__ gadget_is_pxa27x (struct usb_gadget*) ; 
 scalar_t__ gadget_is_sh (struct usb_gadget*) ; 

__attribute__((used)) static inline bool gadget_supports_altsettings(struct usb_gadget *gadget)
{
	/* PXA 21x/25x/26x has no altsettings at all */
	if (gadget_is_pxa(gadget))
		return false;

	/* PXA 27x and 3xx have *broken* altsetting support */
	if (gadget_is_pxa27x(gadget))
		return false;

	/* SH3 hardware just doesn't do altsettings */
	if (gadget_is_sh(gadget))
		return false;

	/* Everything else is *presumably* fine ... */
	return true;
}