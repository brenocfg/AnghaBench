#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {scalar_t__ minor; int /*<<< orphan*/  dev; struct usb_host_interface* cur_altsetting; } ;
struct TYPE_4__ {int bNumEndpoints; } ;
struct usb_host_interface {TYPE_2__* endpoint; TYPE_1__ desc; } ;
struct usb_endpoint_descriptor {scalar_t__ bInterval; int /*<<< orphan*/  wMaxPacketSize; } ;
struct usb_device_id {int dummy; } ;
struct TYPE_6__ {void* bMaxPacketSize0; } ;
struct usb_device {TYPE_3__ descriptor; } ;
struct usb_alphatrack {int interrupt_in_endpoint_size; int interrupt_out_endpoint_size; int /*<<< orphan*/  writes_pending; struct usb_endpoint_descriptor* interrupt_out_endpoint; scalar_t__ interrupt_out_interval; struct usb_endpoint_descriptor* interrupt_in_endpoint; scalar_t__ interrupt_in_interval; void* interrupt_out_urb; void* write_buffer; void* interrupt_out_buffer; void* interrupt_in_urb; void* oldi_buffer; void* interrupt_in_buffer; void* ring_buffer; int /*<<< orphan*/  write_wait; int /*<<< orphan*/  read_wait; struct usb_interface* intf; int /*<<< orphan*/  sem; } ;
struct alphatrack_ocmd {int dummy; } ;
struct alphatrack_icmd {int dummy; } ;
struct TYPE_5__ {struct usb_endpoint_descriptor desc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ RING_BUFFER_SIZE ; 
 scalar_t__ USB_ALPHATRACK_MINOR_BASE ; 
 int /*<<< orphan*/  USB_MAJOR ; 
 scalar_t__ WRITE_BUFFER_SIZE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  init_MUTEX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct usb_alphatrack* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int min (scalar_t__,scalar_t__) ; 
 scalar_t__ min_interrupt_in_interval ; 
 scalar_t__ min_interrupt_out_interval ; 
 scalar_t__ ring_buffer_size ; 
 void* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_alphatrack_class ; 
 int /*<<< orphan*/  usb_alphatrack_delete (struct usb_alphatrack*) ; 
 scalar_t__ usb_endpoint_is_int_in (struct usb_endpoint_descriptor*) ; 
 scalar_t__ usb_endpoint_is_int_out (struct usb_endpoint_descriptor*) ; 
 int usb_register_dev (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct usb_alphatrack*) ; 
 scalar_t__ write_buffer_size ; 

__attribute__((used)) static int usb_alphatrack_probe(struct usb_interface *intf,
				const struct usb_device_id *id)
{
	struct usb_device *udev = interface_to_usbdev(intf);
	struct usb_alphatrack *dev = NULL;
	struct usb_host_interface *iface_desc;
	struct usb_endpoint_descriptor *endpoint;
	int i;
	int true_size;
	int retval = -ENOMEM;

	/* allocate memory for our device state and intialize it */

	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (dev == NULL) {
		dev_err(&intf->dev, "Out of memory\n");
		goto exit;
	}
	init_MUTEX(&dev->sem);
	dev->intf = intf;
	init_waitqueue_head(&dev->read_wait);
	init_waitqueue_head(&dev->write_wait);

	iface_desc = intf->cur_altsetting;

	/* set up the endpoint information */
	for (i = 0; i < iface_desc->desc.bNumEndpoints; ++i) {
		endpoint = &iface_desc->endpoint[i].desc;

		if (usb_endpoint_is_int_in(endpoint))
			dev->interrupt_in_endpoint = endpoint;

		if (usb_endpoint_is_int_out(endpoint))
			dev->interrupt_out_endpoint = endpoint;
	}
	if (dev->interrupt_in_endpoint == NULL) {
		dev_err(&intf->dev, "Interrupt in endpoint not found\n");
		goto error;
	}
	if (dev->interrupt_out_endpoint == NULL)
		dev_warn(&intf->dev,
			 "Interrupt out endpoint not found"
			 "(using control endpoint instead)\n");

	dev->interrupt_in_endpoint_size =
	    le16_to_cpu(dev->interrupt_in_endpoint->wMaxPacketSize);

	if (dev->interrupt_in_endpoint_size != 64)
		dev_warn(&intf->dev, "Interrupt in endpoint size is not 64!\n");

	if (ring_buffer_size == 0)
		ring_buffer_size = RING_BUFFER_SIZE;

	true_size = min(ring_buffer_size, RING_BUFFER_SIZE);

	/* FIXME - there are more usb_alloc routines for dma correctness.
	   Needed? */
	dev->ring_buffer =
	    kmalloc((true_size * sizeof(struct alphatrack_icmd)), GFP_KERNEL);

	if (!dev->ring_buffer) {
		dev_err(&intf->dev,
			"Couldn't allocate input ring_buffer of size %d\n",
			true_size);
		goto error;
	}

	dev->interrupt_in_buffer =
	    kmalloc(dev->interrupt_in_endpoint_size, GFP_KERNEL);

	if (!dev->interrupt_in_buffer) {
		dev_err(&intf->dev, "Couldn't allocate interrupt_in_buffer\n");
		goto error;
	}
	dev->oldi_buffer = kmalloc(dev->interrupt_in_endpoint_size, GFP_KERNEL);
	if (!dev->oldi_buffer) {
		dev_err(&intf->dev, "Couldn't allocate old buffer\n");
		goto error;
	}
	dev->interrupt_in_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!dev->interrupt_in_urb) {
		dev_err(&intf->dev, "Couldn't allocate interrupt_in_urb\n");
		goto error;
	}

