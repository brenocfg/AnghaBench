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
struct ad7877 {int gpio4; int gpio3; int /*<<< orphan*/  mutex; int /*<<< orphan*/  spi; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int AD7877_EXTW_GPIO_DATA ; 
 int /*<<< orphan*/  AD7877_REG_EXTWRITE ; 
 int /*<<< orphan*/  ad7877_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ad7877* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int strict_strtoul (char const*,int,unsigned long*) ; 

__attribute__((used)) static ssize_t ad7877_gpio4_store(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf, size_t count)
{
	struct ad7877 *ts = dev_get_drvdata(dev);
	unsigned long val;
	int error;

	error = strict_strtoul(buf, 10, &val);
	if (error)
		return error;

	mutex_lock(&ts->mutex);
	ts->gpio4 = !!val;
	ad7877_write(ts->spi, AD7877_REG_EXTWRITE, AD7877_EXTW_GPIO_DATA |
		     (ts->gpio4 << 4) | (ts->gpio3 << 5));
	mutex_unlock(&ts->mutex);

	return count;
}