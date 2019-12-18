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
struct ad7877 {unsigned long dac; int /*<<< orphan*/  mutex; int /*<<< orphan*/  spi; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int AD7877_DAC_CONF ; 
 int /*<<< orphan*/  AD7877_REG_DAC ; 
 int /*<<< orphan*/  ad7877_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ad7877* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int strict_strtoul (char const*,int,unsigned long*) ; 

__attribute__((used)) static ssize_t ad7877_dac_store(struct device *dev,
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
	ts->dac = val & 0xFF;
	ad7877_write(ts->spi, AD7877_REG_DAC, (ts->dac << 4) | AD7877_DAC_CONF);
	mutex_unlock(&ts->mutex);

	return count;
}