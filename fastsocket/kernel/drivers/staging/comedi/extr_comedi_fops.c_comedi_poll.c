#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct file {TYPE_1__* f_dentry; } ;
struct comedi_subdevice {TYPE_2__* async; int /*<<< orphan*/  busy; } ;
struct comedi_device_file_info {struct comedi_device* device; } ;
struct comedi_device {int /*<<< orphan*/  mutex; int /*<<< orphan*/  minor; int /*<<< orphan*/  attached; } ;
typedef  int /*<<< orphan*/  poll_table ;
struct TYPE_6__ {int /*<<< orphan*/  subdevice; int /*<<< orphan*/  prealloc_bufsz; int /*<<< orphan*/  wait_head; } ;
struct TYPE_5__ {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,int /*<<< orphan*/ ) ; 
 unsigned int POLLIN ; 
 unsigned int POLLOUT ; 
 unsigned int POLLRDNORM ; 
 unsigned int POLLWRNORM ; 
 int SRF_RUNNING ; 
 scalar_t__ bytes_per_sample (int /*<<< orphan*/ ) ; 
 scalar_t__ comedi_buf_read_n_available (TYPE_2__*) ; 
 int /*<<< orphan*/  comedi_buf_write_alloc (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ comedi_buf_write_n_allocated (TYPE_2__*) ; 
 struct comedi_device_file_info* comedi_get_device_file_info (unsigned int const) ; 
 struct comedi_subdevice* comedi_get_read_subdevice (struct comedi_device_file_info*) ; 
 int comedi_get_subdevice_runflags (struct comedi_subdevice*) ; 
 struct comedi_subdevice* comedi_get_write_subdevice (struct comedi_device_file_info*) ; 
 unsigned int iminor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int comedi_poll(struct file *file, poll_table * wait)
{
	unsigned int mask = 0;
	const unsigned minor = iminor(file->f_dentry->d_inode);
	struct comedi_device_file_info *dev_file_info =
	    comedi_get_device_file_info(minor);
	struct comedi_device *dev = dev_file_info->device;
	struct comedi_subdevice *read_subdev;
	struct comedi_subdevice *write_subdev;

	mutex_lock(&dev->mutex);
	if (!dev->attached) {
		DPRINTK("no driver configured on comedi%i\n", dev->minor);
		mutex_unlock(&dev->mutex);
		return 0;
	}

	mask = 0;
	read_subdev = comedi_get_read_subdevice(dev_file_info);
	if (read_subdev) {
		poll_wait(file, &read_subdev->async->wait_head, wait);
		if (!read_subdev->busy
		    || comedi_buf_read_n_available(read_subdev->async) > 0
		    || !(comedi_get_subdevice_runflags(read_subdev) &
			 SRF_RUNNING)) {
			mask |= POLLIN | POLLRDNORM;
		}
	}
	write_subdev = comedi_get_write_subdevice(dev_file_info);
	if (write_subdev) {
		poll_wait(file, &write_subdev->async->wait_head, wait);
		comedi_buf_write_alloc(write_subdev->async,
				       write_subdev->async->prealloc_bufsz);
		if (!write_subdev->busy
		    || !(comedi_get_subdevice_runflags(write_subdev) &
			 SRF_RUNNING)
		    || comedi_buf_write_n_allocated(write_subdev->async) >=
		    bytes_per_sample(write_subdev->async->subdevice)) {
			mask |= POLLOUT | POLLWRNORM;
		}
	}

	mutex_unlock(&dev->mutex);
	return mask;
}