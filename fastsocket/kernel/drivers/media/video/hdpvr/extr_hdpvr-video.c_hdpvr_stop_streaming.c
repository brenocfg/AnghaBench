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
typedef  int uint ;
typedef  int /*<<< orphan*/  u8 ;
struct hdpvr_device {scalar_t__ status; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  bulk_in_size; int /*<<< orphan*/  bulk_in_endpointAddr; int /*<<< orphan*/  udev; int /*<<< orphan*/  io_mutex; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  wait_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  BULK_URB_TIMEOUT ; 
 int /*<<< orphan*/  CTRL_STOP_STREAMING_VALUE ; 
 int EAGAIN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MSG_BUFFER ; 
 scalar_t__ STATUS_IDLE ; 
 scalar_t__ STATUS_SHUTTING_DOWN ; 
 scalar_t__ STATUS_STREAMING ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdpvr_cancel_queue (struct hdpvr_device*) ; 
 int /*<<< orphan*/  hdpvr_config_call (struct hdpvr_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hdpvr_debug ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_bulk_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hdpvr_stop_streaming(struct hdpvr_device *dev)
{
	int actual_length;
	uint c = 0;
	u8 *buf;

	if (dev->status == STATUS_IDLE)
		return 0;
	else if (dev->status != STATUS_STREAMING)
		return -EAGAIN;

	buf = kmalloc(dev->bulk_in_size, GFP_KERNEL);
	if (!buf)
		v4l2_err(&dev->v4l2_dev, "failed to allocate temporary buffer "
			 "for emptying the internal device buffer. "
			 "Next capture start will be slow\n");

	dev->status = STATUS_SHUTTING_DOWN;
	hdpvr_config_call(dev, CTRL_STOP_STREAMING_VALUE, 0x00);
	mutex_unlock(&dev->io_mutex);

	wake_up_interruptible(&dev->wait_buffer);
	msleep(50);

	flush_workqueue(dev->workqueue);

	mutex_lock(&dev->io_mutex);
	/* kill the still outstanding urbs */
	hdpvr_cancel_queue(dev);

	/* emptying the device buffer beforeshutting it down */
	while (buf && ++c < 500 &&
	       !usb_bulk_msg(dev->udev,
			     usb_rcvbulkpipe(dev->udev,
					     dev->bulk_in_endpointAddr),
			     buf, dev->bulk_in_size, &actual_length,
			     BULK_URB_TIMEOUT)) {
		v4l2_dbg(MSG_BUFFER, hdpvr_debug, &dev->v4l2_dev,
			 "%2d: got %d bytes\n", c, actual_length);
	}
	kfree(buf);
	v4l2_dbg(MSG_BUFFER, hdpvr_debug, &dev->v4l2_dev,
		 "used %d urbs to empty device buffers\n", c-1);
	msleep(10);

	dev->status = STATUS_IDLE;

	return 0;
}