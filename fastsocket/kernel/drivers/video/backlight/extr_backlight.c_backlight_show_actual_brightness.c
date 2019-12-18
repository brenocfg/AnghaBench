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
struct backlight_device {int /*<<< orphan*/  ops_lock; TYPE_1__* ops; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int (* get_brightness ) (struct backlight_device*) ;} ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sprintf (char*,char*,int) ; 
 int stub1 (struct backlight_device*) ; 
 int stub2 (struct backlight_device*) ; 
 struct backlight_device* to_backlight_device (struct device*) ; 

__attribute__((used)) static ssize_t backlight_show_actual_brightness(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	int rc = -ENXIO;
	struct backlight_device *bd = to_backlight_device(dev);

	mutex_lock(&bd->ops_lock);
	if (bd->ops && bd->ops->get_brightness)
		rc = sprintf(buf, "%d\n", bd->ops->get_brightness(bd));
	mutex_unlock(&bd->ops_lock);

	return rc;
}