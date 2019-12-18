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
struct pc87427_data {int fan_enabled; int /*<<< orphan*/  lock; scalar_t__ last_updated; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 struct pc87427_data* dev_get_drvdata (struct device*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pc87427_readall_fan (struct pc87427_data*,int) ; 
 int /*<<< orphan*/  time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static struct pc87427_data *pc87427_update_device(struct device *dev)
{
	struct pc87427_data *data = dev_get_drvdata(dev);
	int i;

	mutex_lock(&data->lock);
	if (!time_after(jiffies, data->last_updated + HZ)
	 && data->last_updated)
		goto done;

	/* Fans */
	for (i = 0; i < 8; i++) {
		if (!(data->fan_enabled & (1 << i)))
			continue;
		pc87427_readall_fan(data, i);
	}
	data->last_updated = jiffies;

done:
	mutex_unlock(&data->lock);
	return data;
}