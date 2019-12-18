#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int /*<<< orphan*/  dev; struct usb_host_interface* cur_altsetting; } ;
struct TYPE_7__ {int bNumEndpoints; } ;
struct usb_host_interface {TYPE_2__* endpoint; TYPE_1__ desc; } ;
struct usb_endpoint_descriptor {int bEndpointAddress; } ;
struct usb_device_id {scalar_t__ driver_info; } ;
struct usb_device {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/ * parent; } ;
struct input_dev {char* name; int /*<<< orphan*/  keybit; int /*<<< orphan*/  evbit; int /*<<< orphan*/  close; int /*<<< orphan*/  open; TYPE_3__ dev; int /*<<< orphan*/  id; int /*<<< orphan*/  phys; } ;
struct atp_info {int xsensors; int xfact; int ysensors; int yfact; int /*<<< orphan*/  datalen; int /*<<< orphan*/  callback; } ;
struct atp {int overflow_warned; TYPE_4__* urb; int /*<<< orphan*/  data; struct atp_info const* info; struct usb_device* udev; int /*<<< orphan*/  work; struct input_dev* input; int /*<<< orphan*/  phys; } ;
struct TYPE_10__ {int /*<<< orphan*/  transfer_dma; } ;
struct TYPE_8__ {struct usb_endpoint_descriptor desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  ATP_FUZZ ; 
 int ATP_PRESSURE ; 
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_TOOL_DOUBLETAP ; 
 int /*<<< orphan*/  BTN_TOOL_FINGER ; 
 int /*<<< orphan*/  BTN_TOOL_TRIPLETAP ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atp_close ; 
 int atp_handle_geyser (struct atp*) ; 
 int /*<<< orphan*/  atp_open ; 
 int /*<<< orphan*/  atp_reinit ; 
 int /*<<< orphan*/  err (char*) ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct atp*) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct atp*) ; 
 struct atp* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcat (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_4__* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_buffer_alloc (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_buffer_free (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_endpoint_is_int_in (struct usb_endpoint_descriptor*) ; 
 int /*<<< orphan*/  usb_fill_int_urb (TYPE_4__*,struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct atp*,int) ; 
 int /*<<< orphan*/  usb_free_urb (TYPE_4__*) ; 
 int /*<<< orphan*/  usb_make_path (struct usb_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_rcvintpipe (struct usb_device*,int) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct atp*) ; 
 int /*<<< orphan*/  usb_to_input_id (struct usb_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int atp_probe(struct usb_interface *iface,
		     const struct usb_device_id *id)
{
	struct atp *dev;
	struct input_dev *input_dev;
	struct usb_device *udev = interface_to_usbdev(iface);
	struct usb_host_interface *iface_desc;
	struct usb_endpoint_descriptor *endpoint;
	int int_in_endpointAddr = 0;
	int i, error = -ENOMEM;
	const struct atp_info *info = (const struct atp_info *)id->driver_info;

	/* set up the endpoint information */
	/* use only the first interrupt-in endpoint */
	iface_desc = iface->cur_altsetting;
	for (i = 0; i < iface_desc->desc.bNumEndpoints; i++) {
		endpoint = &iface_desc->endpoint[i].desc;
		if (!int_in_endpointAddr && usb_endpoint_is_int_in(endpoint)) {
			/* we found an interrupt in endpoint */
			int_in_endpointAddr = endpoint->bEndpointAddress;
			break;
		}
	}
	if (!int_in_endpointAddr) {
		err("Could not find int-in endpoint");
		return -EIO;
	}

	/* allocate memory for our device state and initialize it */
	dev = kzalloc(sizeof(struct atp), GFP_KERNEL);
	input_dev = input_allocate_device();
	if (!dev || !input_dev) {
		err("Out of memory");
		goto err_free_devs;
	}

	dev->udev = udev;
	dev->input = input_dev;
	dev->info = info;
	dev->overflow_warned = false;

	dev->urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!dev->urb)
		goto err_free_devs;

	dev->data = usb_buffer_alloc(dev->udev, dev->info->datalen, GFP_KERNEL,
				     &dev->urb->transfer_dma);
	if (!dev->data)
		goto err_free_urb;

	usb_fill_int_urb(dev->urb, udev,
			 usb_rcvintpipe(udev, int_in_endpointAddr),
			 dev->data, dev->info->datalen,
			 dev->info->callback, dev, 1);

	error = atp_handle_geyser(dev);
	if (error)
		goto err_free_buffer;

	usb_make_path(udev, dev->phys, sizeof(dev->phys));
	strlcat(dev->phys, "/input0", sizeof(dev->phys));

	input_dev->name = "appletouch";
	input_dev->phys = dev->phys;
	usb_to_input_id(dev->udev, &input_dev->id);
	input_dev->dev.parent = &iface->dev;

	input_set_drvdata(input_dev, dev);

	input_dev->open = atp_open;
	input_dev->close = atp_close;

	set_bit(EV_ABS, input_dev->evbit);

	input_set_abs_params(input_dev, ABS_X, 0,
			     (dev->info->xsensors - 1) * dev->info->xfact - 1,
			     ATP_FUZZ, 0);
	input_set_abs_params(input_dev, ABS_Y, 0,
			     (dev->info->ysensors - 1) * dev->info->yfact - 1,
			     ATP_FUZZ, 0);
	input_set_abs_params(input_dev, ABS_PRESSURE, 0, ATP_PRESSURE, 0, 0);

	set_bit(EV_KEY, input_dev->evbit);
	set_bit(BTN_TOUCH, input_dev->keybit);
	set_bit(BTN_TOOL_FINGER, input_dev->keybit);
	set_bit(BTN_TOOL_DOUBLETAP, input_dev->keybit);
	set_bit(BTN_TOOL_TRIPLETAP, input_dev->keybit);
	set_bit(BTN_LEFT, input_dev->keybit);

	error = input_register_device(dev->input);
	if (error)
		goto err_free_buffer;

	/* save our data pointer in this interface device */
	usb_set_intfdata(iface, dev);

	INIT_WORK(&dev->work, atp_reinit);

	return 0;

 err_free_buffer:
	usb_buffer_free(dev->udev, dev->info->datalen,
			dev->data, dev->urb->transfer_dma);
 err_free_urb:
	usb_free_urb(dev->urb);
 err_free_devs:
	usb_set_intfdata(iface, NULL);
	kfree(dev);
	input_free_device(input_dev);
	return error;
}