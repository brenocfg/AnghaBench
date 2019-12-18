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
struct sensor_device_attribute_2 {int index; int nr; } ;
struct dme1737_data {int config2; int /*<<< orphan*/ * zone_abs; int /*<<< orphan*/ * pwm_freq; int /*<<< orphan*/ * zone_low; int /*<<< orphan*/ * zone_hyst; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
#define  SYS_ZONE_AUTO_CHANNELS_TEMP 132 
#define  SYS_ZONE_AUTO_POINT1_TEMP 131 
#define  SYS_ZONE_AUTO_POINT1_TEMP_HYST 130 
#define  SYS_ZONE_AUTO_POINT2_TEMP 129 
#define  SYS_ZONE_AUTO_POINT3_TEMP 128 
 int TEMP_FROM_REG (int /*<<< orphan*/ ,int) ; 
 int TEMP_HYST_FROM_REG (int /*<<< orphan*/ ,int) ; 
 int TEMP_RANGE_FROM_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 struct dme1737_data* dme1737_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t show_zone(struct device *dev, struct device_attribute *attr,
			 char *buf)
{
	struct dme1737_data *data = dme1737_update_device(dev);
	struct sensor_device_attribute_2
		*sensor_attr_2 = to_sensor_dev_attr_2(attr);
	int ix = sensor_attr_2->index;
	int fn = sensor_attr_2->nr;
	int res;

	switch (fn) {
	case SYS_ZONE_AUTO_CHANNELS_TEMP:
		/* check config2 for non-standard temp-to-zone mapping */
		if ((ix == 1) && (data->config2 & 0x02)) {
			res = 4;
		} else {
			res = 1 << ix;
		}
		break;
	case SYS_ZONE_AUTO_POINT1_TEMP_HYST:
		res = TEMP_FROM_REG(data->zone_low[ix], 8) -
		      TEMP_HYST_FROM_REG(data->zone_hyst[ix == 2], ix);
		break;
	case SYS_ZONE_AUTO_POINT1_TEMP:
		res = TEMP_FROM_REG(data->zone_low[ix], 8);
		break;
	case SYS_ZONE_AUTO_POINT2_TEMP:
		/* pwm_freq holds the temp range bits in the upper nibble */
		res = TEMP_FROM_REG(data->zone_low[ix], 8) +
		      TEMP_RANGE_FROM_REG(data->pwm_freq[ix]);
		break;
	case SYS_ZONE_AUTO_POINT3_TEMP:
		res = TEMP_FROM_REG(data->zone_abs[ix], 8);
		break;
	default:
		res = 0;
		dev_dbg(dev, "Unknown function %d.\n", fn);
	}

	return sprintf(buf, "%d\n", res);
}