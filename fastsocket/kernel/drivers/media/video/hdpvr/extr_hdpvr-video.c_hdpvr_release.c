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
struct hdpvr_device {scalar_t__ status; int /*<<< orphan*/  io_mutex; int /*<<< orphan*/  open_count; } ;
struct file {struct hdpvr_fh* private_data; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ STATUS_STREAMING ; 
 int /*<<< orphan*/  hdpvr_stop_streaming (struct hdpvr_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hdpvr_release(struct file *file)
{
	struct hdpvr_fh		*fh  = file->private_data;
	struct hdpvr_device	*dev = fh->dev;

	if (!dev)
		return -ENODEV;

	mutex_lock(&dev->io_mutex);
	if (!(--dev->open_count) && dev->status == STATUS_STREAMING)
		hdpvr_stop_streaming(dev);

	mutex_unlock(&dev->io_mutex);

	return 0;
}