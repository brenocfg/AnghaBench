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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_4__ {int enable; struct qlcnic_dump_template_hdr* tmpl_hdr; } ;
struct qlcnic_hardware_context {TYPE_2__ fw_dump; } ;
struct qlcnic_dump_template_hdr {int /*<<< orphan*/  drv_cap_mask; } ;
struct qlcnic_adapter {TYPE_1__* pdev; struct qlcnic_hardware_context* ahw; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  QLCNIC_DUMP_MASK_DEF ; 
 int __qlcnic_fw_cmd_get_minidump_temp (struct qlcnic_adapter*,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int qlcnic_fw_flash_get_minidump_temp (struct qlcnic_adapter*,scalar_t__*,scalar_t__) ; 
 int qlcnic_fw_get_minidump_temp_size (struct qlcnic_adapter*,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ qlcnic_temp_checksum (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  vfree (struct qlcnic_dump_template_hdr*) ; 
 struct qlcnic_dump_template_hdr* vzalloc (scalar_t__) ; 

int qlcnic_fw_cmd_get_minidump_temp(struct qlcnic_adapter *adapter)
{
	int err;
	u32 temp_size = 0;
	u32 version, csum, *tmp_buf;
	struct qlcnic_hardware_context *ahw;
	struct qlcnic_dump_template_hdr *tmpl_hdr;
	u8 use_flash_temp = 0;

	ahw = adapter->ahw;

	err = qlcnic_fw_get_minidump_temp_size(adapter, &version, &temp_size,
					       &use_flash_temp);
	if (err) {
		dev_err(&adapter->pdev->dev,
			"Can't get template size %d\n", err);
		return -EIO;
	}

	ahw->fw_dump.tmpl_hdr = vzalloc(temp_size);
	if (!ahw->fw_dump.tmpl_hdr)
		return -ENOMEM;

	tmp_buf = (u32 *)ahw->fw_dump.tmpl_hdr;
	if (use_flash_temp)
		goto flash_temp;

	err = __qlcnic_fw_cmd_get_minidump_temp(adapter, tmp_buf, temp_size);

	if (err) {
flash_temp:
		err = qlcnic_fw_flash_get_minidump_temp(adapter, (u8 *)tmp_buf,
							temp_size);

		if (err) {
			dev_err(&adapter->pdev->dev,
				"Failed to get minidump template header %d\n",
				err);
			vfree(ahw->fw_dump.tmpl_hdr);
			ahw->fw_dump.tmpl_hdr = NULL;
			return -EIO;
		}
	}

	csum = qlcnic_temp_checksum((uint32_t *)tmp_buf, temp_size);

	if (csum) {
		dev_err(&adapter->pdev->dev,
			"Template header checksum validation failed\n");
		vfree(ahw->fw_dump.tmpl_hdr);
		ahw->fw_dump.tmpl_hdr = NULL;
		return -EIO;
	}

	tmpl_hdr = ahw->fw_dump.tmpl_hdr;
	tmpl_hdr->drv_cap_mask = QLCNIC_DUMP_MASK_DEF;
	ahw->fw_dump.enable = 1;

	return 0;
}