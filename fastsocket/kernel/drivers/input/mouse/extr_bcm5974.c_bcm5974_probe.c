#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct usb_device_id {int dummy; } ;
struct usb_device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_6__ {int /*<<< orphan*/  version; } ;
struct input_dev {char* name; int /*<<< orphan*/  close; int /*<<< orphan*/  open; TYPE_1__ dev; TYPE_2__ id; int /*<<< orphan*/  phys; } ;
struct bcm5974_config {int /*<<< orphan*/  bt_datalen; int /*<<< orphan*/  tp_datalen; int /*<<< orphan*/  caps; int /*<<< orphan*/  tp_ep; int /*<<< orphan*/  bt_ep; } ;
struct bcm5974 {TYPE_3__* bt_urb; TYPE_3__* tp_urb; void* bt_data; struct bcm5974_config cfg; struct usb_device* udev; void* tp_data; struct input_dev* input; int /*<<< orphan*/  phys; int /*<<< orphan*/  pm_mutex; struct usb_interface* intf; } ;
struct TYPE_7__ {int /*<<< orphan*/  transfer_dma; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  bcm5974_close ; 
 struct bcm5974_config* bcm5974_get_config (struct usb_device*) ; 
 int /*<<< orphan*/  bcm5974_irq_button ; 
 int /*<<< orphan*/  bcm5974_irq_trackpad ; 
 int /*<<< orphan*/  bcm5974_open ; 
 int /*<<< orphan*/  err (char*) ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct bcm5974*) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct bcm5974*) ; 
 struct bcm5974* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_events_to_report (struct input_dev*,struct bcm5974_config const*) ; 
 int /*<<< orphan*/  strlcat (int /*<<< orphan*/ ,char*,int) ; 
 void* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* usb_buffer_alloc (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_buffer_free (struct usb_device*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_int_urb (TYPE_3__*,struct usb_device*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bcm5974*,int) ; 
 int /*<<< orphan*/  usb_free_urb (TYPE_3__*) ; 
 int /*<<< orphan*/  usb_make_path (struct usb_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_rcvintpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct bcm5974*) ; 
 int /*<<< orphan*/  usb_to_input_id (struct usb_device*,TYPE_2__*) ; 

__attribute__((used)) static int bcm5974_probe(struct usb_interface *iface,
			 const struct usb_device_id *id)
{
	struct usb_device *udev = interface_to_usbdev(iface);
	const struct bcm5974_config *cfg;
	struct bcm5974 *dev;
	struct input_dev *input_dev;
	int error = -ENOMEM;

	/* find the product index */
	cfg = bcm5974_get_config(udev);

	/* allocate memory for our device state and initialize it */
	dev = kzalloc(sizeof(struct bcm5974), GFP_KERNEL);
	input_dev = input_allocate_device();
	if (!dev || !input_dev) {
		err("bcm5974: out of memory");
		goto err_free_devs;
	}

	dev->udev = udev;
	dev->intf = iface;
	dev->input = input_dev;
	dev->cfg = *cfg;
	mutex_init(&dev->pm_mutex);

	/* setup urbs */
	dev->bt_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!dev->bt_urb)
		goto err_free_devs;

	dev->tp_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!dev->tp_urb)
		goto err_free_bt_urb;

	dev->bt_data = usb_buffer_alloc(dev->udev,
					dev->cfg.bt_datalen, GFP_KERNEL,
					&dev->bt_urb->transfer_dma);
	if (!dev->bt_data)
		goto err_free_urb;

	dev->tp_data = usb_buffer_alloc(dev->udev,
					dev->cfg.tp_datalen, GFP_KERNEL,
					&dev->tp_urb->transfer_dma);
	if (!dev->tp_data)
		goto err_free_bt_buffer;

	usb_fill_int_urb(dev->bt_urb, udev,
			 usb_rcvintpipe(udev, cfg->bt_ep),
			 dev->bt_data, dev->cfg.bt_datalen,
			 bcm5974_irq_button, dev, 1);

	usb_fill_int_urb(dev->tp_urb, udev,
			 usb_rcvintpipe(udev, cfg->tp_ep),
			 dev->tp_data, dev->cfg.tp_datalen,
			 bcm5974_irq_trackpad, dev, 1);

	/* create bcm5974 device */
	usb_make_path(udev, dev->phys, sizeof(dev->phys));
	strlcat(dev->phys, "/input0", sizeof(dev->phys));

	input_dev->name = "bcm5974";
	input_dev->phys = dev->phys;
	usb_to_input_id(dev->udev, &input_dev->id);
	/* report driver capabilities via the version field */
	input_dev->id.version = cfg->caps;
	input_dev->dev.parent = &iface->dev;

	input_set_drvdata(input_dev, dev);

	input_dev->open = bcm5974_open;
	input_dev->close = bcm5974_close;

	setup_events_to_report(input_dev, cfg);

	error = input_register_device(dev->input);
	if (error)
		goto err_free_buffer;

	/* save our data pointer in this interface device */
	usb_set_intfdata(iface, dev);

	return 0;

err_free_buffer:
	usb_buffer_free(dev->udev, dev->cfg.tp_datalen,
		dev->tp_data, dev->tp_urb->transfer_dma);
err_free_bt_buffer:
	usb_buffer_free(dev->udev, dev->cfg.bt_datalen,
		dev->bt_data, dev->bt_urb->transfer_dma);
err_free_urb:
	usb_free_urb(dev->tp_urb);
err_free_bt_urb:
	usb_free_urb(dev->bt_urb);
err_free_devs:
	usb_set_intfdata(iface, NULL);
	input_free_device(input_dev);
	kfree(dev);
	return error;
}