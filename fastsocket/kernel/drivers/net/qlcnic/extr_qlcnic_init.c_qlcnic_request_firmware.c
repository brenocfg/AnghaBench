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
struct qlcnic_adapter {int /*<<< orphan*/ * fw; TYPE_1__* ahw; struct pci_dev* pdev; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {size_t fw_type; } ;

/* Variables and functions */
 size_t QLCNIC_FLASH_ROMIMAGE ; 
 size_t QLCNIC_UNKNOWN_ROMIMAGE ; 
 int /*<<< orphan*/ * fw_name ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  qlcnic_get_next_fwtype (struct qlcnic_adapter*) ; 
 int qlcnic_validate_firmware (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ *) ; 
 int request_firmware (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void qlcnic_request_firmware(struct qlcnic_adapter *adapter)
{
	struct pci_dev *pdev = adapter->pdev;
	int rc;

	adapter->ahw->fw_type = QLCNIC_UNKNOWN_ROMIMAGE;

next:
	qlcnic_get_next_fwtype(adapter);

	if (adapter->ahw->fw_type == QLCNIC_FLASH_ROMIMAGE) {
		adapter->fw = NULL;
	} else {
		rc = request_firmware(&adapter->fw,
				      fw_name[adapter->ahw->fw_type],
				      &pdev->dev);
		if (rc != 0)
			goto next;

		rc = qlcnic_validate_firmware(adapter);
		if (rc != 0) {
			release_firmware(adapter->fw);
			msleep(1);
			goto next;
		}
	}
}