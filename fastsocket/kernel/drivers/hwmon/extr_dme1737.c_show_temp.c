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
typedef  int u16 ;
struct sensor_device_attribute_2 {int index; int nr; } ;
struct dme1737_data {int alarms; int /*<<< orphan*/ * temp; int /*<<< orphan*/ * temp_offset; int /*<<< orphan*/ * temp_max; int /*<<< orphan*/ * temp_min; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int* DME1737_BIT_ALARM_TEMP ; 
#define  SYS_TEMP_ALARM 133 
#define  SYS_TEMP_FAULT 132 
#define  SYS_TEMP_INPUT 131 
#define  SYS_TEMP_MAX 130 
#define  SYS_TEMP_MIN 129 
#define  SYS_TEMP_OFFSET 128 
 int TEMP_FROM_REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 struct dme1737_data* dme1737_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t show_temp(struct device *dev, struct device_attribute *attr,
			 char *buf)
{
	struct dme1737_data *data = dme1737_update_device(dev);
	struct sensor_device_attribute_2
		*sensor_attr_2 = to_sensor_dev_attr_2(attr);
	int ix = sensor_attr_2->index;
	int fn = sensor_attr_2->nr;
	int res;

	switch (fn) {
	case SYS_TEMP_INPUT:
		res = TEMP_FROM_REG(data->temp[ix], 16);
		break;
	case SYS_TEMP_MIN:
		res = TEMP_FROM_REG(data->temp_min[ix], 8);
		break;
	case SYS_TEMP_MAX:
		res = TEMP_FROM_REG(data->temp_max[ix], 8);
		break;
	case SYS_TEMP_OFFSET:
		res = TEMP_FROM_REG(data->temp_offset[ix], 8);
		break;
	case SYS_TEMP_ALARM:
		res = (data->alarms >> DME1737_BIT_ALARM_TEMP[ix]) & 0x01;
		break;
	case SYS_TEMP_FAULT:
		res = (((u16)data->temp[ix] & 0xff00) == 0x8000);
		break;
	default:
		res = 0;
		dev_dbg(dev, "Unknown function %d.\n", fn);
	}

	return sprintf(buf, "%d\n", res);
}