#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct usb_xpad {int dpad_mapping; scalar_t__ xtype; int* bdata; int /*<<< orphan*/  idata_dma; int /*<<< orphan*/  idata; TYPE_7__* irq_in; TYPE_7__* bulk_out; struct usb_device* udev; struct input_dev* dev; int /*<<< orphan*/  phys; } ;
struct usb_interface {TYPE_4__* cur_altsetting; int /*<<< orphan*/  dev; } ;
struct usb_endpoint_descriptor {int /*<<< orphan*/  bEndpointAddress; int /*<<< orphan*/  bInterval; } ;
struct usb_device_id {int dummy; } ;
struct TYPE_13__ {int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
struct usb_device {TYPE_2__ descriptor; } ;
struct TYPE_16__ {int /*<<< orphan*/ * parent; } ;
struct input_dev {int* evbit; int /*<<< orphan*/  keybit; int /*<<< orphan*/  close; int /*<<< orphan*/  open; TYPE_5__ dev; int /*<<< orphan*/  id; int /*<<< orphan*/  phys; int /*<<< orphan*/  name; } ;
struct TYPE_18__ {struct usb_device* dev; int /*<<< orphan*/  transfer_flags; int /*<<< orphan*/  transfer_dma; } ;
struct TYPE_17__ {scalar_t__ idVendor; scalar_t__ idProduct; int dpad_mapping; scalar_t__ xtype; int /*<<< orphan*/  name; } ;
struct TYPE_14__ {scalar_t__ bInterfaceClass; int bInterfaceProtocol; int bInterfaceNumber; } ;
struct TYPE_15__ {TYPE_1__* endpoint; TYPE_3__ desc; } ;
struct TYPE_12__ {struct usb_endpoint_descriptor desc; } ;

/* Variables and functions */
 int BIT_MASK (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAP_DPAD_TO_AXES ; 
 int MAP_DPAD_TO_BUTTONS ; 
 int MAP_DPAD_UNKNOWN ; 
 int /*<<< orphan*/  URB_NO_TRANSFER_DMA_MAP ; 
 scalar_t__ USB_CLASS_VENDOR_SPEC ; 
 int XPAD_PKT_LEN ; 
 scalar_t__ XTYPE_UNKNOWN ; 
 scalar_t__ XTYPE_XBOX ; 
 scalar_t__ XTYPE_XBOX360 ; 
 scalar_t__ XTYPE_XBOX360W ; 
 int /*<<< orphan*/  dpad_to_buttons ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct usb_xpad*) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct usb_xpad*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcat (int /*<<< orphan*/ ,char*,int) ; 
 void* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_buffer_alloc (struct usb_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_buffer_free (struct usb_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (TYPE_7__*,struct usb_device*,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ,struct usb_xpad*) ; 
 int /*<<< orphan*/  usb_fill_int_urb (TYPE_7__*,struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct usb_xpad*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (TYPE_7__*) ; 
 int /*<<< orphan*/  usb_kill_urb (TYPE_7__*) ; 
 int /*<<< orphan*/  usb_make_path (struct usb_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_rcvintpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct usb_xpad*) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_to_input_id (struct usb_device*,int /*<<< orphan*/ *) ; 
 scalar_t__* xpad360_btn ; 
 scalar_t__* xpad_abs ; 
 scalar_t__* xpad_abs_pad ; 
 scalar_t__* xpad_btn ; 
 scalar_t__* xpad_btn_pad ; 
 int /*<<< orphan*/  xpad_bulk_out ; 
 int /*<<< orphan*/  xpad_close ; 
 scalar_t__* xpad_common_btn ; 
 int /*<<< orphan*/  xpad_deinit_output (struct usb_xpad*) ; 
 TYPE_6__* xpad_device ; 
 int xpad_init_ff (struct usb_xpad*) ; 
 int xpad_init_output (struct usb_interface*,struct usb_xpad*) ; 
 int /*<<< orphan*/  xpad_irq_in ; 
 int xpad_led_probe (struct usb_xpad*) ; 
 int /*<<< orphan*/  xpad_open ; 
 int /*<<< orphan*/  xpad_set_up_abs (struct input_dev*,scalar_t__) ; 

__attribute__((used)) static int xpad_probe(struct usb_interface *intf, const struct usb_device_id *id)
{
	struct usb_device *udev = interface_to_usbdev(intf);
	struct usb_xpad *xpad;
	struct input_dev *input_dev;
	struct usb_endpoint_descriptor *ep_irq_in;
	int i;
	int error = -ENOMEM;

	for (i = 0; xpad_device[i].idVendor; i++) {
		if ((le16_to_cpu(udev->descriptor.idVendor) == xpad_device[i].idVendor) &&
		    (le16_to_cpu(udev->descriptor.idProduct) == xpad_device[i].idProduct))
			break;
	}

	xpad = kzalloc(sizeof(struct usb_xpad), GFP_KERNEL);
	input_dev = input_allocate_device();
	if (!xpad || !input_dev)
		goto fail1;

	xpad->idata = usb_buffer_alloc(udev, XPAD_PKT_LEN,
				       GFP_KERNEL, &xpad->idata_dma);
	if (!xpad->idata)
		goto fail1;

	xpad->irq_in = usb_alloc_urb(0, GFP_KERNEL);
	if (!xpad->irq_in)
		goto fail2;

	xpad->udev = udev;
	xpad->dpad_mapping = xpad_device[i].dpad_mapping;
	xpad->xtype = xpad_device[i].xtype;
	if (xpad->dpad_mapping == MAP_DPAD_UNKNOWN)
		xpad->dpad_mapping = !dpad_to_buttons;
	if (xpad->xtype == XTYPE_UNKNOWN) {
		if (intf->cur_altsetting->desc.bInterfaceClass == USB_CLASS_VENDOR_SPEC) {
			if (intf->cur_altsetting->desc.bInterfaceProtocol == 129)
				xpad->xtype = XTYPE_XBOX360W;
			else
				xpad->xtype = XTYPE_XBOX360;
		} else
			xpad->xtype = XTYPE_XBOX;
	}
	xpad->dev = input_dev;
	usb_make_path(udev, xpad->phys, sizeof(xpad->phys));
	strlcat(xpad->phys, "/input0", sizeof(xpad->phys));

	input_dev->name = xpad_device[i].name;
	input_dev->phys = xpad->phys;
	usb_to_input_id(udev, &input_dev->id);
	input_dev->dev.parent = &intf->dev;

	input_set_drvdata(input_dev, xpad);

	input_dev->open = xpad_open;
	input_dev->close = xpad_close;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);

	/* set up buttons */
	for (i = 0; xpad_common_btn[i] >= 0; i++)
		set_bit(xpad_common_btn[i], input_dev->keybit);
	if ((xpad->xtype == XTYPE_XBOX360) || (xpad->xtype == XTYPE_XBOX360W))
		for (i = 0; xpad360_btn[i] >= 0; i++)
			set_bit(xpad360_btn[i], input_dev->keybit);
	else
		for (i = 0; xpad_btn[i] >= 0; i++)
			set_bit(xpad_btn[i], input_dev->keybit);
	if (xpad->dpad_mapping == MAP_DPAD_TO_BUTTONS)
		for (i = 0; xpad_btn_pad[i] >= 0; i++)
			set_bit(xpad_btn_pad[i], input_dev->keybit);

	/* set up axes */
	for (i = 0; xpad_abs[i] >= 0; i++)
		xpad_set_up_abs(input_dev, xpad_abs[i]);
	if (xpad->dpad_mapping == MAP_DPAD_TO_AXES)
		for (i = 0; xpad_abs_pad[i] >= 0; i++)
		    xpad_set_up_abs(input_dev, xpad_abs_pad[i]);

	error = xpad_init_output(intf, xpad);
	if (error)
		goto fail2;

	error = xpad_init_ff(xpad);
	if (error)
		goto fail3;

	error = xpad_led_probe(xpad);
	if (error)
		goto fail3;

	ep_irq_in = &intf->cur_altsetting->endpoint[0].desc;
	usb_fill_int_urb(xpad->irq_in, udev,
			 usb_rcvintpipe(udev, ep_irq_in->bEndpointAddress),
			 xpad->idata, XPAD_PKT_LEN, xpad_irq_in,
			 xpad, ep_irq_in->bInterval);
	xpad->irq_in->transfer_dma = xpad->idata_dma;
	xpad->irq_in->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	error = input_register_device(xpad->dev);
	if (error)
		goto fail4;

	usb_set_intfdata(intf, xpad);

	/*
	 * Submit the int URB immediatly rather than waiting for open
	 * because we get status messages from the device whether
	 * or not any controllers are attached.  In fact, it's
	 * exactly the message that a controller has arrived that
	 * we're waiting for.
	 */
	if (xpad->xtype == XTYPE_XBOX360W) {
		xpad->irq_in->dev = xpad->udev;
		error = usb_submit_urb(xpad->irq_in, GFP_KERNEL);
		if (error)
			goto fail4;

		/*
		 * Setup the message to set the LEDs on the
		 * controller when it shows up
		 */
		xpad->bulk_out = usb_alloc_urb(0, GFP_KERNEL);
		if(!xpad->bulk_out)
			goto fail5;

		xpad->bdata = kzalloc(XPAD_PKT_LEN, GFP_KERNEL);
		if(!xpad->bdata)
			goto fail6;

		xpad->bdata[2] = 0x08;
		switch (intf->cur_altsetting->desc.bInterfaceNumber) {
		case 0:
			xpad->bdata[3] = 0x42;
			break;
		case 2:
			xpad->bdata[3] = 0x43;
			break;
		case 4:
			xpad->bdata[3] = 0x44;
			break;
		case 6:
			xpad->bdata[3] = 0x45;
		}

		ep_irq_in = &intf->cur_altsetting->endpoint[1].desc;
		usb_fill_bulk_urb(xpad->bulk_out, udev,
				usb_sndbulkpipe(udev, ep_irq_in->bEndpointAddress),
				xpad->bdata, XPAD_PKT_LEN, xpad_bulk_out, xpad);
	}

	return 0;

 fail6:	usb_free_urb(xpad->bulk_out);
 fail5:	usb_kill_urb(xpad->irq_in);
 fail4:	usb_free_urb(xpad->irq_in);
 fail3:	xpad_deinit_output(xpad);
 fail2:	usb_buffer_free(udev, XPAD_PKT_LEN, xpad->idata, xpad->idata_dma);
 fail1:	input_free_device(input_dev);
	kfree(xpad);
	return error;

}