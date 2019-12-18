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
struct lm93_data {int /*<<< orphan*/ * block5; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int LM93_FAN_FROM_REG (int /*<<< orphan*/ ) ; 
 struct lm93_data* lm93_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t show_fan_input(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct sensor_device_attribute *s_attr = to_sensor_dev_attr(attr);
	int nr = s_attr->index;
	struct lm93_data *data = lm93_update_device(dev);

	return sprintf(buf,"%d\n",LM93_FAN_FROM_REG(data->block5[nr]));
}