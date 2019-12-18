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
struct lm90_data {scalar_t__ kind; int /*<<< orphan*/ * temp11; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ adt7461 ; 
 struct lm90_data* lm90_update_device (struct device*) ; 
 scalar_t__ lm99 ; 
 scalar_t__ max6646 ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int temp_from_s16 (int /*<<< orphan*/ ) ; 
 int temp_from_u16 (int /*<<< orphan*/ ) ; 
 int temp_from_u16_adt7461 (struct lm90_data*,int /*<<< orphan*/ ) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t show_temp11(struct device *dev, struct device_attribute *devattr,
			   char *buf)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	struct lm90_data *data = lm90_update_device(dev);
	int temp;

	if (data->kind == adt7461)
		temp = temp_from_u16_adt7461(data, data->temp11[attr->index]);
	else if (data->kind == max6646)
		temp = temp_from_u16(data->temp11[attr->index]);
	else
		temp = temp_from_s16(data->temp11[attr->index]);

	/* +16 degrees offset for temp2 for the LM99 */
	if (data->kind == lm99 &&  attr->index <= 2)
		temp += 16000;

	return sprintf(buf, "%d\n", temp);
}