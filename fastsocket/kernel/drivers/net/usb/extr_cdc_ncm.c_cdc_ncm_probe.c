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
struct usb_interface {int dummy; } ;
struct usb_device_id {int dummy; } ;

/* Variables and functions */
 int usbnet_probe (struct usb_interface*,struct usb_device_id const*) ; 

__attribute__((used)) static int
cdc_ncm_probe(struct usb_interface *udev, const struct usb_device_id *prod)
{
	return usbnet_probe(udev, prod);
}