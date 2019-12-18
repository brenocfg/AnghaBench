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
struct net_device {int dummy; } ;
struct ethtool_wolinfo {int wolopts; } ;
struct be_adapter {int wol; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int WAKE_MAGIC ; 
 int /*<<< orphan*/  be_is_wol_supported (struct be_adapter*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 struct be_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
be_set_wol(struct net_device *netdev, struct ethtool_wolinfo *wol)
{
	struct be_adapter *adapter = netdev_priv(netdev);

	if (wol->wolopts & ~WAKE_MAGIC)
		return -EOPNOTSUPP;

	if (!be_is_wol_supported(adapter)) {
		dev_warn(&adapter->pdev->dev, "WOL not supported\n");
		return -EOPNOTSUPP;
	}

	if (wol->wolopts & WAKE_MAGIC)
		adapter->wol = true;
	else
		adapter->wol = false;

	return 0;
}