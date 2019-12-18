#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int dummy; } ;
struct TYPE_8__ {struct cx231xx* alt_max_pkt_size; } ;
struct TYPE_7__ {struct cx231xx* alt_max_pkt_size; } ;
struct TYPE_6__ {struct cx231xx* alt_max_pkt_size; } ;
struct TYPE_5__ {struct cx231xx* alt_max_pkt_size; } ;
struct cx231xx {TYPE_4__ ts1_mode; TYPE_3__ sliced_cc_mode; TYPE_2__ vbi_mode; TYPE_1__ video_mode; scalar_t__ users; int /*<<< orphan*/  lock; int /*<<< orphan*/  state; int /*<<< orphan*/  wait_stream; int /*<<< orphan*/  wait_frame; scalar_t__ USE_ISO; int /*<<< orphan*/  vdev; int /*<<< orphan*/  open; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_DISCONNECTED ; 
 int /*<<< orphan*/  DEV_MISCONFIGURED ; 
 int /*<<< orphan*/  cx231xx_close_extension (struct cx231xx*) ; 
 int /*<<< orphan*/  cx231xx_release_resources (struct cx231xx*) ; 
 int /*<<< orphan*/  cx231xx_uninit_bulk (struct cx231xx*) ; 
 int /*<<< orphan*/  cx231xx_uninit_isoc (struct cx231xx*) ; 
 int /*<<< orphan*/  cx231xx_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cx231xx*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct cx231xx* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_device_node_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cx231xx_usb_disconnect(struct usb_interface *interface)
{
	struct cx231xx *dev;

	dev = usb_get_intfdata(interface);
	usb_set_intfdata(interface, NULL);

	if (!dev)
		return;

	if (!dev->udev)
		return;

	/* delete v4l2 device */
	v4l2_device_unregister(&dev->v4l2_dev);

	/* wait until all current v4l2 io is finished then deallocate
	   resources */
	mutex_lock(&dev->lock);

	wake_up_interruptible_all(&dev->open);

	if (dev->users) {
		cx231xx_warn
		    ("device %s is open! Deregistration and memory "
		     "deallocation are deferred on close.\n",
		     video_device_node_name(dev->vdev));

		dev->state |= DEV_MISCONFIGURED;
		if (dev->USE_ISO)
			cx231xx_uninit_isoc(dev);
		else
			cx231xx_uninit_bulk(dev);
		dev->state |= DEV_DISCONNECTED;
		wake_up_interruptible(&dev->wait_frame);
		wake_up_interruptible(&dev->wait_stream);
	} else {
		dev->state |= DEV_DISCONNECTED;
		cx231xx_release_resources(dev);
	}

	cx231xx_close_extension(dev);

	mutex_unlock(&dev->lock);

	if (!dev->users) {
		kfree(dev->video_mode.alt_max_pkt_size);
		kfree(dev->vbi_mode.alt_max_pkt_size);
		kfree(dev->sliced_cc_mode.alt_max_pkt_size);
		kfree(dev->ts1_mode.alt_max_pkt_size);
		kfree(dev);
		dev = NULL;
	}
}