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
struct usb_sevsegdev {int textmode; } ;
struct usb_interface {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__* display_textmodes ; 
 scalar_t__ sysfs_streq (scalar_t__,char const*) ; 
 struct usb_interface* to_usb_interface (struct device*) ; 
 int /*<<< orphan*/  update_display_visual (struct usb_sevsegdev*,int /*<<< orphan*/ ) ; 
 struct usb_sevsegdev* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static ssize_t set_attr_textmode(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	struct usb_interface *intf = to_usb_interface(dev);
	struct usb_sevsegdev *mydev = usb_get_intfdata(intf);
	int i;

	for (i = 0; display_textmodes[i]; i++) {
		if (sysfs_streq(display_textmodes[i], buf)) {
			mydev->textmode = i;
			update_display_visual(mydev, GFP_KERNEL);
			return count;
		}
	}

	return -EINVAL;
}