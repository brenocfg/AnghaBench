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
struct lm93_data {int /*<<< orphan*/ * auto_pwm_min_hyst; int /*<<< orphan*/  sfc2; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int LM93_TEMP_OFFSET_FROM_REG (int /*<<< orphan*/ ,int) ; 
 int LM93_TEMP_OFFSET_MODE_FROM_REG (int /*<<< orphan*/ ,int) ; 
 struct lm93_data* lm93_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t show_temp_auto_offset_hyst(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	int nr = (to_sensor_dev_attr(attr))->index;
	struct lm93_data *data = lm93_update_device(dev);
	int mode = LM93_TEMP_OFFSET_MODE_FROM_REG(data->sfc2, nr);
	return sprintf(buf,"%d\n",LM93_TEMP_OFFSET_FROM_REG(
					data->auto_pwm_min_hyst[nr/2], mode));
}