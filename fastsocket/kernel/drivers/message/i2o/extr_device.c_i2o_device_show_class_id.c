#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int class_id; } ;
struct i2o_device {TYPE_1__ lct_data; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 scalar_t__ strlen (char*) ; 
 struct i2o_device* to_i2o_device (struct device*) ; 

__attribute__((used)) static ssize_t i2o_device_show_class_id(struct device *dev,
					struct device_attribute *attr,
					char *buf)
{
	struct i2o_device *i2o_dev = to_i2o_device(dev);

	sprintf(buf, "0x%03x\n", i2o_dev->lct_data.class_id);
	return strlen(buf) + 1;
}