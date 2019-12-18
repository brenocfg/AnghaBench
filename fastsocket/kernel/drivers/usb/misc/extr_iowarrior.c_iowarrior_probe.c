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
struct usb_interface {int /*<<< orphan*/  dev; scalar_t__ minor; struct usb_host_interface* cur_altsetting; } ;
struct TYPE_6__ {int bNumEndpoints; scalar_t__ bInterfaceNumber; } ;
struct usb_host_interface {TYPE_3__ desc; TYPE_1__* endpoint; } ;
struct usb_endpoint_descriptor {int /*<<< orphan*/  bInterval; int /*<<< orphan*/  bEndpointAddress; int /*<<< orphan*/  wMaxPacketSize; } ;
struct usb_device_id {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  iSerialNumber; int /*<<< orphan*/  idProduct; } ;
struct usb_device {TYPE_2__ descriptor; } ;
struct iowarrior {scalar_t__ product_id; int report_size; int present; scalar_t__ minor; int /*<<< orphan*/  chip_serial; struct usb_interface* interface; void* read_queue; struct usb_endpoint_descriptor* int_in_endpoint; void* int_in_buffer; struct usb_device* udev; int /*<<< orphan*/  int_in_urb; struct usb_endpoint_descriptor* int_out_endpoint; int /*<<< orphan*/  write_wait; int /*<<< orphan*/  write_busy; int /*<<< orphan*/  read_wait; int /*<<< orphan*/  overflow_flag; int /*<<< orphan*/  intr_idx_lock; int /*<<< orphan*/  read_idx; int /*<<< orphan*/  intr_idx; int /*<<< orphan*/  mutex; } ;
struct TYPE_4__ {struct usb_endpoint_descriptor desc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IOWARRIOR_MINOR_BASE ; 
 int MAX_INTERRUPT_BUFFER ; 
 int /*<<< orphan*/  USB_CTRL_SET_TIMEOUT ; 
 scalar_t__ USB_DEVICE_ID_CODEMERCS_IOW56 ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_CLASS ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  iowarrior_callback ; 
 int /*<<< orphan*/  iowarrior_class ; 
 int /*<<< orphan*/  iowarrior_delete (struct iowarrior*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct iowarrior* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_endpoint_is_int_in (struct usb_endpoint_descriptor*) ; 
 scalar_t__ usb_endpoint_is_int_out (struct usb_endpoint_descriptor*) ; 
 int /*<<< orphan*/  usb_fill_int_urb (int /*<<< orphan*/ ,struct usb_device*,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,struct iowarrior*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvintpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int usb_register_dev (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct iowarrior*) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_string (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int iowarrior_probe(struct usb_interface *interface,
			   const struct usb_device_id *id)
{
	struct usb_device *udev = interface_to_usbdev(interface);
	struct iowarrior *dev = NULL;
	struct usb_host_interface *iface_desc;
	struct usb_endpoint_descriptor *endpoint;
	int i;
	int retval = -ENOMEM;

	/* allocate memory for our device state and intialize it */
	dev = kzalloc(sizeof(struct iowarrior), GFP_KERNEL);
	if (dev == NULL) {
		dev_err(&interface->dev, "Out of memory\n");
		return retval;
	}

	mutex_init(&dev->mutex);

	atomic_set(&dev->intr_idx, 0);
	atomic_set(&dev->read_idx, 0);
	spin_lock_init(&dev->intr_idx_lock);
	atomic_set(&dev->overflow_flag, 0);
	init_waitqueue_head(&dev->read_wait);
	atomic_set(&dev->write_busy, 0);
	init_waitqueue_head(&dev->write_wait);

	dev->udev = udev;
	dev->interface = interface;

	iface_desc = interface->cur_altsetting;
	dev->product_id = le16_to_cpu(udev->descriptor.idProduct);

	/* set up the endpoint information */
	for (i = 0; i < iface_desc->desc.bNumEndpoints; ++i) {
		endpoint = &iface_desc->endpoint[i].desc;

		if (usb_endpoint_is_int_in(endpoint))
			dev->int_in_endpoint = endpoint;
		if (usb_endpoint_is_int_out(endpoint))
			/* this one will match for the IOWarrior56 only */
			dev->int_out_endpoint = endpoint;
	}
	/* we have to check the report_size often, so remember it in the endianess suitable for our machine */
	dev->report_size = le16_to_cpu(dev->int_in_endpoint->wMaxPacketSize);
	if ((dev->interface->cur_altsetting->desc.bInterfaceNumber == 0) &&
	    (dev->product_id == USB_DEVICE_ID_CODEMERCS_IOW56))
		/* IOWarrior56 has wMaxPacketSize different from report size */
		dev->report_size = 7;

	/* create the urb and buffer for reading */
	dev->int_in_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!dev->int_in_urb) {
		dev_err(&interface->dev, "Couldn't allocate interrupt_in_urb\n");
		goto error;
	}
	dev->int_in_buffer = kmalloc(dev->report_size, GFP_KERNEL);
	if (!dev->int_in_buffer) {
		dev_err(&interface->dev, "Couldn't allocate int_in_buffer\n");
		goto error;
	}
	usb_fill_int_urb(dev->int_in_urb, dev->udev,
			 usb_rcvintpipe(dev->udev,
					dev->int_in_endpoint->bEndpointAddress),
			 dev->int_in_buffer, dev->report_size,
			 iowarrior_callback, dev,
			 dev->int_in_endpoint->bInterval);
	/* create an internal buffer for interrupt data from the device */
	dev->read_queue =
	    kmalloc(((dev->report_size + 1) * MAX_INTERRUPT_BUFFER),
		    GFP_KERNEL);
	if (!dev->read_queue) {
		dev_err(&interface->dev, "Couldn't allocate read_queue\n");
		goto error;
	}
	/* Get the serial-number of the chip */
	memset(dev->chip_serial, 0x00, sizeof(dev->chip_serial));
	usb_string(udev, udev->descriptor.iSerialNumber, dev->chip_serial,
		   sizeof(dev->chip_serial));
	if (strlen(dev->chip_serial) != 8)
		memset(dev->chip_serial, 0x00, sizeof(dev->chip_serial));

	/* Set the idle timeout to 0, if this is interface 0 */
	if (dev->interface->cur_altsetting->desc.bInterfaceNumber == 0) {
	    usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
			    0x0A,
			    USB_TYPE_CLASS | USB_RECIP_INTERFACE, 0,
			    0, NULL, 0, USB_CTRL_SET_TIMEOUT);
	}
	/* allow device read and ioctl */
	dev->present = 1;

	/* we can register the device now, as it is ready */
	usb_set_intfdata(interface, dev);

	retval = usb_register_dev(interface, &iowarrior_class);
	if (retval) {
		/* something prevented us from registering this driver */
		dev_err(&interface->dev, "Not able to get a minor for this device.\n");
		usb_set_intfdata(interface, NULL);
		goto error;
	}

	dev->minor = interface->minor;

	/* let the user know what node this device is now attached to */
	dev_info(&interface->dev, "IOWarrior product=0x%x, serial=%s interface=%d "
		 "now attached to iowarrior%d\n", dev->product_id, dev->chip_serial,
		 iface_desc->desc.bInterfaceNumber, dev->minor - IOWARRIOR_MINOR_BASE);
	return retval;

error:
	iowarrior_delete(dev);
	return retval;
}