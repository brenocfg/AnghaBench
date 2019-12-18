#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct qlcnic_adapter {int /*<<< orphan*/  state; TYPE_1__* ahw; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int capabilities; } ;

/* Variables and functions */
 int EINVAL ; 
 int QLCNIC_FW_CAPABILITY_BDG ; 
 int /*<<< orphan*/  __QLCNIC_DEV_UP ; 
 struct qlcnic_adapter* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  qlcnic_config_bridged_mode (struct qlcnic_adapter*,int) ; 
 scalar_t__ strict_strtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t qlcnic_store_bridged_mode(struct device *dev,
					 struct device_attribute *attr,
					 const char *buf, size_t len)
{
	struct qlcnic_adapter *adapter = dev_get_drvdata(dev);
	unsigned long new;
	int ret = -EINVAL;

	if (!(adapter->ahw->capabilities & QLCNIC_FW_CAPABILITY_BDG))
		goto err_out;

	if (!test_bit(__QLCNIC_DEV_UP, &adapter->state))
		goto err_out;

	if (strict_strtoul(buf, 2, &new))
		goto err_out;

	if (!qlcnic_config_bridged_mode(adapter, !!new))
		ret = len;

err_out:
	return ret;
}