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
struct qlcnic_adapter {TYPE_1__* netdev; } ;
struct net_device {int mtu; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int P3P_MAX_MTU ; 
 int P3P_MIN_MTU ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 
 int qlcnic_fw_cmd_set_mtu (struct qlcnic_adapter*,int) ; 

int qlcnic_change_mtu(struct net_device *netdev, int mtu)
{
	struct qlcnic_adapter *adapter = netdev_priv(netdev);
	int rc = 0;

	if (mtu < P3P_MIN_MTU || mtu > P3P_MAX_MTU) {
		dev_err(&adapter->netdev->dev, "%d bytes < mtu < %d bytes"
			" not supported\n", P3P_MAX_MTU, P3P_MIN_MTU);
		return -EINVAL;
	}

	rc = qlcnic_fw_cmd_set_mtu(adapter, mtu);

	if (!rc)
		netdev->mtu = mtu;

	return rc;
}