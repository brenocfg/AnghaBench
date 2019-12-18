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
typedef  unsigned long uint64_t ;
typedef  unsigned long uint32_t ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct comedi_subdevice {int subdev_flags; TYPE_1__* async; } ;
struct comedi_device_file_info {TYPE_2__* device; } ;
typedef  size_t ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_3__ {unsigned long max_bufsize; } ;

/* Variables and functions */
 size_t EINVAL ; 
 int SDF_CMD_READ ; 
 unsigned long bytes_per_kibi ; 
 struct comedi_subdevice* comedi_get_read_subdevice (struct comedi_device_file_info*) ; 
 struct comedi_device_file_info* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strict_strtoul (char const*,int,unsigned long*) ; 

__attribute__((used)) static ssize_t store_max_read_buffer_kb(struct device *dev,
					struct device_attribute *attr,
					const char *buf, size_t count)
{
	struct comedi_device_file_info *info = dev_get_drvdata(dev);
	unsigned long new_max_size_kb;
	uint64_t new_max_size;
	struct comedi_subdevice *const read_subdevice =
	    comedi_get_read_subdevice(info);

	if (strict_strtoul(buf, 10, &new_max_size_kb))
		return -EINVAL;
	if (new_max_size_kb != (uint32_t) new_max_size_kb)
		return -EINVAL;
	new_max_size = ((uint64_t) new_max_size_kb) * bytes_per_kibi;
	if (new_max_size != (uint32_t) new_max_size)
		return -EINVAL;

	mutex_lock(&info->device->mutex);
	if (read_subdevice == NULL ||
	    (read_subdevice->subdev_flags & SDF_CMD_READ) == 0 ||
	    read_subdevice->async == NULL) {
		mutex_unlock(&info->device->mutex);
		return -EINVAL;
	}
	read_subdevice->async->max_bufsize = new_max_size;
	mutex_unlock(&info->device->mutex);

	return count;
}