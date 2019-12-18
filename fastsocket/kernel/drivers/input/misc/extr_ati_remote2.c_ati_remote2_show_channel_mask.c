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
struct usb_device {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ati_remote2 {int channel_mask; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct usb_device* to_usb_device (struct device*) ; 
 struct ati_remote2* usb_get_intfdata (struct usb_interface*) ; 
 struct usb_interface* usb_ifnum_to_if (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t ati_remote2_show_channel_mask(struct device *dev,
					     struct device_attribute *attr,
					     char *buf)
{
	struct usb_device *udev = to_usb_device(dev);
	struct usb_interface *intf = usb_ifnum_to_if(udev, 0);
	struct ati_remote2 *ar2 = usb_get_intfdata(intf);

	return sprintf(buf, "0x%04x\n", ar2->channel_mask);
}