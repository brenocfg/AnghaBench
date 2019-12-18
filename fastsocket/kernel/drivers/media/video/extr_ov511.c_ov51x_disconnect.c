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
struct usb_ov511 {int nr; int curframe; int /*<<< orphan*/  cbuf_lock; struct usb_ov511* cbuf; int /*<<< orphan*/  user; int /*<<< orphan*/ * dev; int /*<<< orphan*/  lock; scalar_t__ streaming; int /*<<< orphan*/  wq; TYPE_1__* frame; scalar_t__ vdev; } ;
struct usb_interface {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  wq; int /*<<< orphan*/  grabstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  FRAME_ERROR ; 
 int OV511_NUMFRAMES ; 
 int /*<<< orphan*/  PDEBUG (int,char*) ; 
 int /*<<< orphan*/  kfree (struct usb_ov511*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ov511_devused ; 
 int /*<<< orphan*/  ov51x_dealloc (struct usb_ov511*) ; 
 int /*<<< orphan*/  ov51x_unlink_isoc (struct usb_ov511*) ; 
 struct usb_ov511* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (scalar_t__) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ov51x_disconnect(struct usb_interface *intf)
{
	struct usb_ov511 *ov = usb_get_intfdata(intf);
	int n;

	PDEBUG(3, "");

	mutex_lock(&ov->lock);
	usb_set_intfdata (intf, NULL);

	if (!ov) {
		mutex_unlock(&ov->lock);
		return;
	}

	/* Free device number */
	ov511_devused &= ~(1 << ov->nr);

	if (ov->vdev)
		video_unregister_device(ov->vdev);

	for (n = 0; n < OV511_NUMFRAMES; n++)
		ov->frame[n].grabstate = FRAME_ERROR;

	ov->curframe = -1;

	/* This will cause the process to request another frame */
	for (n = 0; n < OV511_NUMFRAMES; n++)
		wake_up_interruptible(&ov->frame[n].wq);

	wake_up_interruptible(&ov->wq);

	ov->streaming = 0;
	ov51x_unlink_isoc(ov);
	mutex_unlock(&ov->lock);

	ov->dev = NULL;

	/* Free the memory */
	if (ov && !ov->user) {
		mutex_lock(&ov->cbuf_lock);
		kfree(ov->cbuf);
		ov->cbuf = NULL;
		mutex_unlock(&ov->cbuf_lock);

		ov51x_dealloc(ov);
		kfree(ov);
		ov = NULL;
	}

	PDEBUG(3, "Disconnect complete");
}