	dev->interrupt_out_endpoint_size =
	    dev->interrupt_out_endpoint ? le16_to_cpu(dev->
						      interrupt_out_endpoint->
						      wMaxPacketSize) : udev->
	    descriptor.bMaxPacketSize0;

	if (dev->interrupt_out_endpoint_size != 64)
		dev_warn(&intf->dev,
			 "Interrupt out endpoint size is not 64!)\n");

	if (write_buffer_size == 0)
		write_buffer_size = WRITE_BUFFER_SIZE;
	true_size = min(write_buffer_size, WRITE_BUFFER_SIZE);

	dev->interrupt_out_buffer =
	    kmalloc(true_size * dev->interrupt_out_endpoint_size, GFP_KERNEL);

	if (!dev->interrupt_out_buffer) {
		dev_err(&intf->dev, "Couldn't allocate interrupt_out_buffer\n");
		goto error;
	}

	dev->write_buffer =
	    kmalloc(sizeof(struct alphatrack_ocmd) * true_size, GFP_KERNEL);

	if (!dev->write_buffer) {
		dev_err(&intf->dev, "Couldn't allocate write_buffer \n");
		goto error;
	}

	dev->interrupt_out_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!dev->interrupt_out_urb) {
		dev_err(&intf->dev, "Couldn't allocate interrupt_out_urb\n");
		goto error;
	}
	dev->interrupt_in_interval =
	    min_interrupt_in_interval >
	    dev->interrupt_in_endpoint->
	    bInterval ? min_interrupt_in_interval : dev->interrupt_in_endpoint->
	    bInterval;
	if (dev->interrupt_out_endpoint)
		dev->interrupt_out_interval =
		    min_interrupt_out_interval >
		    dev->interrupt_out_endpoint->
		    bInterval ? min_interrupt_out_interval : dev->
		    interrupt_out_endpoint->bInterval;

	/* we can register the device now, as it is ready */
	usb_set_intfdata(intf, dev);

	atomic_set(&dev->writes_pending, 0);
	retval = usb_register_dev(intf, &usb_alphatrack_class);
	if (retval) {
		/* something prevented us from registering this driver */
		dev_err(&intf->dev,
			"Not able to get a minor for this device.\n");
		usb_set_intfdata(intf, NULL);
		goto error;
	}

	/* let the user know what node this device is now attached to */
	dev_info(&intf->dev,
		 "Alphatrack Device #%d now attached to major %d minor %d\n",
		 (intf->minor - USB_ALPHATRACK_MINOR_BASE), USB_MAJOR,
		 intf->minor);

exit:
	return retval;

error:
	usb_alphatrack_delete(dev);

	return retval;
}