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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ ** bw_percentage; } ;
struct ixgbe_adapter {TYPE_1__ temp_dcb_cfg; } ;

/* Variables and functions */
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ixgbe_dcbnl_set_pg_bwg_cfg_rx(struct net_device *netdev, int bwg_id,
                                          u8 bw_pct)
{
	struct ixgbe_adapter *adapter = netdev_priv(netdev);

	adapter->temp_dcb_cfg.bw_percentage[1][bwg_id] = bw_pct;
}