#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usbdevfs_ioctl {int ioctl_code; int /*<<< orphan*/  data; int /*<<< orphan*/  ifno; } ;
struct TYPE_5__ {int /*<<< orphan*/  driver; } ;
struct usb_interface {TYPE_2__ dev; } ;
struct usb_driver {int (* ioctl ) (struct usb_interface*,int,void*) ;} ;
struct dev_state {TYPE_1__* dev; } ;
struct TYPE_4__ {scalar_t__ state; } ;

/* Variables and functions */
 int EBUSY ; 
 int EFAULT ; 
 int EHOSTUNREACH ; 
 int EINVAL ; 
 int ENODATA ; 
 int ENODEV ; 
 int ENOIOCTLCMD ; 
 int ENOMEM ; 
 int ENOTTY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  USBDEVFS_CONNECT 129 
#define  USBDEVFS_DISCONNECT 128 
 scalar_t__ USB_STATE_CONFIGURED ; 
 int _IOC_DIR (int) ; 
 int _IOC_READ ; 
 int _IOC_SIZE (int) ; 
 int _IOC_WRITE ; 
 int /*<<< orphan*/  connected (struct dev_state*) ; 
 scalar_t__ copy_from_user (void*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_2__*,char*) ; 
 int device_attach (TYPE_2__*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct usb_interface*,int,void*) ; 
 struct usb_driver* to_usb_driver (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_driver_release_interface (struct usb_driver*,struct usb_interface*) ; 
 struct usb_interface* usb_ifnum_to_if (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int proc_ioctl(struct dev_state *ps, struct usbdevfs_ioctl *ctl)
{
	int			size;
	void			*buf = NULL;
	int			retval = 0;
	struct usb_interface    *intf = NULL;
	struct usb_driver       *driver = NULL;

	/* alloc buffer */
	if ((size = _IOC_SIZE(ctl->ioctl_code)) > 0) {
		if ((buf = kmalloc(size, GFP_KERNEL)) == NULL)
			return -ENOMEM;
		if ((_IOC_DIR(ctl->ioctl_code) & _IOC_WRITE)) {
			if (copy_from_user(buf, ctl->data, size)) {
				kfree(buf);
				return -EFAULT;
			}
		} else {
			memset(buf, 0, size);
		}
	}

	if (!connected(ps)) {
		kfree(buf);
		return -ENODEV;
	}

	if (ps->dev->state != USB_STATE_CONFIGURED)
		retval = -EHOSTUNREACH;
	else if (!(intf = usb_ifnum_to_if(ps->dev, ctl->ifno)))
		retval = -EINVAL;
	else switch (ctl->ioctl_code) {

	/* disconnect kernel driver from interface */
	case USBDEVFS_DISCONNECT:
		if (intf->dev.driver) {
			driver = to_usb_driver(intf->dev.driver);
			dev_dbg(&intf->dev, "disconnect by usbfs\n");
			usb_driver_release_interface(driver, intf);
		} else
			retval = -ENODATA;
		break;

	/* let kernel drivers try to (re)bind to the interface */
	case USBDEVFS_CONNECT:
		if (!intf->dev.driver)
			retval = device_attach(&intf->dev);
		else
			retval = -EBUSY;
		break;

	/* talk directly to the interface's driver */
	default:
		if (intf->dev.driver)
			driver = to_usb_driver(intf->dev.driver);
		if (driver == NULL || driver->ioctl == NULL) {
			retval = -ENOTTY;
		} else {
			retval = driver->ioctl(intf, ctl->ioctl_code, buf);
			if (retval == -ENOIOCTLCMD)
				retval = -ENOTTY;
		}
	}

	/* cleanup and return */
	if (retval >= 0
			&& (_IOC_DIR(ctl->ioctl_code) & _IOC_READ) != 0
			&& size > 0
			&& copy_to_user(ctl->data, buf, size) != 0)
		retval = -EFAULT;

	kfree(buf);
	return retval;
}