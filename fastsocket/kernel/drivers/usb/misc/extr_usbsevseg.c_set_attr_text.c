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
struct usb_sevsegdev {size_t textlength; int /*<<< orphan*/  text; } ;
struct usb_interface {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 size_t my_memlen (char const*,size_t) ; 
 struct usb_interface* to_usb_interface (struct device*) ; 
 int /*<<< orphan*/  update_display_visual (struct usb_sevsegdev*,int /*<<< orphan*/ ) ; 
 struct usb_sevsegdev* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static ssize_t set_attr_text(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	struct usb_interface *intf = to_usb_interface(dev);
	struct usb_sevsegdev *mydev = usb_get_intfdata(intf);
	size_t end = my_memlen(buf, count);

	if (end > sizeof(mydev->text))
		return -EINVAL;

	memset(mydev->text, 0, sizeof(mydev->text));
	mydev->textlength = end;

	if (end > 0)
		memcpy(mydev->text, buf, end);

	update_display_visual(mydev, GFP_KERNEL);
	return count;
}