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
struct sensor_device_attribute_2 {int index; int nr; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct abituguru_data {int* alarms; int** bank1_settings; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 struct abituguru_data* abituguru_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t show_bank1_alarm(struct device *dev,
	struct device_attribute *devattr, char *buf)
{
	struct sensor_device_attribute_2 *attr = to_sensor_dev_attr_2(devattr);
	struct abituguru_data *data = abituguru_update_device(dev);
	if (!data)
		return -EIO;
	/* See if the alarm bit for this sensor is set, and if the
	   alarm matches the type of alarm we're looking for (for volt
	   it can be either low or high). The type is stored in a few
	   readonly bits in the settings part of the relevant sensor.
	   The bitmask of the type is passed to us in attr->nr. */
	if ((data->alarms[attr->index / 8] & (0x01 << (attr->index % 8))) &&
			(data->bank1_settings[attr->index][0] & attr->nr))
		return sprintf(buf, "1\n");
	else
		return sprintf(buf, "0\n");
}