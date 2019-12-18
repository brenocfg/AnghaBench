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
struct usb_sevsegdev {int* decimals; } ;
struct usb_interface {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct usb_interface* to_usb_interface (struct device*) ; 
 struct usb_sevsegdev* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static ssize_t show_attr_decimals(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	struct usb_interface *intf = to_usb_interface(dev);
	struct usb_sevsegdev *mydev = usb_get_intfdata(intf);
	int i;
	int pos;

	for (i = 0; i < sizeof(mydev->decimals); i++) {
		pos = sizeof(mydev->decimals) - 1 - i;
		if (mydev->decimals[i] == 0)
			buf[pos] = '0';
		else if (mydev->decimals[i] == 1)
			buf[pos] = '1';
		else
			buf[pos] = 'x';
	}

	buf[sizeof(mydev->decimals)] = '\n';
	return sizeof(mydev->decimals) + 1;
}