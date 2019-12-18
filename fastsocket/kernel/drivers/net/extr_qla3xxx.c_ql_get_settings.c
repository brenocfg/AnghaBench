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
struct ql3_adapter {int /*<<< orphan*/  PHYAddr; int /*<<< orphan*/  flags; } ;
struct net_device {int dummy; } ;
struct ethtool_cmd {int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  autoneg; void* advertising; int /*<<< orphan*/  phy_address; int /*<<< orphan*/  port; void* supported; int /*<<< orphan*/  transceiver; } ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_FIBRE ; 
 int /*<<< orphan*/  PORT_TP ; 
 int /*<<< orphan*/  QL_LINK_OPTICAL ; 
 int /*<<< orphan*/  XCVR_INTERNAL ; 
 struct ql3_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ql_get_auto_cfg_status (struct ql3_adapter*) ; 
 int /*<<< orphan*/  ql_get_full_dup (struct ql3_adapter*) ; 
 int /*<<< orphan*/  ql_get_speed (struct ql3_adapter*) ; 
 void* ql_supported_modes (struct ql3_adapter*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ql_get_settings(struct net_device *ndev, struct ethtool_cmd *ecmd)
{
	struct ql3_adapter *qdev = netdev_priv(ndev);

	ecmd->transceiver = XCVR_INTERNAL;
	ecmd->supported = ql_supported_modes(qdev);

	if (test_bit(QL_LINK_OPTICAL,&qdev->flags)) {
		ecmd->port = PORT_FIBRE;
	} else {
		ecmd->port = PORT_TP;
		ecmd->phy_address = qdev->PHYAddr;
	}
	ecmd->advertising = ql_supported_modes(qdev);
	ecmd->autoneg = ql_get_auto_cfg_status(qdev);
	ecmd->speed = ql_get_speed(qdev);
	ecmd->duplex = ql_get_full_dup(qdev);
	return 0;
}