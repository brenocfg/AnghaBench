#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct video_device {int dummy; } ;
struct usb_ov511 {scalar_t__ led_policy; int /*<<< orphan*/  lock; scalar_t__ user; int /*<<< orphan*/  decomp_ops; scalar_t__ compress; TYPE_1__* frame; scalar_t__ sub_flag; } ;
struct file {struct video_device* private_data; } ;
struct TYPE_2__ {scalar_t__ bytes_read; int /*<<< orphan*/  grabstate; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  FRAME_UNUSED ; 
 scalar_t__ LED_AUTO ; 
 int OV511_NUMFRAMES ; 
 int /*<<< orphan*/  PDEBUG (int,char*) ; 
 int /*<<< orphan*/  dumppix ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ov51x_alloc (struct usb_ov511*) ; 
 int /*<<< orphan*/  ov51x_dealloc (struct usb_ov511*) ; 
 int ov51x_init_isoc (struct usb_ov511*) ; 
 int /*<<< orphan*/  ov51x_led_control (struct usb_ov511*,int) ; 
 int ov51x_set_default_params (struct usb_ov511*) ; 
 int request_decompressor (struct usb_ov511*) ; 
 struct video_device* video_devdata (struct file*) ; 
 struct usb_ov511* video_get_drvdata (struct video_device*) ; 

__attribute__((used)) static int
ov51x_v4l1_open(struct file *file)
{
	struct video_device *vdev = video_devdata(file);
	struct usb_ov511 *ov = video_get_drvdata(vdev);
	int err, i;

	PDEBUG(4, "opening");

	mutex_lock(&ov->lock);

	err = -EBUSY;
	if (ov->user)
		goto out;

	ov->sub_flag = 0;

	/* In case app doesn't set them... */
	err = ov51x_set_default_params(ov);
	if (err < 0)
		goto out;

	/* Make sure frames are reset */
	for (i = 0; i < OV511_NUMFRAMES; i++) {
		ov->frame[i].grabstate = FRAME_UNUSED;
		ov->frame[i].bytes_read = 0;
	}

	/* If compression is on, make sure now that a
	 * decompressor can be loaded */
	if (ov->compress && !ov->decomp_ops) {
		err = request_decompressor(ov);
		if (err && !dumppix)
			goto out;
	}

	err = ov51x_alloc(ov);
	if (err < 0)
		goto out;

	err = ov51x_init_isoc(ov);
	if (err) {
		ov51x_dealloc(ov);
		goto out;
	}

	ov->user++;
	file->private_data = vdev;

	if (ov->led_policy == LED_AUTO)
		ov51x_led_control(ov, 1);

out:
	mutex_unlock(&ov->lock);
	return err;
}