#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct v4l2_device {int /*<<< orphan*/  name; } ;
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct usb_device_id {int dummy; } ;
struct amradio_device {double curfreq; int stereo; struct amradio_device* buffer; TYPE_1__* videodev; int /*<<< orphan*/  lock; int /*<<< orphan*/  usbdev; scalar_t__ users; scalar_t__ removed; struct v4l2_device v4l2_dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  release; int /*<<< orphan*/ * ioctl_ops; int /*<<< orphan*/ * fops; struct v4l2_device* v4l2_dev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_LENGTH ; 
 int EIO ; 
 int ENOMEM ; 
 double FREQ_MUL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  VFL_TYPE_RADIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct amradio_device*) ; 
 struct amradio_device* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct amradio_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radio_nr ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_amradio_fops ; 
 int /*<<< orphan*/  usb_amradio_ioctl_ops ; 
 int /*<<< orphan*/  usb_amradio_video_device_release ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct amradio_device*) ; 
 int v4l2_device_register (int /*<<< orphan*/ *,struct v4l2_device*) ; 
 int /*<<< orphan*/  v4l2_device_unregister (struct v4l2_device*) ; 
 TYPE_1__* video_device_alloc () ; 
 int /*<<< orphan*/  video_device_release (TYPE_1__*) ; 
 int video_register_device (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_set_drvdata (TYPE_1__*,struct amradio_device*) ; 

__attribute__((used)) static int usb_amradio_probe(struct usb_interface *intf,
				const struct usb_device_id *id)
{
	struct amradio_device *radio;
	struct v4l2_device *v4l2_dev;
	int retval;

	radio = kzalloc(sizeof(struct amradio_device), GFP_KERNEL);

	if (!radio) {
		dev_err(&intf->dev, "kmalloc for amradio_device failed\n");
		return -ENOMEM;
	}

	radio->buffer = kmalloc(BUFFER_LENGTH, GFP_KERNEL);

	if (!radio->buffer) {
		dev_err(&intf->dev, "kmalloc for radio->buffer failed\n");
		kfree(radio);
		return -ENOMEM;
	}

	v4l2_dev = &radio->v4l2_dev;
	retval = v4l2_device_register(&intf->dev, v4l2_dev);
	if (retval < 0) {
		dev_err(&intf->dev, "couldn't register v4l2_device\n");
		kfree(radio->buffer);
		kfree(radio);
		return retval;
	}

	radio->videodev = video_device_alloc();

	if (!radio->videodev) {
		dev_err(&intf->dev, "video_device_alloc failed\n");
		kfree(radio->buffer);
		kfree(radio);
		return -ENOMEM;
	}

	strlcpy(radio->videodev->name, v4l2_dev->name, sizeof(radio->videodev->name));
	radio->videodev->v4l2_dev = v4l2_dev;
	radio->videodev->fops = &usb_amradio_fops;
	radio->videodev->ioctl_ops = &usb_amradio_ioctl_ops;
	radio->videodev->release = usb_amradio_video_device_release;

	radio->removed = 0;
	radio->users = 0;
	radio->usbdev = interface_to_usbdev(intf);
	radio->curfreq = 95.16 * FREQ_MUL;
	radio->stereo = -1;

	mutex_init(&radio->lock);

	video_set_drvdata(radio->videodev, radio);

	retval = video_register_device(radio->videodev,	VFL_TYPE_RADIO,	radio_nr);
	if (retval < 0) {
		dev_err(&intf->dev, "could not register video device\n");
		video_device_release(radio->videodev);
		v4l2_device_unregister(v4l2_dev);
		kfree(radio->buffer);
		kfree(radio);
		return -EIO;
	}

	usb_set_intfdata(intf, radio);
	return 0;
}