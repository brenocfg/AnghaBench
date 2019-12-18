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
typedef  int u32 ;
struct qlcnic_dump_template_hdr {int /*<<< orphan*/  version; int /*<<< orphan*/  size; } ;
struct TYPE_2__ {int /*<<< orphan*/ * arg; } ;
struct qlcnic_cmd_args {TYPE_1__ rsp; } ;
struct qlcnic_adapter {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  QLC_83XX_MINIDUMP_FLASH ; 
 scalar_t__ qlcnic_82xx_check (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_83xx_lock_flash (struct qlcnic_adapter*) ; 
 int qlcnic_83xx_lockless_flash_read32 (struct qlcnic_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  qlcnic_83xx_unlock_flash (struct qlcnic_adapter*) ; 

__attribute__((used)) static int
qlcnic_fw_flash_get_minidump_temp_size(struct qlcnic_adapter *adapter,
				       struct qlcnic_cmd_args *cmd)
{
	struct qlcnic_dump_template_hdr tmp_hdr;
	u32 size = sizeof(struct qlcnic_dump_template_hdr) / sizeof(u32);
	int ret = 0;

	if (qlcnic_82xx_check(adapter))
		return -EIO;

	if (qlcnic_83xx_lock_flash(adapter))
		return -EIO;

	ret = qlcnic_83xx_lockless_flash_read32(adapter,
						QLC_83XX_MINIDUMP_FLASH,
						(u8 *)&tmp_hdr, size);

	qlcnic_83xx_unlock_flash(adapter);

	cmd->rsp.arg[2] = tmp_hdr.size;
	cmd->rsp.arg[3] = tmp_hdr.version;

	return ret;
}