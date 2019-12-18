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
struct w83793_data {int /*<<< orphan*/  vrm; int /*<<< orphan*/ * vid; } ;
struct sensor_device_attribute_2 {int index; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 
 int vid_from_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct w83793_data* w83793_update_device (struct device*) ; 

__attribute__((used)) static ssize_t
show_vid(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct w83793_data *data = w83793_update_device(dev);
	struct sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	int index = sensor_attr->index;

	return sprintf(buf, "%d\n", vid_from_reg(data->vid[index], data->vrm));
}