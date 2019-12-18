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
struct usb_interface {int dummy; } ;
struct hdpvr_device {int /*<<< orphan*/  video_dev; int /*<<< orphan*/  i2c_adapter; int /*<<< orphan*/  io_mutex; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  wait_buffer; int /*<<< orphan*/  wait_data; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATUS_DISCONNECTED ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_nr ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdpvr_cancel_queue (struct hdpvr_device*) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct hdpvr_device* to_hdpvr_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  v4l2_device_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_device_node_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hdpvr_disconnect(struct usb_interface *interface)
{
	struct hdpvr_device *dev = to_hdpvr_dev(usb_get_intfdata(interface));

	v4l2_info(&dev->v4l2_dev, "device %s disconnected\n",
		  video_device_node_name(dev->video_dev));
	/* prevent more I/O from starting and stop any ongoing */
	mutex_lock(&dev->io_mutex);
	dev->status = STATUS_DISCONNECTED;
	wake_up_interruptible(&dev->wait_data);
	wake_up_interruptible(&dev->wait_buffer);
	mutex_unlock(&dev->io_mutex);
	v4l2_device_disconnect(&dev->v4l2_dev);
	msleep(100);
	flush_workqueue(dev->workqueue);
	mutex_lock(&dev->io_mutex);
	hdpvr_cancel_queue(dev);
	mutex_unlock(&dev->io_mutex);
#if defined(CONFIG_I2C) || defined(CONFIG_I2C_MODULE)
	i2c_del_adapter(&dev->i2c_adapter);
#endif
	video_unregister_device(dev->video_dev);
	atomic_dec(&dev_nr);
}