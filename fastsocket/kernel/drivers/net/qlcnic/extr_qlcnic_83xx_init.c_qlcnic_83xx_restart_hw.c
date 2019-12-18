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
typedef  int u32 ;
struct qlcnic_adapter {int /*<<< orphan*/  ahw; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  QLCNIC_FW_IMG_VALID ; 
 int QLCRDX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QLC_83XX_BOOT_FROM_FLASH ; 
 int /*<<< orphan*/  QLC_83XX_IDC_CTRL ; 
 int QLC_83XX_IDC_GRACEFULL_RESET ; 
 int /*<<< orphan*/  QLC_SHARED_REG_WR32 (struct qlcnic_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ qlcnic_83xx_check_hw_status (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_83xx_copy_bootloader (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_init_hw (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_83xx_load_fw_image_from_host (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_start_hw (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_stop_hw (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_dump_fw (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_load_fw_file ; 

__attribute__((used)) static int qlcnic_83xx_restart_hw(struct qlcnic_adapter *adapter)
{
	u32 val;
	int err = -EIO;

	qlcnic_83xx_stop_hw(adapter);

	/* Collect FW register dump if required */
	val = QLCRDX(adapter->ahw, QLC_83XX_IDC_CTRL);
	if (!(val & QLC_83XX_IDC_GRACEFULL_RESET))
		qlcnic_dump_fw(adapter);
	qlcnic_83xx_init_hw(adapter);

	if (qlcnic_83xx_copy_bootloader(adapter))
		return err;
	/* Boot either flash image or firmware image from host file system */
	if (qlcnic_load_fw_file) {
		if (qlcnic_83xx_load_fw_image_from_host(adapter))
			return err;
	} else {
		QLC_SHARED_REG_WR32(adapter, QLCNIC_FW_IMG_VALID,
				    QLC_83XX_BOOT_FROM_FLASH);
	}

	qlcnic_83xx_start_hw(adapter);
	if (qlcnic_83xx_check_hw_status(adapter))
		return -EIO;

	return 0;
}