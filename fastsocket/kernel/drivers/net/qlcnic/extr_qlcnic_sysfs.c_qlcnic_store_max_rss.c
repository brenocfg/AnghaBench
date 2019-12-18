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
struct qlcnic_adapter {int flags; unsigned long max_sds_rings; int /*<<< orphan*/  state; struct net_device* netdev; } ;
struct net_device {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int QLCNIC_MSIX_ENABLED ; 
 int QLCNIC_MSI_ENABLED ; 
 int /*<<< orphan*/  __QLCNIC_RESETTING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct qlcnic_adapter* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,unsigned long) ; 
 int qlcnic_set_max_rss (struct qlcnic_adapter*,unsigned long,size_t) ; 
 scalar_t__ qlcnic_sriov_vf_check (struct qlcnic_adapter*) ; 
 int qlcnic_validate_max_rss (struct qlcnic_adapter*,unsigned long) ; 
 scalar_t__ strict_strtoul (char const*,int,unsigned long*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t qlcnic_store_max_rss(struct device *dev,
				    struct device_attribute *attr,
				    const char *buf, size_t len)
{
	struct qlcnic_adapter *adapter = dev_get_drvdata(dev);
	struct net_device *netdev = adapter->netdev;
	unsigned long data;
	int err;

	if (qlcnic_sriov_vf_check(adapter))
		return -EOPNOTSUPP;

	if (test_and_set_bit(__QLCNIC_RESETTING, &adapter->state))
		return -EBUSY;

	if (strict_strtoul(buf, 10, &data)) {
		err = -EINVAL;
		goto done;
	}

	if (!(adapter->flags & (QLCNIC_MSI_ENABLED | QLCNIC_MSIX_ENABLED))) {
		netdev_err(netdev, "no msix or msi support, hence no rss\n");
		err = -EINVAL;
		goto done;
	}

	if (data == adapter->max_sds_rings) {
		err = len;
		goto done;
	}

	err = qlcnic_validate_max_rss(adapter, data);
	if (err) {
		netdev_err(netdev,
			   "rss_ring valid range[1 - %d] in powers of 2\n",
			    err);
		err = -EINVAL;
		goto done;
	}

	err = qlcnic_set_max_rss(adapter, data, len);
 done:
	clear_bit(__QLCNIC_RESETTING, &adapter->state);
	netdev_info(netdev, "allocated 0x%x sds rings\n",
			adapter->max_sds_rings);
	return err;
}