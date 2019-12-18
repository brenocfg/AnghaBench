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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct asus_oled_dev {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  enable_oled (struct asus_oled_dev*,int) ; 
 int strict_strtoul (char const*,int,int /*<<< orphan*/ *) ; 
 struct usb_interface* to_usb_interface (struct device*) ; 
 struct asus_oled_dev* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static ssize_t set_enabled(struct device *dev, struct device_attribute *attr,
			   const char *buf, size_t count)
{
	struct usb_interface *intf = to_usb_interface(dev);
	struct asus_oled_dev *odev = usb_get_intfdata(intf);
	int temp = strict_strtoul(buf, 10, NULL);

	enable_oled(odev, temp);

	return count;
}