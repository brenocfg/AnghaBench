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
typedef  int u32 ;
struct qlcnic_adapter {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  QLCNIC_ROMUSB_ROM_ABYTE_CNT ; 
 int /*<<< orphan*/  QLCNIC_ROMUSB_ROM_ADDRESS ; 
 int /*<<< orphan*/  QLCNIC_ROMUSB_ROM_DUMMY_BYTE_CNT ; 
 int /*<<< orphan*/  QLCNIC_ROMUSB_ROM_INSTR_OPCODE ; 
 int /*<<< orphan*/  QLCNIC_ROMUSB_ROM_RDATA ; 
 int QLCRD32 (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QLCWR32 (struct qlcnic_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ qlcnic_wait_rom_done (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int do_rom_fast_read(struct qlcnic_adapter *adapter,
			    u32 addr, u32 *valp)
{
	QLCWR32(adapter, QLCNIC_ROMUSB_ROM_ADDRESS, addr);
	QLCWR32(adapter, QLCNIC_ROMUSB_ROM_DUMMY_BYTE_CNT, 0);
	QLCWR32(adapter, QLCNIC_ROMUSB_ROM_ABYTE_CNT, 3);
	QLCWR32(adapter, QLCNIC_ROMUSB_ROM_INSTR_OPCODE, 0xb);
	if (qlcnic_wait_rom_done(adapter)) {
		dev_err(&adapter->pdev->dev, "Error waiting for rom done\n");
		return -EIO;
	}
	/* reset abyte_cnt and dummy_byte_cnt */
	QLCWR32(adapter, QLCNIC_ROMUSB_ROM_ABYTE_CNT, 0);
	udelay(10);
	QLCWR32(adapter, QLCNIC_ROMUSB_ROM_DUMMY_BYTE_CNT, 0);

	*valp = QLCRD32(adapter, QLCNIC_ROMUSB_ROM_RDATA);
	return 0;
}