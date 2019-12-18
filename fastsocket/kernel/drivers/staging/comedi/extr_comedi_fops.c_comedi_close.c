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
struct inode {int dummy; } ;
struct file {int f_flags; } ;
struct comedi_subdevice {struct file* lock; struct file* busy; } ;
struct comedi_device_file_info {struct comedi_device* device; } ;
struct comedi_device {int n_subdevices; int use_count; int /*<<< orphan*/  mutex; TYPE_1__* driver; scalar_t__ attached; int /*<<< orphan*/  (* close ) (struct comedi_device*) ;struct comedi_subdevice* subdevices; } ;
struct TYPE_2__ {int /*<<< orphan*/  module; } ;

/* Variables and functions */
 int FASYNC ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  comedi_fasync (int,struct file*,int /*<<< orphan*/ ) ; 
 struct comedi_device_file_info* comedi_get_device_file_info (unsigned int const) ; 
 int /*<<< orphan*/  do_cancel (struct comedi_device*,struct comedi_subdevice*) ; 
 unsigned int iminor (struct inode*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct comedi_device*) ; 

__attribute__((used)) static int comedi_close(struct inode *inode, struct file *file)
{
	const unsigned minor = iminor(inode);
	struct comedi_device_file_info *dev_file_info =
	    comedi_get_device_file_info(minor);
	struct comedi_device *dev = dev_file_info->device;
	struct comedi_subdevice *s = NULL;
	int i;

	mutex_lock(&dev->mutex);

	if (dev->subdevices) {
		for (i = 0; i < dev->n_subdevices; i++) {
			s = dev->subdevices + i;

			if (s->busy == file)
				do_cancel(dev, s);
			if (s->lock == file)
				s->lock = NULL;
		}
	}
	if (dev->attached && dev->use_count == 1 && dev->close)
		dev->close(dev);

	module_put(THIS_MODULE);
	if (dev->attached)
		module_put(dev->driver->module);

	dev->use_count--;

	mutex_unlock(&dev->mutex);

	if (file->f_flags & FASYNC)
		comedi_fasync(-1, file, 0);

	return 0;
}