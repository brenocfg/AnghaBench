#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct qlcnic_adapter {TYPE_2__* ahw; TYPE_1__* pdev; } ;
struct ethtool_cmd {scalar_t__ autoneg; } ;
struct TYPE_4__ {int /*<<< orphan*/  port_config; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_10 ; 
 int /*<<< orphan*/  BIT_11 ; 
 int /*<<< orphan*/  BIT_15 ; 
 int /*<<< orphan*/  BIT_8 ; 
 int /*<<< orphan*/  BIT_9 ; 
 int EINVAL ; 
#define  SPEED_10 131 
#define  SPEED_100 130 
#define  SPEED_1000 129 
#define  SPEED_10000 128 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int ethtool_cmd_speed (struct ethtool_cmd*) ; 
 int qlcnic_83xx_set_port_config (struct qlcnic_adapter*) ; 

int qlcnic_83xx_set_settings(struct qlcnic_adapter *adapter,
			     struct ethtool_cmd *ecmd)
{
	int status = 0;
	u32 config = adapter->ahw->port_config;

	if (ecmd->autoneg)
		adapter->ahw->port_config |= BIT_15;

	switch (ethtool_cmd_speed(ecmd)) {
	case SPEED_10:
		adapter->ahw->port_config |= BIT_8;
		break;
	case SPEED_100:
		adapter->ahw->port_config |= BIT_9;
		break;
	case SPEED_1000:
		adapter->ahw->port_config |= BIT_10;
		break;
	case SPEED_10000:
		adapter->ahw->port_config |= BIT_11;
		break;
	default:
		return -EINVAL;
	}

	status = qlcnic_83xx_set_port_config(adapter);
	if (status) {
		dev_info(&adapter->pdev->dev,
			 "Faild to Set Link Speed and autoneg.\n");
		adapter->ahw->port_config = config;
	}
	return status;
}