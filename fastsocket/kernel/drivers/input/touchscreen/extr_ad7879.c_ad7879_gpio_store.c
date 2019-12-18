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
struct ad7879 {int gpio; int cmd_crtl2; int /*<<< orphan*/  mutex; int /*<<< orphan*/  bus; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int AD7879_GPIO_DATA ; 
 int /*<<< orphan*/  AD7879_REG_CTRL2 ; 
 int ad7879_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ad7879* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int strict_strtoul (char const*,int,unsigned long*) ; 

__attribute__((used)) static ssize_t ad7879_gpio_store(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf, size_t count)
{
	struct ad7879 *ts = dev_get_drvdata(dev);
	unsigned long val;
	int error;

	error = strict_strtoul(buf, 10, &val);
	if (error)
		return error;

	mutex_lock(&ts->mutex);
	ts->gpio = !!val;
	error = ad7879_write(ts->bus, AD7879_REG_CTRL2,
			   ts->gpio ?
				ts->cmd_crtl2 & ~AD7879_GPIO_DATA :
				ts->cmd_crtl2 | AD7879_GPIO_DATA);
	mutex_unlock(&ts->mutex);

	return error ? : count;
}