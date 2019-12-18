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
struct via686a_data {int /*<<< orphan*/ * in; } ;
struct sensor_device_attribute {int index; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  IN_FROM_REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 
 struct via686a_data* via686a_update_device (struct device*) ; 

__attribute__((used)) static ssize_t show_in(struct device *dev, struct device_attribute *da,
		char *buf) {
	struct via686a_data *data = via686a_update_device(dev);
	struct sensor_device_attribute *attr = to_sensor_dev_attr(da);
	int nr = attr->index;
	return sprintf(buf, "%ld\n", IN_FROM_REG(data->in[nr], nr));
}