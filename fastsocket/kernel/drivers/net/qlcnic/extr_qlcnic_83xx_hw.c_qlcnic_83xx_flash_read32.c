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
typedef  int /*<<< orphan*/  ulong ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct qlcnic_adapter {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  QLC_83XX_FLASH_DIRECT_DATA (int) ; 
 int /*<<< orphan*/  QLC_83XX_FLASH_DIRECT_WINDOW ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ qlcnic_83xx_lock_flash (struct qlcnic_adapter*) ; 
 int qlcnic_83xx_rd_reg_indirect (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_83xx_unlock_flash (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_83xx_wrt_reg_indirect (struct qlcnic_adapter*,int /*<<< orphan*/ ,int) ; 

int qlcnic_83xx_flash_read32(struct qlcnic_adapter *adapter, u32 flash_addr,
			     u8 *p_data, int count)
{
	int i, ret;
	u32 word, addr = flash_addr;
	ulong  indirect_addr;

	if (qlcnic_83xx_lock_flash(adapter) != 0)
		return -EIO;

	if (addr & 0x3) {
		dev_err(&adapter->pdev->dev, "Illegal addr = 0x%x\n", addr);
		qlcnic_83xx_unlock_flash(adapter);
		return -EIO;
	}

	for (i = 0; i < count; i++) {
		if (qlcnic_83xx_wrt_reg_indirect(adapter,
						 QLC_83XX_FLASH_DIRECT_WINDOW,
						 (addr))) {
			qlcnic_83xx_unlock_flash(adapter);
			return -EIO;
		}

		indirect_addr = QLC_83XX_FLASH_DIRECT_DATA(addr);
		ret = qlcnic_83xx_rd_reg_indirect(adapter,
						  indirect_addr);
		if (ret == -EIO)
			return -EIO;
		word = ret;
		*(u32 *)p_data  = word;
		p_data = p_data + 4;
		addr = addr + 4;
	}

	qlcnic_83xx_unlock_flash(adapter);

	return 0;
}