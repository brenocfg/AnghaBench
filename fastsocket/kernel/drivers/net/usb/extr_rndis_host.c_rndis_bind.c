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
struct usbnet {int dummy; } ;
struct usb_interface {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_RNDIS_PHYM_NOT_WIRELESS ; 
 int generic_rndis_bind (struct usbnet*,struct usb_interface*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rndis_bind(struct usbnet *dev, struct usb_interface *intf)
{
	return generic_rndis_bind(dev, intf, FLAG_RNDIS_PHYM_NOT_WIRELESS);
}