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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adt7473_data {int* pwm_behavior; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int ADT7473_PWM_BHVR_SHIFT ; 
 int /*<<< orphan*/  BUG () ; 
 struct adt7473_data* adt7473_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t show_pwm_auto_temp(struct device *dev,
				  struct device_attribute *devattr,
				  char *buf)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	struct adt7473_data *data = adt7473_update_device(dev);
	int bhvr = data->pwm_behavior[attr->index] >> ADT7473_PWM_BHVR_SHIFT;

	switch (bhvr) {
	case 3:
	case 4:
	case 7:
		return sprintf(buf, "0\n");
	case 0:
	case 1:
	case 5:
	case 6:
		return sprintf(buf, "%d\n", bhvr + 1);
	case 2:
		return sprintf(buf, "4\n");
	}
	/* shouldn't ever get here */
	BUG();
}