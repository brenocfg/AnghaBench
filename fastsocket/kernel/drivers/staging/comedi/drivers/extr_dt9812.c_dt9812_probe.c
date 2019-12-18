#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct usb_interface {int /*<<< orphan*/  dev; struct usb_host_interface* cur_altsetting; } ;
struct TYPE_8__ {int bNumEndpoints; } ;
struct usb_host_interface {TYPE_2__* endpoint; TYPE_1__ desc; } ;
struct usb_endpoint_descriptor {int bEndpointAddress; int wMaxPacketSize; } ;
struct TYPE_14__ {int addr; void* size; } ;
struct TYPE_13__ {int addr; void* size; } ;
struct TYPE_12__ {int addr; void* size; } ;
struct TYPE_11__ {int addr; void* size; } ;
struct TYPE_10__ {int addr; void* size; } ;
struct usb_dt9812 {int vendor; int product; int device; int serial; int* analog_out_shadow; int /*<<< orphan*/  kref; struct slot_dt9812* slot; scalar_t__ digital_out_shadow; int /*<<< orphan*/  udev; TYPE_7__ read_stream; TYPE_6__ write_stream; TYPE_5__ command_read; TYPE_4__ command_write; TYPE_3__ message_pipe; struct usb_interface* interface; } ;
struct usb_device_id {int dummy; } ;
struct slot_dt9812 {scalar_t__ serial; int /*<<< orphan*/  mutex; struct usb_dt9812* usb; } ;
typedef  int /*<<< orphan*/  fw ;
struct TYPE_9__ {struct usb_endpoint_descriptor desc; } ;

/* Variables and functions */
#define  DT9812_DEVID_DT9812_10 129 
#define  DT9812_DEVID_DT9812_2PT5 128 
 int DT9812_NUM_SLOTS ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int USB_DIR_IN ; 
 int USB_DIR_OUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 struct slot_dt9812* dt9812 ; 
 int /*<<< orphan*/  dt9812_delete ; 
 int /*<<< orphan*/  dt9812_mutex ; 
 int dt9812_read_info (struct usb_dt9812*,int,int*,int) ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct usb_dt9812* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* le16_to_cpu (int) ; 
 int le32_to_cpu (int) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_get_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_reset_configuration (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct usb_dt9812*) ; 

