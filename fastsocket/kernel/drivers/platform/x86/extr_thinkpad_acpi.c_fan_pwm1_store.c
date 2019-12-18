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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int ERESTARTSYS ; 
 int TP_EC_FAN_AUTO ; 
 int TP_EC_FAN_FULLSPEED ; 
 int fan_get_status (int*) ; 
 int /*<<< orphan*/  fan_mutex ; 
 int fan_set_level (int) ; 
 int /*<<< orphan*/  fan_update_desired_level (int) ; 
 int /*<<< orphan*/  fan_watchdog_reset () ; 
 scalar_t__ mutex_lock_killable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ parse_strtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  tpacpi_disclose_usertask (char*,char*,unsigned long) ; 

__attribute__((used)) static ssize_t fan_pwm1_store(struct device *dev,
			      struct device_attribute *attr,
			      const char *buf, size_t count)
{
	unsigned long s;
	int rc;
	u8 status, newlevel;

	if (parse_strtoul(buf, 255, &s))
		return -EINVAL;

	tpacpi_disclose_usertask("hwmon pwm1",
			"set fan speed to %lu\n", s);

	/* scale down from 0-255 to 0-7 */
	newlevel = (s >> 5) & 0x07;

	if (mutex_lock_killable(&fan_mutex))
		return -ERESTARTSYS;

	rc = fan_get_status(&status);
	if (!rc && (status &
		    (TP_EC_FAN_AUTO | TP_EC_FAN_FULLSPEED)) == 0) {
		rc = fan_set_level(newlevel);
		if (rc == -ENXIO)
			rc = -EINVAL;
		else if (!rc) {
			fan_update_desired_level(newlevel);
			fan_watchdog_reset();
		}
	}

	mutex_unlock(&fan_mutex);
	return (rc)? rc : count;
}