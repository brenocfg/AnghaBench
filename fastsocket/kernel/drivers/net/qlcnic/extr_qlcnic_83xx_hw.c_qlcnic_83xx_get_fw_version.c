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
typedef  int /*<<< orphan*/  u32 ;
struct qlcnic_adapter {int fw_version; struct pci_dev* pdev; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_FW_VERSION_MAJOR ; 
 int /*<<< orphan*/  QLCNIC_FW_VERSION_MINOR ; 
 int /*<<< orphan*/  QLCNIC_FW_VERSION_SUB ; 
 int /*<<< orphan*/  QLCNIC_LINUX_VERSIONID ; 
 int QLCNIC_VERSION_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QLC_SHARED_REG_RD32 (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int qlcnic_83xx_get_fw_version(struct qlcnic_adapter *adapter)
{
	u32 fw_major, fw_minor, fw_build;
	struct pci_dev *pdev = adapter->pdev;

	fw_major = QLC_SHARED_REG_RD32(adapter, QLCNIC_FW_VERSION_MAJOR);
	fw_minor = QLC_SHARED_REG_RD32(adapter, QLCNIC_FW_VERSION_MINOR);
	fw_build = QLC_SHARED_REG_RD32(adapter, QLCNIC_FW_VERSION_SUB);
	adapter->fw_version = QLCNIC_VERSION_CODE(fw_major, fw_minor, fw_build);

	dev_info(&pdev->dev, "Driver v%s, firmware version %d.%d.%d\n",
		 QLCNIC_LINUX_VERSIONID, fw_major, fw_minor, fw_build);

	return adapter->fw_version;
}