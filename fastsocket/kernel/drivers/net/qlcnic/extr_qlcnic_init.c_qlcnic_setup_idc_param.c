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
typedef  int u32 ;
struct qlcnic_adapter {int dev_init_timeo; int reset_ack_timeo; TYPE_2__* ahw; TYPE_1__* pdev; int /*<<< orphan*/  portnum; } ;
struct TYPE_4__ {int physical_port; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  QLCNIC_CRB_DEV_PARTITION_INFO ; 
 int QLCNIC_INIT_TIMEOUT_SECS ; 
 int QLCNIC_RESET_TIMEOUT_SECS ; 
 int /*<<< orphan*/  QLCNIC_ROM_DEV_INIT_TIMEOUT ; 
 int /*<<< orphan*/  QLCNIC_ROM_DRV_RESET_TIMEOUT ; 
 int QLCNIC_TYPE_NIC ; 
 int QLC_DEV_GET_DRV (int,int /*<<< orphan*/ ) ; 
 int QLC_SHARED_REG_RD32 (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ qlcnic_rom_fast_read (struct qlcnic_adapter*,int /*<<< orphan*/ ,int*) ; 

int
qlcnic_setup_idc_param(struct qlcnic_adapter *adapter) {

	int timeo;
	u32 val;

	val = QLC_SHARED_REG_RD32(adapter, QLCNIC_CRB_DEV_PARTITION_INFO);
	val = QLC_DEV_GET_DRV(val, adapter->portnum);
	if ((val & 0x3) != QLCNIC_TYPE_NIC) {
		dev_err(&adapter->pdev->dev,
			"Not an Ethernet NIC func=%u\n", val);
		return -EIO;
	}
	adapter->ahw->physical_port = (val >> 2);
	if (qlcnic_rom_fast_read(adapter, QLCNIC_ROM_DEV_INIT_TIMEOUT, &timeo))
		timeo = QLCNIC_INIT_TIMEOUT_SECS;

	adapter->dev_init_timeo = timeo;

	if (qlcnic_rom_fast_read(adapter, QLCNIC_ROM_DRV_RESET_TIMEOUT, &timeo))
		timeo = QLCNIC_RESET_TIMEOUT_SECS;

	adapter->reset_ack_timeo = timeo;

	return 0;
}