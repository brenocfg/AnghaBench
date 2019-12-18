#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int minor; int /*<<< orphan*/  usb_dev; int /*<<< orphan*/  dev; } ;
struct usb_class_driver {int minor_base; char* name; int /*<<< orphan*/ * fops; } ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_2__ {int /*<<< orphan*/  class; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int MAX_USB_MINORS ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_MAJOR ; 
 int /*<<< orphan*/  dbg (char*,int) ; 
 int /*<<< orphan*/  device_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct usb_class_driver*,char*,char*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int init_usb_class () ; 
 int /*<<< orphan*/  minor_rwsem ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 TYPE_1__* usb_class ; 
 int /*<<< orphan*/ ** usb_minors ; 

int usb_register_dev(struct usb_interface *intf,
		     struct usb_class_driver *class_driver)
{
	int retval = -EINVAL;
	int minor_base = class_driver->minor_base;
	int minor = 0;
	char name[20];
	char *temp;

#ifdef CONFIG_USB_DYNAMIC_MINORS
	/* 
	 * We don't care what the device tries to start at, we want to start
	 * at zero to pack the devices into the smallest available space with
	 * no holes in the minor range.
	 */
	minor_base = 0;
#endif
	intf->minor = -1;

	dbg ("looking for a minor, starting at %d", minor_base);

	if (class_driver->fops == NULL)
		goto exit;

	down_write(&minor_rwsem);
	for (minor = minor_base; minor < MAX_USB_MINORS; ++minor) {
		if (usb_minors[minor])
			continue;

		usb_minors[minor] = class_driver->fops;

		retval = 0;
		break;
	}
	up_write(&minor_rwsem);

	if (retval)
		goto exit;

	retval = init_usb_class();
	if (retval)
		goto exit;

	intf->minor = minor;

	/* create a usb class device for this usb interface */
	snprintf(name, sizeof(name), class_driver->name, minor - minor_base);
	temp = strrchr(name, '/');
	if (temp && (temp[1] != '\0'))
		++temp;
	else
		temp = name;
	intf->usb_dev = device_create(usb_class->class, &intf->dev,
				      MKDEV(USB_MAJOR, minor), class_driver,
				      "%s", temp);
	if (IS_ERR(intf->usb_dev)) {
		down_write(&minor_rwsem);
		usb_minors[intf->minor] = NULL;
		up_write(&minor_rwsem);
		retval = PTR_ERR(intf->usb_dev);
	}
exit:
	return retval;
}