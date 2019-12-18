#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct comedi_subdevice {int subdev_flags; TYPE_1__* async; } ;
struct comedi_device_file_info {TYPE_2__* device; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_3__ {unsigned int max_bufsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int SDF_CMD_READ ; 
 unsigned int bytes_per_kibi ; 
 struct comedi_subdevice* comedi_get_read_subdevice (struct comedi_device_file_info*) ; 
 struct comedi_device_file_info* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,unsigned int) ; 

__attribute__((used)) static ssize_t show_max_read_buffer_kb(struct device *dev,
				       struct device_attribute *attr, char *buf)
{
	ssize_t retval;
	struct comedi_device_file_info *info = dev_get_drvdata(dev);
	unsigned max_buffer_size_kb = 0;
	struct comedi_subdevice *const read_subdevice =
	    comedi_get_read_subdevice(info);

	mutex_lock(&info->device->mutex);
	if (read_subdevice &&
	    (read_subdevice->subdev_flags & SDF_CMD_READ) &&
	    read_subdevice->async) {
		max_buffer_size_kb = read_subdevice->async->max_bufsize /
		    bytes_per_kibi;
	}
	retval = snprintf(buf, PAGE_SIZE, "%i\n", max_buffer_size_kb);
	mutex_unlock(&info->device->mutex);

	return retval;
}