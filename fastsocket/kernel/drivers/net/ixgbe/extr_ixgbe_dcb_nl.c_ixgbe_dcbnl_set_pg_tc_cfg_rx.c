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
typedef  scalar_t__ u8 ;
struct net_device {int dummy; } ;
struct TYPE_6__ {TYPE_2__* tc_config; } ;
struct ixgbe_adapter {TYPE_3__ temp_dcb_cfg; } ;
struct TYPE_5__ {TYPE_1__* path; } ;
struct TYPE_4__ {scalar_t__ up_to_tc_bitmap; scalar_t__ bwg_percent; scalar_t__ bwg_id; scalar_t__ prio_type; } ;

/* Variables and functions */
 scalar_t__ DCB_ATTR_VALUE_UNDEFINED ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ixgbe_dcbnl_set_pg_tc_cfg_rx(struct net_device *netdev, int tc,
                                         u8 prio, u8 bwg_id, u8 bw_pct,
                                         u8 up_map)
{
	struct ixgbe_adapter *adapter = netdev_priv(netdev);

	if (prio != DCB_ATTR_VALUE_UNDEFINED)
		adapter->temp_dcb_cfg.tc_config[tc].path[1].prio_type = prio;
	if (bwg_id != DCB_ATTR_VALUE_UNDEFINED)
		adapter->temp_dcb_cfg.tc_config[tc].path[1].bwg_id = bwg_id;
	if (bw_pct != DCB_ATTR_VALUE_UNDEFINED)
		adapter->temp_dcb_cfg.tc_config[tc].path[1].bwg_percent =
			bw_pct;
	if (up_map != DCB_ATTR_VALUE_UNDEFINED)
		adapter->temp_dcb_cfg.tc_config[tc].path[1].up_to_tc_bitmap =
			up_map;
}