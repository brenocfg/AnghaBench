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

/* Variables and functions */
 int parse_arg (char const*,size_t,int*) ; 
 int /*<<< orphan*/  set_light_sens_level (int) ; 

__attribute__((used)) static ssize_t store_lslvl(struct device *dev, struct device_attribute *attr,
			   const char *buf, size_t count)
{
	int rv, value;

	rv = parse_arg(buf, count, &value);
	if (rv > 0) {
		value = (0 < value) ? ((15 < value) ? 15 : value) : 0;
		/* 0 <= value <= 15 */
		set_light_sens_level(value);
	}

	return rv;
}