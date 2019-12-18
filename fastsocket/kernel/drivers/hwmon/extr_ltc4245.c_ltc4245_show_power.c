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
struct sensor_device_attribute {scalar_t__ index; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 unsigned int abs (int const) ; 
 unsigned int ltc4245_get_current (struct device*,scalar_t__) ; 
 int ltc4245_get_voltage (struct device*,scalar_t__) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,unsigned int const) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t ltc4245_show_power(struct device *dev,
				  struct device_attribute *da,
				  char *buf)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(da);
	const unsigned int curr = ltc4245_get_current(dev, attr->index);
	const int output_voltage = ltc4245_get_voltage(dev, attr->index+1);

	/* current in mA * voltage in mV == power in uW */
	const unsigned int power = abs(output_voltage * curr);

	return snprintf(buf, PAGE_SIZE, "%u\n", power);
}