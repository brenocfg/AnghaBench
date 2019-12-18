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
typedef  scalar_t__ u8 ;
struct env {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 scalar_t__ FAN_DATA_VALID (int) ; 
 int FAN_PERIOD_TO_RPM (int) ; 
 scalar_t__ IREG_FAN0 ; 
 struct env* dev_get_drvdata (struct device*) ; 
 scalar_t__ env_read (struct env*,scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t show_fan_speed(struct device *dev, struct device_attribute *attr, char *buf)
{
	int fan_nr = to_sensor_dev_attr(attr)->index;
	struct env *p = dev_get_drvdata(dev);
	int rpm, period;
	u8 val;

	val = env_read(p, IREG_FAN0 + fan_nr);
	period = (int) val << 8;
	if (FAN_DATA_VALID(period))
		rpm = FAN_PERIOD_TO_RPM(period);
	else
		rpm = 0;

	return sprintf(buf, "%d\n", rpm);
}