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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct usb_device_id {int dummy; } ;
struct usb_device {int /*<<< orphan*/  devnum; } ;
struct rio_usb_data {int present; int /*<<< orphan*/  lock; void* ibuf; void* obuf; struct usb_device* rio_dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IBUF_SIZE ; 
 int /*<<< orphan*/  OBUF_SIZE ; 
 int /*<<< orphan*/  dbg (char*,void*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (char*) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct rio_usb_data rio_instance ; 
 int /*<<< orphan*/  usb_deregister_dev (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int usb_register_dev (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_rio_class ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct rio_usb_data*) ; 

__attribute__((used)) static int probe_rio(struct usb_interface *intf,
		     const struct usb_device_id *id)
{
	struct usb_device *dev = interface_to_usbdev(intf);
	struct rio_usb_data *rio = &rio_instance;
	int retval;

	dev_info(&intf->dev, "USB Rio found at address %d\n", dev->devnum);

	retval = usb_register_dev(intf, &usb_rio_class);
	if (retval) {
		err("Not able to get a minor for this device.");
		return -ENOMEM;
	}

	rio->rio_dev = dev;

	if (!(rio->obuf = kmalloc(OBUF_SIZE, GFP_KERNEL))) {
		err("probe_rio: Not enough memory for the output buffer");
		usb_deregister_dev(intf, &usb_rio_class);
		return -ENOMEM;
	}
	dbg("probe_rio: obuf address:%p", rio->obuf);

	if (!(rio->ibuf = kmalloc(IBUF_SIZE, GFP_KERNEL))) {
		err("probe_rio: Not enough memory for the input buffer");
		usb_deregister_dev(intf, &usb_rio_class);
		kfree(rio->obuf);
		return -ENOMEM;
	}
	dbg("probe_rio: ibuf address:%p", rio->ibuf);

	mutex_init(&(rio->lock));

	usb_set_intfdata (intf, rio);
	rio->present = 1;

	return 0;
}