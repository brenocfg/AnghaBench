#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_device {int /*<<< orphan*/  name; } ;
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct usb_device_id {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  release; int /*<<< orphan*/ * ioctl_ops; int /*<<< orphan*/ * fops; struct v4l2_device* v4l2_dev; int /*<<< orphan*/  name; } ;
struct dsbr100_device {int curfreq; struct dsbr100_device* transfer_buffer; TYPE_1__ videodev; int /*<<< orphan*/  status; int /*<<< orphan*/  usbdev; scalar_t__ removed; int /*<<< orphan*/  lock; struct v4l2_device v4l2_dev; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int FREQ_MIN ; 
 int FREQ_MUL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  STOPPED ; 
 int /*<<< orphan*/  TB_LEN ; 
 int /*<<< orphan*/  VFL_TYPE_RADIO ; 
 int /*<<< orphan*/  interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct dsbr100_device*) ; 
 struct dsbr100_device* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dsbr100_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radio_nr ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_dsbr100_fops ; 
 int /*<<< orphan*/  usb_dsbr100_ioctl_ops ; 
 int /*<<< orphan*/  usb_dsbr100_video_device_release ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct dsbr100_device*) ; 
 int v4l2_device_register (int /*<<< orphan*/ *,struct v4l2_device*) ; 
 int /*<<< orphan*/  v4l2_device_unregister (struct v4l2_device*) ; 
 int /*<<< orphan*/  v4l2_err (struct v4l2_device*,char*) ; 
 int video_register_device (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_set_drvdata (TYPE_1__*,struct dsbr100_device*) ; 

__attribute__((used)) static int usb_dsbr100_probe(struct usb_interface *intf,
				const struct usb_device_id *id)
{
	struct dsbr100_device *radio;
	struct v4l2_device *v4l2_dev;
	int retval;

	radio = kzalloc(sizeof(struct dsbr100_device), GFP_KERNEL);

	if (!radio)
		return -ENOMEM;

	radio->transfer_buffer = kmalloc(TB_LEN, GFP_KERNEL);

	if (!(radio->transfer_buffer)) {
		kfree(radio);
		return -ENOMEM;
	}

	v4l2_dev = &radio->v4l2_dev;

	retval = v4l2_device_register(&intf->dev, v4l2_dev);
	if (retval < 0) {
		v4l2_err(v4l2_dev, "couldn't register v4l2_device\n");
		kfree(radio->transfer_buffer);
		kfree(radio);
		return retval;
	}

	strlcpy(radio->videodev.name, v4l2_dev->name, sizeof(radio->videodev.name));
	radio->videodev.v4l2_dev = v4l2_dev;
	radio->videodev.fops = &usb_dsbr100_fops;
	radio->videodev.ioctl_ops = &usb_dsbr100_ioctl_ops;
	radio->videodev.release = usb_dsbr100_video_device_release;

	mutex_init(&radio->lock);

	radio->removed = 0;
	radio->usbdev = interface_to_usbdev(intf);
	radio->curfreq = FREQ_MIN * FREQ_MUL;
	radio->status = STOPPED;

	video_set_drvdata(&radio->videodev, radio);

	retval = video_register_device(&radio->videodev, VFL_TYPE_RADIO, radio_nr);
	if (retval < 0) {
		v4l2_err(v4l2_dev, "couldn't register video device\n");
		v4l2_device_unregister(v4l2_dev);
		kfree(radio->transfer_buffer);
		kfree(radio);
		return -EIO;
	}
	usb_set_intfdata(intf, radio);
	return 0;
}