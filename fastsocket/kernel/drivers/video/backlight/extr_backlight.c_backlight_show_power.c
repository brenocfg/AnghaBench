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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int power; } ;
struct backlight_device {TYPE_1__ props; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct backlight_device* to_backlight_device (struct device*) ; 

__attribute__((used)) static ssize_t backlight_show_power(struct device *dev,
		struct device_attribute *attr,char *buf)
{
	struct backlight_device *bd = to_backlight_device(dev);

	return sprintf(buf, "%d\n", bd->props.power);
}