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
struct hdpvr_fh {struct hdpvr_device* dev; } ;
struct hdpvr_device {scalar_t__ status; int /*<<< orphan*/  wait_data; int /*<<< orphan*/  io_mutex; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  video_dev; } ;
struct hdpvr_buffer {scalar_t__ status; } ;
struct file {struct hdpvr_fh* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 scalar_t__ BUFSTAT_READY ; 
 unsigned int EIO ; 
 int /*<<< orphan*/  MSG_BUFFER ; 
 unsigned int POLLIN ; 
 unsigned int POLLRDNORM ; 
 scalar_t__ STATUS_IDLE ; 
 int /*<<< orphan*/  hdpvr_debug ; 
 struct hdpvr_buffer* hdpvr_get_next_buffer (struct hdpvr_device*) ; 
 scalar_t__ hdpvr_start_streaming (struct hdpvr_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_buffer_status () ; 
 int /*<<< orphan*/  v4l2_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  video_is_registered (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int hdpvr_poll(struct file *filp, poll_table *wait)
{
	struct hdpvr_buffer *buf = NULL;
	struct hdpvr_fh *fh = filp->private_data;
	struct hdpvr_device *dev = fh->dev;
	unsigned int mask = 0;

	mutex_lock(&dev->io_mutex);

	if (!video_is_registered(dev->video_dev)) {
		mutex_unlock(&dev->io_mutex);
		return -EIO;
	}

	if (dev->status == STATUS_IDLE) {
		if (hdpvr_start_streaming(dev)) {
			v4l2_dbg(MSG_BUFFER, hdpvr_debug, &dev->v4l2_dev,
				 "start_streaming failed\n");
			dev->status = STATUS_IDLE;
		}

		print_buffer_status();
	}
	mutex_unlock(&dev->io_mutex);

	buf = hdpvr_get_next_buffer(dev);
	/* only wait if no data is available */
	if (!buf || buf->status != BUFSTAT_READY) {
		poll_wait(filp, &dev->wait_data, wait);
		buf = hdpvr_get_next_buffer(dev);
	}
	if (buf && buf->status == BUFSTAT_READY)
		mask |= POLLIN | POLLRDNORM;

	return mask;
}