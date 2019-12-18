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
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int /*<<< orphan*/  revision_id; } ;
struct netxen_adapter {TYPE_2__* pdev; TYPE_1__ ahw; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 scalar_t__ NETXEN_DECODE_VERSION (scalar_t__) ; 
 scalar_t__ NETXEN_MIN_P3_FW_SUPP ; 
 int /*<<< orphan*/  NX_FW_VERSION_OFFSET ; 
 scalar_t__ NX_IS_REVISION_P2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _build (scalar_t__) ; 
 int /*<<< orphan*/  _major (scalar_t__) ; 
 int /*<<< orphan*/  _minor (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ netxen_rom_fast_read (struct netxen_adapter*,int /*<<< orphan*/ ,int*) ; 

int
netxen_check_flash_fw_compatibility(struct netxen_adapter *adapter)
{
	u32 flash_fw_ver, min_fw_ver;

	if (NX_IS_REVISION_P2(adapter->ahw.revision_id))
		return 0;

	if (netxen_rom_fast_read(adapter,
			NX_FW_VERSION_OFFSET, (int *)&flash_fw_ver)) {
		dev_err(&adapter->pdev->dev, "Unable to read flash fw"
			"version\n");
		return -EIO;
	}

	flash_fw_ver = NETXEN_DECODE_VERSION(flash_fw_ver);
	min_fw_ver = NETXEN_MIN_P3_FW_SUPP;
	if (flash_fw_ver >= min_fw_ver)
		return 0;

	dev_info(&adapter->pdev->dev, "Flash fw[%d.%d.%d] is < min fw supported"
		"[4.0.505]. Please update firmware on flash\n",
		_major(flash_fw_ver), _minor(flash_fw_ver),
		_build(flash_fw_ver));
	return -EINVAL;
}