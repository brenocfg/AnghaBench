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
struct w1_slave {int dummy; } ;
struct w1_reg_num {scalar_t__ id; int /*<<< orphan*/  family; } ;
struct w1_master {int /*<<< orphan*/  mutex; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ,unsigned long long) ; 
 struct w1_master* dev_to_w1_master (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ w1_atoreg_num (struct device*,char const*,size_t,struct w1_reg_num*) ; 
 int /*<<< orphan*/  w1_slave_detach (struct w1_slave*) ; 
 struct w1_slave* w1_slave_search_device (struct w1_master*,struct w1_reg_num*) ; 

__attribute__((used)) static ssize_t w1_master_attribute_store_remove(struct device *dev,
						struct device_attribute *attr,
						const char *buf, size_t count)
{
	struct w1_master *md = dev_to_w1_master(dev);
	struct w1_reg_num rn;
	struct w1_slave *sl;
	ssize_t result = count;

	if (w1_atoreg_num(dev, buf, count, &rn))
		return -EINVAL;

	mutex_lock(&md->mutex);
	sl = w1_slave_search_device(md, &rn);
	if (sl) {
		w1_slave_detach(sl);
	} else {
		dev_info(dev, "Device %02x-%012llx doesn't exists\n", rn.family,
			(unsigned long long)rn.id);
		result = -EINVAL;
	}
	mutex_unlock(&md->mutex);

	return result;
}