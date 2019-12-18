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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
typedef  int s16 ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SENSOR_X ; 
 int /*<<< orphan*/  SENSOR_Y ; 
 int /*<<< orphan*/  SENSOR_Z ; 
 int /*<<< orphan*/  applesmc_lock ; 
 int applesmc_read_motion_sensor (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,int,int,int) ; 

__attribute__((used)) static ssize_t applesmc_position_show(struct device *dev,
				   struct device_attribute *attr, char *buf)
{
	int ret;
	s16 x, y, z;

	mutex_lock(&applesmc_lock);

	ret = applesmc_read_motion_sensor(SENSOR_X, &x);
	if (ret)
		goto out;
	ret = applesmc_read_motion_sensor(SENSOR_Y, &y);
	if (ret)
		goto out;
	ret = applesmc_read_motion_sensor(SENSOR_Z, &z);
	if (ret)
		goto out;

out:
	mutex_unlock(&applesmc_lock);
	if (ret)
		return ret;
	else
		return snprintf(buf, PAGE_SIZE, "(%d,%d,%d)\n", x, y, z);
}