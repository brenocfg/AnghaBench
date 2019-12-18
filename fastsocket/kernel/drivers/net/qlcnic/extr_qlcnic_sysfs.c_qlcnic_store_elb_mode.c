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
struct qlcnic_adapter {int /*<<< orphan*/  state; int /*<<< orphan*/  netdev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  QLCNIC_ELB_MODE ; 
 int /*<<< orphan*/  __QLCNIC_ELB_INPROGRESS ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct qlcnic_adapter* dev_get_drvdata (struct device*) ; 
 int qlcnic_loopback_test (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 scalar_t__ strict_strtoul (char const*,int,unsigned long*) ; 
 unsigned long test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t qlcnic_store_elb_mode(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf, size_t len)
{
	struct qlcnic_adapter *adapter = dev_get_drvdata(dev);
	unsigned long new;
	int err;

	if (strict_strtoul(buf, 2, &new))
		return -EINVAL;

	if (new == test_and_set_bit(__QLCNIC_ELB_INPROGRESS, &adapter->state))
		return len;

	rtnl_lock();
	err = qlcnic_loopback_test(adapter->netdev, QLCNIC_ELB_MODE);
	rtnl_unlock();

	clear_bit(__QLCNIC_ELB_INPROGRESS, &adapter->state);

	if (!err)
		err = len;

	return err;
}