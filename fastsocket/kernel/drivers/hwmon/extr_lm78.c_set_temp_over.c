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
struct lm78_data {int /*<<< orphan*/  update_lock; int /*<<< orphan*/  temp_over; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  LM78_REG_TEMP_OVER ; 
 int /*<<< orphan*/  TEMP_TO_REG (long) ; 
 struct lm78_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  lm78_write_value (struct lm78_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 long simple_strtol (char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static ssize_t set_temp_over(struct device *dev, struct device_attribute *da,
			     const char *buf, size_t count)
{
	struct lm78_data *data = dev_get_drvdata(dev);
	long val = simple_strtol(buf, NULL, 10);

	mutex_lock(&data->update_lock);
	data->temp_over = TEMP_TO_REG(val);
	lm78_write_value(data, LM78_REG_TEMP_OVER, data->temp_over);
	mutex_unlock(&data->update_lock);
	return count;
}