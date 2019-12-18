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
struct asus_oled_dev {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 scalar_t__ dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  enable_oled (struct asus_oled_dev*,int) ; 
 int strict_strtoul (char const*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t class_set_enabled(struct device *device,
				 struct device_attribute *attr,
				 const char *buf, size_t count)
{
	struct asus_oled_dev *odev =
		(struct asus_oled_dev *) dev_get_drvdata(device);

	int temp = strict_strtoul(buf, 10, NULL);

	enable_oled(odev, temp);

	return count;
}