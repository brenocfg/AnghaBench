#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int /*<<< orphan*/  dev; struct usb_host_interface* altsetting; } ;
struct usb_idmouse {int bulk_in_size; int present; scalar_t__ bulk_in_endpointAddr; int /*<<< orphan*/  bulk_in_buffer; int /*<<< orphan*/  orig_bi_size; struct usb_interface* interface; struct usb_device* udev; int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int bInterfaceClass; } ;
struct usb_host_interface {TYPE_2__* endpoint; TYPE_1__ desc; } ;
struct usb_endpoint_descriptor {scalar_t__ bEndpointAddress; int /*<<< orphan*/  wMaxPacketSize; } ;
struct usb_device_id {int dummy; } ;
struct usb_device {int dummy; } ;
struct TYPE_4__ {struct usb_endpoint_descriptor desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_DESC ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IMGSIZE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  idmouse_class ; 
 int /*<<< orphan*/  idmouse_delete (struct usb_idmouse*) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 struct usb_idmouse* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ usb_endpoint_is_bulk_in (struct usb_endpoint_descriptor*) ; 
 int usb_register_dev (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct usb_idmouse*) ; 

__attribute__((used)) static int idmouse_probe(struct usb_interface *interface,
				const struct usb_device_id *id)
{
	struct usb_device *udev = interface_to_usbdev(interface);
	struct usb_idmouse *dev;
	struct usb_host_interface *iface_desc;
	struct usb_endpoint_descriptor *endpoint;
	int result;

	/* check if we have gotten the data or the hid interface */
	iface_desc = &interface->altsetting[0];
	if (iface_desc->desc.bInterfaceClass != 0x0A)
		return -ENODEV;

	/* allocate memory for our device state and initialize it */
	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (dev == NULL)
		return -ENOMEM;

	mutex_init(&dev->lock);
	dev->udev = udev;
	dev->interface = interface;

	/* set up the endpoint information - use only the first bulk-in endpoint */
	endpoint = &iface_desc->endpoint[0].desc;
	if (!dev->bulk_in_endpointAddr && usb_endpoint_is_bulk_in(endpoint)) {
		/* we found a bulk in endpoint */
		dev->orig_bi_size = le16_to_cpu(endpoint->wMaxPacketSize);
		dev->bulk_in_size = 0x200; /* works _much_ faster */
		dev->bulk_in_endpointAddr = endpoint->bEndpointAddress;
		dev->bulk_in_buffer =
			kmalloc(IMGSIZE + dev->bulk_in_size, GFP_KERNEL);

		if (!dev->bulk_in_buffer) {
			err("Unable to allocate input buffer.");
			idmouse_delete(dev);
			return -ENOMEM;
		}
	}

	if (!(dev->bulk_in_endpointAddr)) {
		err("Unable to find bulk-in endpoint.");
		idmouse_delete(dev);
		return -ENODEV;
	}
	/* allow device read, write and ioctl */
	dev->present = 1;

	/* we can register the device now, as it is ready */
	usb_set_intfdata(interface, dev);
	result = usb_register_dev(interface, &idmouse_class);
	if (result) {
		/* something prevented us from registering this device */
		err("Unble to allocate minor number.");
		usb_set_intfdata(interface, NULL);
		idmouse_delete(dev);
		return result;
	}

	/* be noisy */
	dev_info(&interface->dev,"%s now attached\n",DRIVER_DESC);

	return 0;
}