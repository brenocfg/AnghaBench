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
struct sensor_device_attribute_2 {int index; int nr; } ;
struct TYPE_2__ {int /*<<< orphan*/ * offset; } ;
struct lm93_data {TYPE_1__ block10; int /*<<< orphan*/  sfc2; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int LM93_TEMP_AUTO_OFFSET_FROM_REG (int /*<<< orphan*/ ,int,int) ; 
 int LM93_TEMP_OFFSET_MODE_FROM_REG (int /*<<< orphan*/ ,int) ; 
 struct lm93_data* lm93_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t show_temp_auto_offset(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct sensor_device_attribute_2 *s_attr = to_sensor_dev_attr_2(attr);
	int nr = s_attr->index;
	int ofs = s_attr->nr;
	struct lm93_data *data = lm93_update_device(dev);
	int mode = LM93_TEMP_OFFSET_MODE_FROM_REG(data->sfc2, nr);
	return sprintf(buf,"%d\n",
	       LM93_TEMP_AUTO_OFFSET_FROM_REG(data->block10.offset[ofs],
					      nr,mode));
}