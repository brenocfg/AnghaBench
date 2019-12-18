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
typedef  int u8 ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int DS1672_REG_CONTROL_EOSC ; 
 int ds1672_get_control (struct i2c_client*,int*) ; 
 int sprintf (char*,char*,char*) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t show_control(struct device *dev, struct device_attribute *attr,
			    char *buf)
{
	struct i2c_client *client = to_i2c_client(dev);
	u8 control;
	int err;

	err = ds1672_get_control(client, &control);
	if (err)
		return err;

	return sprintf(buf, "%s\n", (control & DS1672_REG_CONTROL_EOSC)
		       ? "disabled" : "enabled");
}