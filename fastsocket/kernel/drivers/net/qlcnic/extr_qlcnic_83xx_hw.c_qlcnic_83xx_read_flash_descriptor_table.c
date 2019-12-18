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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct qlcnic_fdt {int dummy; } ;
struct qlcnic_adapter {TYPE_1__* ahw; } ;
struct TYPE_2__ {int /*<<< orphan*/  fdt; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  QLCNIC_FDT_LOCATION ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ qlcnic_83xx_lock_flash (struct qlcnic_adapter*) ; 
 int qlcnic_83xx_lockless_flash_read32 (struct qlcnic_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  qlcnic_83xx_unlock_flash (struct qlcnic_adapter*) ; 

int qlcnic_83xx_read_flash_descriptor_table(struct qlcnic_adapter *adapter)
{
	int count, fdt_size, ret = 0;

	fdt_size = sizeof(struct qlcnic_fdt);
	count = fdt_size / sizeof(u32);

	if (qlcnic_83xx_lock_flash(adapter))
		return -EIO;

	memset(&adapter->ahw->fdt, 0, fdt_size);
	ret = qlcnic_83xx_lockless_flash_read32(adapter, QLCNIC_FDT_LOCATION,
						(u8 *)&adapter->ahw->fdt,
						count);

	qlcnic_83xx_unlock_flash(adapter);
	return ret;
}