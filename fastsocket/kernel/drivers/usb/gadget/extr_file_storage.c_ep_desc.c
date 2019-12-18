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
struct usb_gadget {scalar_t__ speed; } ;
struct usb_endpoint_descriptor {int dummy; } ;

/* Variables and functions */
 scalar_t__ USB_SPEED_HIGH ; 
 scalar_t__ gadget_is_dualspeed (struct usb_gadget*) ; 

__attribute__((used)) static struct usb_endpoint_descriptor *
ep_desc(struct usb_gadget *g, struct usb_endpoint_descriptor *fs,
		struct usb_endpoint_descriptor *hs)
{
	if (gadget_is_dualspeed(g) && g->speed == USB_SPEED_HIGH)
		return hs;
	return fs;
}