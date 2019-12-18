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
struct device {int dummy; } ;
struct adp5520_bl {int /*<<< orphan*/  lock; int /*<<< orphan*/  master; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  adp5520_write (int /*<<< orphan*/ ,int,unsigned long) ; 
 struct adp5520_bl* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int strict_strtoul (char const*,int,unsigned long*) ; 

__attribute__((used)) static ssize_t adp5520_store(struct device *dev, const char *buf,
			 size_t count, int reg)
{
	struct adp5520_bl *data = dev_get_drvdata(dev);
	unsigned long val;
	int ret;

	ret = strict_strtoul(buf, 10, &val);
	if (ret)
		return ret;

	mutex_lock(&data->lock);
	adp5520_write(data->master, reg, val);
	mutex_unlock(&data->lock);

	return count;
}