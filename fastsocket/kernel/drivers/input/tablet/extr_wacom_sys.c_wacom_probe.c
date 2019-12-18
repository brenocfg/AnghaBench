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
struct wacom_wac {int /*<<< orphan*/  data_dma; int /*<<< orphan*/  data; TYPE_4__* irq; struct input_dev* dev; int /*<<< orphan*/  name; struct wacom_wac* wacom_wac; struct wacom_features* features; int /*<<< orphan*/  phys; int /*<<< orphan*/  lock; struct usb_interface* intf; struct usb_device* usbdev; } ;
struct wacom_features {scalar_t__ pktlen; scalar_t__ device_type; int quirks; int /*<<< orphan*/  name; int /*<<< orphan*/  pressure_max; int /*<<< orphan*/  y_max; int /*<<< orphan*/  x_max; } ;
struct wacom {int /*<<< orphan*/  data_dma; int /*<<< orphan*/  data; TYPE_4__* irq; struct input_dev* dev; int /*<<< orphan*/  name; struct wacom* wacom_wac; struct wacom_features* features; int /*<<< orphan*/  phys; int /*<<< orphan*/  lock; struct usb_interface* intf; struct usb_device* usbdev; } ;
struct usb_interface {TYPE_3__* cur_altsetting; int /*<<< orphan*/  dev; } ;
struct usb_endpoint_descriptor {int /*<<< orphan*/  bInterval; int /*<<< orphan*/  bEndpointAddress; } ;
struct usb_device_id {int dummy; } ;
struct usb_device {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/ * parent; } ;
struct input_dev {int* evbit; int* keybit; int* absbit; int /*<<< orphan*/  name; int /*<<< orphan*/  close; int /*<<< orphan*/  open; TYPE_1__ dev; int /*<<< orphan*/  id; } ;
struct TYPE_10__ {int /*<<< orphan*/  transfer_flags; int /*<<< orphan*/  transfer_dma; } ;
struct TYPE_9__ {TYPE_2__* endpoint; } ;
struct TYPE_8__ {struct usb_endpoint_descriptor desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MISC ; 
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int BIT_MASK (int /*<<< orphan*/ ) ; 
 size_t BIT_WORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTN_DIGI ; 
 scalar_t__ BTN_TOOL_PEN ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  URB_NO_TRANSFER_DMA_MAP ; 
 scalar_t__ WACOM_PKGLEN_MAX ; 
 int WACOM_QUIRK_MULTI_INPUT ; 
 struct wacom_features* get_wacom_feature (struct usb_device_id const*) ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct wacom_wac*) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct wacom_wac*) ; 
 struct wacom_wac* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcat (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_4__* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_buffer_alloc (struct usb_device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_buffer_free (struct usb_device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_int_urb (TYPE_4__*,struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,struct wacom_wac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (TYPE_4__*) ; 
 int /*<<< orphan*/  usb_make_path (struct usb_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_rcvintpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct wacom_wac*) ; 
 int /*<<< orphan*/  usb_to_input_id (struct usb_device*,int /*<<< orphan*/ *) ; 
 int wacom_add_shared_data (struct wacom_wac*,struct usb_device*) ; 
 int /*<<< orphan*/  wacom_close ; 
 int /*<<< orphan*/  wacom_destroy_leds (struct wacom_wac*) ; 
 int /*<<< orphan*/  wacom_init_input_dev (struct input_dev*,struct wacom_wac*) ; 
 int wacom_initialize_leds (struct wacom_wac*) ; 
 int /*<<< orphan*/  wacom_open ; 
 int /*<<< orphan*/  wacom_query_tablet_data (struct usb_interface*,struct wacom_features*) ; 
 int /*<<< orphan*/  wacom_remove_shared_data (struct wacom_wac*) ; 
 int wacom_retrieve_hid_descriptor (struct usb_interface*,struct wacom_features*) ; 
 int /*<<< orphan*/  wacom_setup_device_quirks (struct wacom_features*) ; 
 int /*<<< orphan*/  wacom_sys_irq ; 

__attribute__((used)) static int wacom_probe(struct usb_interface *intf, const struct usb_device_id *id)
{
	struct usb_device *dev = interface_to_usbdev(intf);
	struct usb_endpoint_descriptor *endpoint;
	struct wacom *wacom;
	struct wacom_wac *wacom_wac;
	struct wacom_features *features;
	struct input_dev *input_dev;
	int error = -ENOMEM;

	wacom = kzalloc(sizeof(struct wacom), GFP_KERNEL);
	wacom_wac = kzalloc(sizeof(struct wacom_wac), GFP_KERNEL);
	input_dev = input_allocate_device();
	if (!wacom || !input_dev || !wacom_wac)
		goto fail1;

	wacom_wac->data = usb_buffer_alloc(dev, WACOM_PKGLEN_MAX, GFP_KERNEL, &wacom->data_dma);
	if (!wacom_wac->data)
		goto fail1;

	wacom->irq = usb_alloc_urb(0, GFP_KERNEL);
	if (!wacom->irq)
		goto fail2;

	wacom->usbdev = dev;
	wacom->dev = input_dev;
	wacom->intf = intf;
	mutex_init(&wacom->lock);
	usb_make_path(dev, wacom->phys, sizeof(wacom->phys));
	strlcat(wacom->phys, "/input0", sizeof(wacom->phys));

	wacom_wac->features = features = get_wacom_feature(id);
	BUG_ON(features->pktlen > WACOM_PKGLEN_MAX);

	error = wacom_add_shared_data(wacom_wac, dev);
	if (error)
		goto fail3;

	wacom->wacom_wac = wacom_wac;
	usb_to_input_id(dev, &input_dev->id);

	input_dev->dev.parent = &intf->dev;

	input_set_drvdata(input_dev, wacom);

	input_dev->open = wacom_open;
	input_dev->close = wacom_close;

	endpoint = &intf->cur_altsetting->endpoint[0].desc;

	/* Retrieve the physical and logical size for OEM devices */
	error = wacom_retrieve_hid_descriptor(intf, features);
	if (error)
		goto fail4;

	input_dev->evbit[0] |= BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	input_dev->keybit[BIT_WORD(BTN_DIGI)] |= BIT_MASK(BTN_TOUCH);
	input_set_abs_params(input_dev, ABS_X, 0, features->x_max, 4, 0);
	input_set_abs_params(input_dev, ABS_Y, 0, features->y_max, 4, 0);
	input_dev->absbit[BIT_WORD(ABS_MISC)] |= BIT_MASK(ABS_MISC);

	if (features->device_type == BTN_TOOL_PEN)
		input_set_abs_params(input_dev, ABS_PRESSURE, 0, features->pressure_max, 0, 0);

	wacom_init_input_dev(input_dev, wacom_wac);

	wacom_setup_device_quirks(features);

	strlcpy(wacom_wac->name, features->name, sizeof(wacom_wac->name));

	if (features->quirks & WACOM_QUIRK_MULTI_INPUT) {
		/* Append the device type to the name */
		strlcat(wacom_wac->name,
			features->device_type == BTN_TOOL_PEN ?
				" Pen" : " Finger",
			sizeof(wacom_wac->name));
	}

	input_dev->name = wacom_wac->name;

	usb_fill_int_urb(wacom->irq, dev,
			 usb_rcvintpipe(dev, endpoint->bEndpointAddress),
			 wacom_wac->data, features->pktlen,
			 wacom_sys_irq, wacom, endpoint->bInterval);
	wacom->irq->transfer_dma = wacom->data_dma;
	wacom->irq->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	error = wacom_initialize_leds(wacom);
	if (error)
		goto fail4;

	error = input_register_device(wacom->dev);
	if (error)
		goto fail5;

	/* Note that if query fails it is not a hard failure */
	wacom_query_tablet_data(intf, features);

	usb_set_intfdata(intf, wacom);
	return 0;

 fail5: wacom_destroy_leds(wacom);
 fail4:	wacom_remove_shared_data(wacom_wac);
 fail3:	usb_free_urb(wacom->irq);
 fail2:	usb_buffer_free(dev, WACOM_PKGLEN_MAX, wacom_wac->data, wacom->data_dma);
 fail1:	input_free_device(input_dev);
	kfree(wacom);
	kfree(wacom_wac);
	return error;
}