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
typedef  unsigned long uint64_t ;
typedef  unsigned long uint32_t ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct comedi_subdevice {int subdev_flags; int /*<<< orphan*/ * async; } ;
struct comedi_device_file_info {TYPE_1__* device; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int EINVAL ; 
 int SDF_CMD_WRITE ; 
 unsigned long bytes_per_kibi ; 
 struct comedi_subdevice* comedi_get_write_subdevice (struct comedi_device_file_info*) ; 
 struct comedi_device_file_info* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int resize_async_buffer (TYPE_1__*,struct comedi_subdevice* const,int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ strict_strtoul (char const*,int,unsigned long*) ; 

__attribute__((used)) static ssize_t store_write_buffer_kb(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf, size_t count)
{
	struct comedi_device_file_info *info = dev_get_drvdata(dev);
	unsigned long new_size_kb;
	uint64_t new_size;
	int retval;
	struct comedi_subdevice *const write_subdevice =
	    comedi_get_write_subdevice(info);

	if (strict_strtoul(buf, 10, &new_size_kb))
		return -EINVAL;
	if (new_size_kb != (uint32_t) new_size_kb)
		return -EINVAL;
	new_size = ((uint64_t) new_size_kb) * bytes_per_kibi;
	if (new_size != (uint32_t) new_size)
		return -EINVAL;

	mutex_lock(&info->device->mutex);
	if (write_subdevice == NULL ||
	    (write_subdevice->subdev_flags & SDF_CMD_WRITE) == 0 ||
	    write_subdevice->async == NULL) {
		mutex_unlock(&info->device->mutex);
		return -EINVAL;
	}
	retval = resize_async_buffer(info->device, write_subdevice,
				     write_subdevice->async, new_size);
	mutex_unlock(&info->device->mutex);

	if (retval < 0)
		return retval;
	return count;
}