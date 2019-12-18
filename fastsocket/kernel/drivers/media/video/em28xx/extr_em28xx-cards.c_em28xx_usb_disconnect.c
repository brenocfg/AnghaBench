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
struct usb_interface {int dummy; } ;
struct em28xx {struct em28xx* alt_max_pkt_size; scalar_t__ users; int /*<<< orphan*/  lock; int /*<<< orphan*/  state; int /*<<< orphan*/  wait_stream; int /*<<< orphan*/  wait_frame; TYPE_1__* vdev; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  open; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_DISCONNECTED ; 
 int /*<<< orphan*/  DEV_MISCONFIGURED ; 
 int /*<<< orphan*/  em28xx_close_extension (struct em28xx*) ; 
 int /*<<< orphan*/  em28xx_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  em28xx_release_resources (struct em28xx*) ; 
 int /*<<< orphan*/  em28xx_uninit_isoc (struct em28xx*) ; 
 int /*<<< orphan*/  em28xx_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct em28xx*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct em28xx* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_device_node_name (TYPE_1__*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void em28xx_usb_disconnect(struct usb_interface *interface)
{
	struct em28xx *dev;

	dev = usb_get_intfdata(interface);
	usb_set_intfdata(interface, NULL);

	if (!dev)
		return;

	em28xx_info("disconnecting %s\n", dev->vdev->name);

	/* wait until all current v4l2 io is finished then deallocate
	   resources */
	mutex_lock(&dev->lock);

	wake_up_interruptible_all(&dev->open);

	v4l2_device_disconnect(&dev->v4l2_dev);

	if (dev->users) {
		em28xx_warn
		    ("device %s is open! Deregistration and memory "
		     "deallocation are deferred on close.\n",
		     video_device_node_name(dev->vdev));

		dev->state |= DEV_MISCONFIGURED;
		em28xx_uninit_isoc(dev);
		dev->state |= DEV_DISCONNECTED;
		wake_up_interruptible(&dev->wait_frame);
		wake_up_interruptible(&dev->wait_stream);
	} else {
		dev->state |= DEV_DISCONNECTED;
		em28xx_release_resources(dev);
	}

	em28xx_close_extension(dev);

	mutex_unlock(&dev->lock);

	if (!dev->users) {
		kfree(dev->alt_max_pkt_size);
		kfree(dev);
	}
}