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
struct wl1251 {int chip_id; int /*<<< orphan*/  use_eeprom; int /*<<< orphan*/ * nvs; int /*<<< orphan*/ * fw; TYPE_1__* if_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* reset ) (struct wl1251*) ;} ;

/* Variables and functions */
#define  CHIP_ID_1251_PG10 130 
#define  CHIP_ID_1251_PG11 129 
#define  CHIP_ID_1251_PG12 128 
 int /*<<< orphan*/  CHIP_ID_B ; 
 int /*<<< orphan*/  DEBUG_BOOT ; 
 int ENODEV ; 
 int /*<<< orphan*/  REGISTERS_BASE ; 
 int /*<<< orphan*/  REGISTERS_DOWN_SIZE ; 
 int /*<<< orphan*/  WL1251_POWER_ON_SLEEP ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct wl1251*) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wl1251_error (char*,int) ; 
 int wl1251_fetch_firmware (struct wl1251*) ; 
 int wl1251_fetch_nvs (struct wl1251*) ; 
 int /*<<< orphan*/  wl1251_fw_wakeup (struct wl1251*) ; 
 int wl1251_power_on (struct wl1251*) ; 
 int wl1251_reg_read32 (struct wl1251*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1251_set_partition (struct wl1251*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wl1251_chip_wakeup(struct wl1251 *wl)
{
	int ret;

	ret = wl1251_power_on(wl);
	if (ret < 0)
		return ret;

	msleep(WL1251_POWER_ON_SLEEP);
	wl->if_ops->reset(wl);

	/* We don't need a real memory partition here, because we only want
	 * to use the registers at this point. */
	wl1251_set_partition(wl,
			     0x00000000,
			     0x00000000,
			     REGISTERS_BASE,
			     REGISTERS_DOWN_SIZE);

	/* ELP module wake up */
	wl1251_fw_wakeup(wl);

	/* whal_FwCtrl_BootSm() */

	/* 0. read chip id from CHIP_ID */
	wl->chip_id = wl1251_reg_read32(wl, CHIP_ID_B);

	/* 1. check if chip id is valid */

	switch (wl->chip_id) {
	case CHIP_ID_1251_PG12:
		wl1251_debug(DEBUG_BOOT, "chip id 0x%x (1251 PG12)",
			     wl->chip_id);
		break;
	case CHIP_ID_1251_PG11:
		wl1251_debug(DEBUG_BOOT, "chip id 0x%x (1251 PG11)",
			     wl->chip_id);
		break;
	case CHIP_ID_1251_PG10:
	default:
		wl1251_error("unsupported chip id: 0x%x", wl->chip_id);
		ret = -ENODEV;
		goto out;
	}

	if (wl->fw == NULL) {
		ret = wl1251_fetch_firmware(wl);
		if (ret < 0)
			goto out;
	}

	if (wl->nvs == NULL && !wl->use_eeprom) {
		/* No NVS from netlink, try to get it from the filesystem */
		ret = wl1251_fetch_nvs(wl);
		if (ret < 0)
			goto out;
	}

out:
	return ret;
}