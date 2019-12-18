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
struct qlcnic_adapter {TYPE_2__* ahw; TYPE_1__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  link_autoneg; int /*<<< orphan*/  port_config; int /*<<< orphan*/  port_type; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int /*<<< orphan*/  QLCNIC_GBE ; 
 int /*<<< orphan*/  QLCNIC_XGBE ; 
 scalar_t__ QLC_83XX_AUTONEG (int /*<<< orphan*/ ) ; 
 scalar_t__ QLC_83XX_SFP_10G_CAPABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int qlcnic_83xx_get_port_config (struct qlcnic_adapter*) ; 

int qlcnic_83xx_get_port_info(struct qlcnic_adapter *adapter)
{
	int status;

	status = qlcnic_83xx_get_port_config(adapter);
	if (status) {
		dev_err(&adapter->pdev->dev,
			"Get Port Info failed\n");
	} else {
		if (QLC_83XX_SFP_10G_CAPABLE(adapter->ahw->port_config))
			adapter->ahw->port_type = QLCNIC_XGBE;
		else
			adapter->ahw->port_type = QLCNIC_GBE;

		if (QLC_83XX_AUTONEG(adapter->ahw->port_config))
			adapter->ahw->link_autoneg = AUTONEG_ENABLE;
	}
	return status;
}