#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct video_device {int dummy; } ;
struct usb_ov511 {scalar_t__ led_policy; int /*<<< orphan*/  cbuf_lock; struct usb_ov511* cbuf; scalar_t__ dev; int /*<<< orphan*/  lock; int /*<<< orphan*/  user; } ;
struct file {struct video_device* private_data; } ;

/* Variables and functions */
 scalar_t__ LED_AUTO ; 
 int /*<<< orphan*/  PDEBUG (int,char*) ; 
 int /*<<< orphan*/  kfree (struct usb_ov511*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ov51x_dealloc (struct usb_ov511*) ; 
 int /*<<< orphan*/  ov51x_led_control (struct usb_ov511*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ov51x_stop_isoc (struct usb_ov511*) ; 
 struct usb_ov511* video_get_drvdata (struct video_device*) ; 

__attribute__((used)) static int
ov51x_v4l1_close(struct file *file)
{
	struct video_device *vdev = file->private_data;
	struct usb_ov511 *ov = video_get_drvdata(vdev);

	PDEBUG(4, "ov511_close");

	mutex_lock(&ov->lock);

	ov->user--;
	ov51x_stop_isoc(ov);

	if (ov->led_policy == LED_AUTO)
		ov51x_led_control(ov, 0);

	if (ov->dev)
		ov51x_dealloc(ov);

	mutex_unlock(&ov->lock);

	/* Device unplugged while open. Only a minimum of unregistration is done
	 * here; the disconnect callback already did the rest. */
	if (!ov->dev) {
		mutex_lock(&ov->cbuf_lock);
		kfree(ov->cbuf);
		ov->cbuf = NULL;
		mutex_unlock(&ov->cbuf_lock);

		ov51x_dealloc(ov);
		kfree(ov);
		ov = NULL;
	}

	file->private_data = NULL;
	return 0;
}