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
struct ad7879 {int gpio; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct ad7879* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t ad7879_gpio_show(struct device *dev,
				     struct device_attribute *attr, char *buf)
{
	struct ad7879 *ts = dev_get_drvdata(dev);

	return sprintf(buf, "%u\n", ts->gpio);
}