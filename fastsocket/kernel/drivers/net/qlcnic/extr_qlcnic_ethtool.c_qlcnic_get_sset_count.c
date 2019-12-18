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
struct qlcnic_adapter {int flags; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETH_SS_STATS 129 
#define  ETH_SS_TEST 128 
 int QLCNIC_ESWITCH_ENABLED ; 
 int QLCNIC_STATS_LEN ; 
 int QLCNIC_TEST_LEN ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 
 int qlcnic_82xx_statistics () ; 
 int /*<<< orphan*/  qlcnic_83xx_check (struct qlcnic_adapter*) ; 
 int qlcnic_dev_statistics_len (struct qlcnic_adapter*) ; 

__attribute__((used)) static int qlcnic_get_sset_count(struct net_device *dev, int sset)
{
	int len;

	struct qlcnic_adapter *adapter = netdev_priv(dev);
	switch (sset) {
	case ETH_SS_TEST:
		return QLCNIC_TEST_LEN;
	case ETH_SS_STATS:
		len = qlcnic_dev_statistics_len(adapter) + QLCNIC_STATS_LEN;
		if ((adapter->flags & QLCNIC_ESWITCH_ENABLED) ||
		    qlcnic_83xx_check(adapter))
			return len;
		return qlcnic_82xx_statistics();
	default:
		return -EOPNOTSUPP;
	}
}