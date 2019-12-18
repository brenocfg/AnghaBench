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
struct qlcnic_adapter {TYPE_2__* ahw; TYPE_1__* pdev; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int msix_supported; int /*<<< orphan*/  fw_hal_version; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  QLCNIC_ADAPTER_INITIALIZED ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_83xx_config_buff_descriptors (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_get_minidump_template (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_83xx_get_port_info (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_use_msi_x ; 

__attribute__((used)) static int qlcnic_83xx_init_default_driver(struct qlcnic_adapter *adapter)
{
	int err = -EIO;

	qlcnic_83xx_get_minidump_template(adapter);
	if (qlcnic_83xx_get_port_info(adapter))
		return err;

	qlcnic_83xx_config_buff_descriptors(adapter);
	adapter->ahw->msix_supported = !!qlcnic_use_msi_x;
	adapter->flags |= QLCNIC_ADAPTER_INITIALIZED;

	dev_info(&adapter->pdev->dev, "HAL Version: %d\n",
		 adapter->ahw->fw_hal_version);

	return 0;
}