__attribute__((used)) static int dt9812_probe(struct usb_interface *interface,
			const struct usb_device_id *id)
{
	int retval = -ENOMEM;
	struct usb_dt9812 *dev = NULL;
	struct usb_host_interface *iface_desc;
	struct usb_endpoint_descriptor *endpoint;
	int i;
	u8 fw;

	/* allocate memory for our device state and initialize it */
	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (dev == NULL) {
		dev_err(&interface->dev, "Out of memory\n");
		goto error;
	}
	kref_init(&dev->kref);

	dev->udev = usb_get_dev(interface_to_usbdev(interface));
	dev->interface = interface;

	/* Check endpoints */
	iface_desc = interface->cur_altsetting;

	if (iface_desc->desc.bNumEndpoints != 5) {
		err("Wrong number of endpints.");
		retval = -ENODEV;
		goto error;
	}

	for (i = 0; i < iface_desc->desc.bNumEndpoints; ++i) {
		int direction = -1;
		endpoint = &iface_desc->endpoint[i].desc;
		switch (i) {
		case 0:
			direction = USB_DIR_IN;
			dev->message_pipe.addr = endpoint->bEndpointAddress;
			dev->message_pipe.size =
			    le16_to_cpu(endpoint->wMaxPacketSize);

			break;
		case 1:
			direction = USB_DIR_OUT;
			dev->command_write.addr = endpoint->bEndpointAddress;
			dev->command_write.size =
			    le16_to_cpu(endpoint->wMaxPacketSize);
			break;
		case 2:
			direction = USB_DIR_IN;
			dev->command_read.addr = endpoint->bEndpointAddress;
			dev->command_read.size =
			    le16_to_cpu(endpoint->wMaxPacketSize);
			break;
		case 3:
			direction = USB_DIR_OUT;
			dev->write_stream.addr = endpoint->bEndpointAddress;
			dev->write_stream.size =
			    le16_to_cpu(endpoint->wMaxPacketSize);
			break;
		case 4:
			direction = USB_DIR_IN;
			dev->read_stream.addr = endpoint->bEndpointAddress;
			dev->read_stream.size =
			    le16_to_cpu(endpoint->wMaxPacketSize);
			break;
		}
		if ((endpoint->bEndpointAddress & USB_DIR_IN) != direction) {
			dev_err(&interface->dev,
				"Endpoint has wrong direction.\n");
			retval = -ENODEV;
			goto error;
		}
	}
	if (dt9812_read_info(dev, 0, &fw, sizeof(fw)) != 0) {
		/*
		 * Seems like a configuration reset is necessary if driver is
		 * reloaded while device is attached
		 */
		usb_reset_configuration(dev->udev);
		for (i = 0; i < 10; i++) {
			retval = dt9812_read_info(dev, 1, &fw, sizeof(fw));
			if (retval == 0) {
				dev_info(&interface->dev,
					 "usb_reset_configuration succeded "
					 "after %d iterations\n", i);
				break;
			}
		}
	}

	if (dt9812_read_info(dev, 1, &dev->vendor, sizeof(dev->vendor)) != 0) {
		err("Failed to read vendor.");
		retval = -ENODEV;
		goto error;
	}
	if (dt9812_read_info(dev, 3, &dev->product, sizeof(dev->product)) != 0) {
		err("Failed to read product.");
		retval = -ENODEV;
		goto error;
	}
	if (dt9812_read_info(dev, 5, &dev->device, sizeof(dev->device)) != 0) {
		err("Failed to read device.");
		retval = -ENODEV;
		goto error;
	}
	if (dt9812_read_info(dev, 7, &dev->serial, sizeof(dev->serial)) != 0) {
		err("Failed to read serial.");
		retval = -ENODEV;
		goto error;
	}

	dev->vendor = le16_to_cpu(dev->vendor);
	dev->product = le16_to_cpu(dev->product);
	dev->device = le16_to_cpu(dev->device);
	dev->serial = le32_to_cpu(dev->serial);
	switch (dev->device) {
	case DT9812_DEVID_DT9812_10:
		dev->analog_out_shadow[0] = 0x0800;
		dev->analog_out_shadow[1] = 0x800;
		break;
	case DT9812_DEVID_DT9812_2PT5:
		dev->analog_out_shadow[0] = 0x0000;
		dev->analog_out_shadow[1] = 0x0000;
		break;
	}
	dev->digital_out_shadow = 0;

	/* save our data pointer in this interface device */
	usb_set_intfdata(interface, dev);

	/* let the user know what node this device is now attached to */
	dev_info(&interface->dev, "USB DT9812 (%4.4x.%4.4x.%4.4x) #0x%8.8x\n",
		 dev->vendor, dev->product, dev->device, dev->serial);

	down(&dt9812_mutex);
	{
		/* Find a slot for the USB device */
		struct slot_dt9812 *first = NULL;
		struct slot_dt9812 *best = NULL;

		for (i = 0; i < DT9812_NUM_SLOTS; i++) {
			if (!first && !dt9812[i].usb && dt9812[i].serial == 0)
				first = &dt9812[i];
			if (!best && dt9812[i].serial == dev->serial)
				best = &dt9812[i];
		}

		if (!best)
			best = first;

		if (best) {
			down(&best->mutex);
			best->usb = dev;
			dev->slot = best;
			up(&best->mutex);
		}
	}
	up(&dt9812_mutex);

	return 0;

error:
	if (dev)
		kref_put(&dev->kref, dt9812_delete);
	return retval;
}