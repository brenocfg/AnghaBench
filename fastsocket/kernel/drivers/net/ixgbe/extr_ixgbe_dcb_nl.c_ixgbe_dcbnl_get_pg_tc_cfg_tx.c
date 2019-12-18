#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct TYPE_6__ {TYPE_2__* tc_config; } ;
struct ixgbe_adapter {TYPE_3__ dcb_cfg; } ;
struct TYPE_5__ {TYPE_1__* path; } ;
struct TYPE_4__ {int /*<<< orphan*/  up_to_tc_bitmap; int /*<<< orphan*/  bwg_percent; int /*<<< orphan*/  bwg_id; int /*<<< orphan*/  prio_type; } ;

/* Variables and functions */
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ixgbe_dcbnl_get_pg_tc_cfg_tx(struct net_device *netdev, int tc,
                                         u8 *prio, u8 *bwg_id, u8 *bw_pct,
                                         u8 *up_map)
{
	struct ixgbe_adapter *adapter = netdev_priv(netdev);

	*prio = adapter->dcb_cfg.tc_config[tc].path[0].prio_type;
	*bwg_id = adapter->dcb_cfg.tc_config[tc].path[0].bwg_id;
	*bw_pct = adapter->dcb_cfg.tc_config[tc].path[0].bwg_percent;
	*up_map = adapter->dcb_cfg.tc_config[tc].path[0].up_to_tc_bitmap;
}