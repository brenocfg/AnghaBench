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
struct net_device {int dummy; } ;
struct fe_priv {int driver_data; } ;

/* Variables and functions */
 int DEV_HAS_STATISTICS_V1 ; 
 int DEV_HAS_STATISTICS_V2 ; 
 int DEV_HAS_STATISTICS_V3 ; 
 int DEV_HAS_TEST_EXTENDED ; 
 int EOPNOTSUPP ; 
#define  ETH_SS_STATS 129 
#define  ETH_SS_TEST 128 
 int NV_DEV_STATISTICS_V1_COUNT ; 
 int NV_DEV_STATISTICS_V2_COUNT ; 
 int NV_DEV_STATISTICS_V3_COUNT ; 
 int NV_TEST_COUNT_BASE ; 
 int NV_TEST_COUNT_EXTENDED ; 
 struct fe_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int nv_get_sset_count(struct net_device *dev, int sset)
{
	struct fe_priv *np = netdev_priv(dev);

	switch (sset) {
	case ETH_SS_TEST:
		if (np->driver_data & DEV_HAS_TEST_EXTENDED)
			return NV_TEST_COUNT_EXTENDED;
		else
			return NV_TEST_COUNT_BASE;
	case ETH_SS_STATS:
		if (np->driver_data & DEV_HAS_STATISTICS_V3)
			return NV_DEV_STATISTICS_V3_COUNT;
		else if (np->driver_data & DEV_HAS_STATISTICS_V2)
			return NV_DEV_STATISTICS_V2_COUNT;
		else if (np->driver_data & DEV_HAS_STATISTICS_V1)
			return NV_DEV_STATISTICS_V1_COUNT;
		else
			return 0;
	default:
		return -EOPNOTSUPP;
	}
}