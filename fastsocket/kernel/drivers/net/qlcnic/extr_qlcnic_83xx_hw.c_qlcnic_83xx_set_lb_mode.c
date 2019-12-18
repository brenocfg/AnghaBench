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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  status; } ;
struct qlcnic_hardware_context {TYPE_2__ idc; int /*<<< orphan*/  port_config; } ;
struct qlcnic_adapter {int flags; int /*<<< orphan*/  mac_addr; TYPE_1__* pdev; struct qlcnic_hardware_context* ahw; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ QLCNIC_ELB_MODE ; 
 int /*<<< orphan*/  QLCNIC_ILB_MAX_RCV_LOOP ; 
 scalar_t__ QLCNIC_ILB_MODE ; 
 int /*<<< orphan*/  QLCNIC_MAC_ADD ; 
 int QLCNIC_MSIX_ENABLED ; 
 int /*<<< orphan*/  QLC_83XX_CFG_LOOPBACK_EXT ; 
 int /*<<< orphan*/  QLC_83XX_CFG_LOOPBACK_HSS ; 
 int /*<<< orphan*/  QLC_83XX_IDC_COMP_AEN ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  qlcnic_83xx_clear_lb_mode (struct qlcnic_adapter*,scalar_t__) ; 
 int qlcnic_83xx_get_port_config (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_process_aen (struct qlcnic_adapter*) ; 
 int qlcnic_83xx_set_port_config (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_sre_macaddr_change (struct qlcnic_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int qlcnic_83xx_set_lb_mode(struct qlcnic_adapter *adapter, u8 mode)
{
	struct qlcnic_hardware_context *ahw = adapter->ahw;
	int status = 0, loop = 0;
	u32 config;

	status = qlcnic_83xx_get_port_config(adapter);
	if (status)
		return status;

	config = ahw->port_config;
	set_bit(QLC_83XX_IDC_COMP_AEN, &ahw->idc.status);

	if (mode == QLCNIC_ILB_MODE)
		ahw->port_config |= QLC_83XX_CFG_LOOPBACK_HSS;
	if (mode == QLCNIC_ELB_MODE)
		ahw->port_config |= QLC_83XX_CFG_LOOPBACK_EXT;

	status = qlcnic_83xx_set_port_config(adapter);
	if (status) {
		dev_err(&adapter->pdev->dev,
			"Failed to Set Loopback Mode = 0x%x.\n",
			ahw->port_config);
		ahw->port_config = config;
		clear_bit(QLC_83XX_IDC_COMP_AEN, &ahw->idc.status);
		return status;
	}

	/* Wait for Link and IDC Completion AEN */
	do {
		msleep(300);
		if (!(adapter->flags & QLCNIC_MSIX_ENABLED))
			qlcnic_83xx_process_aen(adapter);

		if (loop++ > QLCNIC_ILB_MAX_RCV_LOOP) {
			dev_err(&adapter->pdev->dev,
				"FW did not generate IDC completion AEN\n");
			clear_bit(QLC_83XX_IDC_COMP_AEN, &ahw->idc.status);
			qlcnic_83xx_clear_lb_mode(adapter, mode);
			return -EIO;
		}
	} while (test_bit(QLC_83XX_IDC_COMP_AEN, &ahw->idc.status));

	qlcnic_sre_macaddr_change(adapter, adapter->mac_addr, 0,
				  QLCNIC_MAC_ADD);
	return status;
}