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
struct sensor_device_attribute {size_t index; } ;
struct max6650_data {int* tach; int /*<<< orphan*/  count; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int DIV_FROM_REG (int /*<<< orphan*/ ) ; 
 struct max6650_data* max6650_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t get_fan(struct device *dev, struct device_attribute *devattr,
		       char *buf)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	struct max6650_data *data = max6650_update_device(dev);
	int rpm;

	/*
	* Calculation details:
	*
	* Each tachometer counts over an interval given by the "count"
	* register (0.25, 0.5, 1 or 2 seconds). This module assumes
	* that the fans produce two pulses per revolution (this seems
	* to be the most common).
	*/

	rpm = ((data->tach[attr->index] * 120) / DIV_FROM_REG(data->count));
	return sprintf(buf, "%d\n", rpm);
}