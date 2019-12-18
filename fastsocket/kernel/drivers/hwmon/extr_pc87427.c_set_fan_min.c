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
struct sensor_device_attribute {int index; } ;
struct pc87427_data {int* address; int /*<<< orphan*/  lock; int /*<<< orphan*/ * fan_min; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  BANK_FM (int) ; 
 int /*<<< orphan*/  FAN_STATUS_MONEN ; 
 size_t LD_FAN ; 
 scalar_t__ PC87427_REG_BANK ; 
 scalar_t__ PC87427_REG_FAN_MIN ; 
 scalar_t__ PC87427_REG_FAN_STATUS ; 
 struct pc87427_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  fan_to_reg (unsigned long) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned long simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t set_fan_min(struct device *dev, struct device_attribute
			   *devattr, const char *buf, size_t count)
{
	struct pc87427_data *data = dev_get_drvdata(dev);
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	int nr = attr->index;
	unsigned long val = simple_strtoul(buf, NULL, 10);
	int iobase = data->address[LD_FAN];

	mutex_lock(&data->lock);
	outb(BANK_FM(nr), iobase + PC87427_REG_BANK);
	/* The low speed limit registers are read-only while monitoring
	   is enabled, so we have to disable monitoring, then change the
	   limit, and finally enable monitoring again. */
	outb(0, iobase + PC87427_REG_FAN_STATUS);
	data->fan_min[nr] = fan_to_reg(val);
	outw(data->fan_min[nr], iobase + PC87427_REG_FAN_MIN);
	outb(FAN_STATUS_MONEN, iobase + PC87427_REG_FAN_STATUS);
	mutex_unlock(&data->lock);

	return count;
}