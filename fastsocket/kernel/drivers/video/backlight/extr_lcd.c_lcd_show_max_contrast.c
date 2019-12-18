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
struct TYPE_2__ {int max_contrast; } ;
struct lcd_device {TYPE_1__ props; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct lcd_device* to_lcd_device (struct device*) ; 

__attribute__((used)) static ssize_t lcd_show_max_contrast(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct lcd_device *ld = to_lcd_device(dev);

	return sprintf(buf, "%d\n", ld->props.max_contrast);
}