#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct usb_ov511 {int num_inputs; int stop_during_set; scalar_t__ bclass; int nr; int /*<<< orphan*/  cbuf_lock; struct usb_ov511* cbuf; TYPE_5__* vdev; int /*<<< orphan*/  lock; int /*<<< orphan*/  usb_path; TYPE_4__* sbuf; TYPE_3__* frame; int /*<<< orphan*/  buf_state; int /*<<< orphan*/  i2c_lock; int /*<<< orphan*/  buf_lock; int /*<<< orphan*/  wq; void* bridge; int /*<<< orphan*/  auto_exp; int /*<<< orphan*/  auto_gain; int /*<<< orphan*/  auto_brt; int /*<<< orphan*/  mirror; int /*<<< orphan*/  backlight; int /*<<< orphan*/  lightfreq; int /*<<< orphan*/  compress; int /*<<< orphan*/  led_policy; int /*<<< orphan*/  iface; struct usb_device* dev; } ;
struct usb_interface_descriptor {int bInterfaceClass; int bInterfaceSubClass; int /*<<< orphan*/  bInterfaceNumber; } ;
struct usb_interface {int /*<<< orphan*/  dev; TYPE_1__* cur_altsetting; } ;
struct usb_device_id {int dummy; } ;
struct TYPE_13__ {int bNumConfigurations; int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
struct usb_device {TYPE_2__ descriptor; } ;
struct TYPE_16__ {int minor; int /*<<< orphan*/ * parent; } ;
struct TYPE_15__ {int n; int /*<<< orphan*/  lock; struct usb_ov511* ov; } ;
struct TYPE_14__ {int framenum; int /*<<< orphan*/  wq; } ;
struct TYPE_12__ {struct usb_interface_descriptor desc; } ;

/* Variables and functions */
 scalar_t__ BCL_OV511 ; 
 scalar_t__ BCL_OV518 ; 
 void* BRG_OV511 ; 
 void* BRG_OV511PLUS ; 
 void* BRG_OV518 ; 
 void* BRG_OV518PLUS ; 
 int /*<<< orphan*/  BUF_NOT_ALLOCATED ; 
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OV511_CBUF_SIZE ; 
 int /*<<< orphan*/  OV511_MAX_UNIT_VIDEO ; 
 int OV511_NUMFRAMES ; 
 int OV511_NUMSBUF ; 
 int /*<<< orphan*/  OV511_USB_PATH_LEN ; 
 int /*<<< orphan*/  PDEBUG (int,char*) ; 
#define  PROD_ME2CAM 132 
#define  PROD_OV511 131 
#define  PROD_OV511PLUS 130 
#define  PROD_OV518 129 
#define  PROD_OV518PLUS 128 
 int VEND_MATTEL ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  autobright ; 
 int /*<<< orphan*/  autoexp ; 
 int /*<<< orphan*/  autogain ; 
 int /*<<< orphan*/  backlight ; 
 int /*<<< orphan*/  brglist ; 
 int /*<<< orphan*/  compress ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ dump_bridge ; 
 int /*<<< orphan*/  err (char*,...) ; 
 int /*<<< orphan*/  fastset ; 
 int find_first_zero_bit (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct usb_ov511*) ; 
 struct usb_ov511* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct usb_ov511* kzalloc (int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  led ; 
 int /*<<< orphan*/  lightfreq ; 
 int /*<<< orphan*/  memcpy (TYPE_5__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mirror ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ ov511_configure (struct usb_ov511*) ; 
 int ov511_devused ; 
 int /*<<< orphan*/  ov511_dump_regs (struct usb_ov511*) ; 
 scalar_t__ ov518_configure (struct usb_ov511*) ; 
 int /*<<< orphan*/  ov518_dump_regs (struct usb_ov511*) ; 
 scalar_t__ ov51x_set_default_params (struct usb_ov511*) ; 
 scalar_t__ ov_create_sysfs (TYPE_5__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  symbolic (int /*<<< orphan*/ ,void*) ; 
 scalar_t__* unit_video ; 
 scalar_t__ usb_make_path (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct usb_ov511*) ; 
 int /*<<< orphan*/  vdev_template ; 
 TYPE_5__* video_device_alloc () ; 
 int /*<<< orphan*/  video_device_release (TYPE_5__*) ; 
 int video_register_device (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_set_drvdata (TYPE_5__*,struct usb_ov511*) ; 
 int /*<<< orphan*/  video_unregister_device (TYPE_5__*) ; 

__attribute__((used)) static int
ov51x_probe(struct usb_interface *intf, const struct usb_device_id *id)
{
	struct usb_device *dev = interface_to_usbdev(intf);
	struct usb_interface_descriptor *idesc;
	struct usb_ov511 *ov;
	int i, rc, nr;

	PDEBUG(1, "probing for device...");

	/* We don't handle multi-config cameras */
	if (dev->descriptor.bNumConfigurations != 1)
		return -ENODEV;

	idesc = &intf->cur_altsetting->desc;

	if (idesc->bInterfaceClass != 0xFF)
		return -ENODEV;
	if (idesc->bInterfaceSubClass != 0x00)
		return -ENODEV;

	if ((ov = kzalloc(sizeof(*ov), GFP_KERNEL)) == NULL) {
		err("couldn't kmalloc ov struct");
		goto error_out;
	}

	ov->dev = dev;
	ov->iface = idesc->bInterfaceNumber;
	ov->led_policy = led;
	ov->compress = compress;
	ov->lightfreq = lightfreq;
	ov->num_inputs = 1;	   /* Video decoder init functs. change this */
	ov->stop_during_set = !fastset;
	ov->backlight = backlight;
	ov->mirror = mirror;
	ov->auto_brt = autobright;
	ov->auto_gain = autogain;
	ov->auto_exp = autoexp;

	switch (le16_to_cpu(dev->descriptor.idProduct)) {
	case PROD_OV511:
		ov->bridge = BRG_OV511;
		ov->bclass = BCL_OV511;
		break;
	case PROD_OV511PLUS:
		ov->bridge = BRG_OV511PLUS;
		ov->bclass = BCL_OV511;
		break;
	case PROD_OV518:
		ov->bridge = BRG_OV518;
		ov->bclass = BCL_OV518;
		break;
	case PROD_OV518PLUS:
		ov->bridge = BRG_OV518PLUS;
		ov->bclass = BCL_OV518;
		break;
	case PROD_ME2CAM:
		if (le16_to_cpu(dev->descriptor.idVendor) != VEND_MATTEL)
			goto error;
		ov->bridge = BRG_OV511PLUS;
		ov->bclass = BCL_OV511;
		break;
	default:
		err("Unknown product ID 0x%04x", le16_to_cpu(dev->descriptor.idProduct));
		goto error;
	}

	dev_info(&intf->dev, "USB %s video device found\n",
		 symbolic(brglist, ov->bridge));

	init_waitqueue_head(&ov->wq);

	mutex_init(&ov->lock);	/* to 1 == available */
	mutex_init(&ov->buf_lock);
	mutex_init(&ov->i2c_lock);
	mutex_init(&ov->cbuf_lock);

	ov->buf_state = BUF_NOT_ALLOCATED;

	if (usb_make_path(dev, ov->usb_path, OV511_USB_PATH_LEN) < 0) {
		err("usb_make_path error");
		goto error;
	}

	/* Allocate control transfer buffer. */
	/* Must be kmalloc()'ed, for DMA compatibility */
	ov->cbuf = kmalloc(OV511_CBUF_SIZE, GFP_KERNEL);
	if (!ov->cbuf)
		goto error;

	if (ov->bclass == BCL_OV518) {
		if (ov518_configure(ov) < 0)
			goto error;
	} else {
		if (ov511_configure(ov) < 0)
			goto error;
	}

	for (i = 0; i < OV511_NUMFRAMES; i++) {
		ov->frame[i].framenum = i;
		init_waitqueue_head(&ov->frame[i].wq);
	}

	for (i = 0; i < OV511_NUMSBUF; i++) {
		ov->sbuf[i].ov = ov;
		spin_lock_init(&ov->sbuf[i].lock);
		ov->sbuf[i].n = i;
	}

	/* Unnecessary? (This is done on open(). Need to make sure variables
	 * are properly initialized without this before removing it, though). */
	if (ov51x_set_default_params(ov) < 0)
		goto error;

#ifdef OV511_DEBUG
	if (dump_bridge) {
		if (ov->bclass == BCL_OV511)
			ov511_dump_regs(ov);
		else
			ov518_dump_regs(ov);
	}
#endif

	ov->vdev = video_device_alloc();
	if (!ov->vdev)
		goto error;

	memcpy(ov->vdev, &vdev_template, sizeof(*ov->vdev));
	ov->vdev->parent = &intf->dev;
	video_set_drvdata(ov->vdev, ov);

	mutex_lock(&ov->lock);

	/* Check to see next free device and mark as used */
	nr = find_first_zero_bit(&ov511_devused, OV511_MAX_UNIT_VIDEO);

	/* Registers device */
	if (unit_video[nr] != 0)
		rc = video_register_device(ov->vdev, VFL_TYPE_GRABBER,
					   unit_video[nr]);
	else
		rc = video_register_device(ov->vdev, VFL_TYPE_GRABBER, -1);

	if (rc < 0) {
		err("video_register_device failed");
		mutex_unlock(&ov->lock);
		goto error;
	}

	/* Mark device as used */
	ov511_devused |= 1 << nr;
	ov->nr = nr;

	dev_info(&intf->dev, "Device at %s registered to minor %d\n",
		 ov->usb_path, ov->vdev->minor);

	usb_set_intfdata(intf, ov);
	if (ov_create_sysfs(ov->vdev)) {
		err("ov_create_sysfs failed");
		ov511_devused &= ~(1 << nr);
		mutex_unlock(&ov->lock);
		goto error;
	}

	mutex_unlock(&ov->lock);

	return 0;

error:
	if (ov->vdev) {
		if (-1 == ov->vdev->minor)
			video_device_release(ov->vdev);
		else
			video_unregister_device(ov->vdev);
		ov->vdev = NULL;
	}

	if (ov->cbuf) {
		mutex_lock(&ov->cbuf_lock);
		kfree(ov->cbuf);
		ov->cbuf = NULL;
		mutex_unlock(&ov->cbuf_lock);
	}

	kfree(ov);
	ov = NULL;

error_out:
	err("Camera initialization failed");
	return -EIO;
}