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
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  led_red ; 
 int /*<<< orphan*/  simple_strtol (char const*,char**,int) ; 
 int /*<<< orphan*/  toneport_update_led (struct device*) ; 

__attribute__((used)) static ssize_t toneport_set_led_red(struct device *dev,
				    struct device_attribute *attr,
				    const char *buf, size_t count)
{
	char *c;
	led_red = simple_strtol(buf, &c, 10);
	toneport_update_led(dev);
	return count;
}