#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int /*<<< orphan*/  dev; TYPE_6__* altsetting; int /*<<< orphan*/  num_altsetting; TYPE_2__* cur_altsetting; } ;
struct usb_device_id {int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
struct usb_device {TYPE_4__* config; } ;
struct sd_desc {int (* config ) (struct gspca_dev*,struct usb_device_id const*) ;int (* init ) (struct gspca_dev*) ;} ;
struct module {int dummy; } ;
struct TYPE_18__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_17__ {int /*<<< orphan*/ * ctrls; } ;
struct gspca_dev {int audio; int nbufread; int empty_packet; int present; struct gspca_dev* usb_buf; scalar_t__ input_dev; TYPE_8__ vdev; struct module* module; int /*<<< orphan*/  wq; int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  usb_lock; TYPE_7__ cam; struct sd_desc const* sd_desc; int /*<<< orphan*/  nbalt; int /*<<< orphan*/  iface; struct usb_device* dev; } ;
struct TYPE_15__ {scalar_t__ bInterfaceClass; } ;
struct TYPE_16__ {TYPE_5__ desc; } ;
struct TYPE_13__ {int bNumInterfaces; } ;
struct TYPE_14__ {struct usb_interface** interface; TYPE_3__ desc; } ;
struct TYPE_11__ {int /*<<< orphan*/  bInterfaceNumber; } ;
struct TYPE_12__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_PROBE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  USB_BUF_SZ ; 
 scalar_t__ USB_CLASS_AUDIO ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  ctrls_init (struct gspca_dev*) ; 
 int /*<<< orphan*/  err (char*,...) ; 
 int gspca_input_connect (struct gspca_dev*) ; 
 int /*<<< orphan*/  gspca_input_create_urb (struct gspca_dev*) ; 
 int /*<<< orphan*/  gspca_set_default_mode (struct gspca_dev*) ; 
 int /*<<< orphan*/  gspca_template ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_unregister_device (scalar_t__) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct gspca_dev*) ; 
 struct gspca_dev* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct gspca_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_8__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int stub1 (struct gspca_dev*,struct usb_device_id const*) ; 
 int stub2 (struct gspca_dev*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct gspca_dev*) ; 
 int /*<<< orphan*/  video_device_node_name (TYPE_8__*) ; 
 int video_register_device (TYPE_8__*,int /*<<< orphan*/ ,int) ; 

int gspca_dev_probe2(struct usb_interface *intf,
		const struct usb_device_id *id,
		const struct sd_desc *sd_desc,
		int dev_size,
		struct module *module)
{
	struct gspca_dev *gspca_dev;
	struct usb_device *dev = interface_to_usbdev(intf);
	int ret;

	PDEBUG(D_PROBE, "probing %04x:%04x", id->idVendor, id->idProduct);

	/* create the device */
	if (dev_size < sizeof *gspca_dev)
		dev_size = sizeof *gspca_dev;
	gspca_dev = kzalloc(dev_size, GFP_KERNEL);
	if (!gspca_dev) {
		err("couldn't kzalloc gspca struct");
		return -ENOMEM;
	}
	gspca_dev->usb_buf = kmalloc(USB_BUF_SZ, GFP_KERNEL);
	if (!gspca_dev->usb_buf) {
		err("out of memory");
		ret = -ENOMEM;
		goto out;
	}
	gspca_dev->dev = dev;
	gspca_dev->iface = intf->cur_altsetting->desc.bInterfaceNumber;
	gspca_dev->nbalt = intf->num_altsetting;

	/* check if any audio device */
	if (dev->config->desc.bNumInterfaces != 1) {
		int i;
		struct usb_interface *intf2;

		for (i = 0; i < dev->config->desc.bNumInterfaces; i++) {
			intf2 = dev->config->interface[i];
			if (intf2 != NULL
			 && intf2->altsetting != NULL
			 && intf2->altsetting->desc.bInterfaceClass ==
					 USB_CLASS_AUDIO) {
				gspca_dev->audio = 1;
				break;
			}
		}
	}

	gspca_dev->sd_desc = sd_desc;
	gspca_dev->nbufread = 2;
	gspca_dev->empty_packet = -1;	/* don't check the empty packets */

	/* configure the subdriver and initialize the USB device */
	ret = sd_desc->config(gspca_dev, id);
	if (ret < 0)
		goto out;
	if (gspca_dev->cam.ctrls != NULL)
		ctrls_init(gspca_dev);
	ret = sd_desc->init(gspca_dev);
	if (ret < 0)
		goto out;
	gspca_set_default_mode(gspca_dev);

	ret = gspca_input_connect(gspca_dev);
	if (ret)
		goto out;

	mutex_init(&gspca_dev->usb_lock);
	mutex_init(&gspca_dev->queue_lock);
	init_waitqueue_head(&gspca_dev->wq);

	/* init video stuff */
	memcpy(&gspca_dev->vdev, &gspca_template, sizeof gspca_template);
	gspca_dev->vdev.parent = &intf->dev;
	gspca_dev->module = module;
	gspca_dev->present = 1;
	ret = video_register_device(&gspca_dev->vdev,
				  VFL_TYPE_GRABBER,
				  -1);
	if (ret < 0) {
		err("video_register_device err %d", ret);
		goto out;
	}

	usb_set_intfdata(intf, gspca_dev);
	PDEBUG(D_PROBE, "%s created", video_device_node_name(&gspca_dev->vdev));

	gspca_input_create_urb(gspca_dev);

	return 0;
out:
#if defined(CONFIG_INPUT) || defined(CONFIG_INPUT_MODULE)
	if (gspca_dev->input_dev)
		input_unregister_device(gspca_dev->input_dev);
#endif
	kfree(gspca_dev->usb_buf);
	kfree(gspca_dev);
	return ret;
}