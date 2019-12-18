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
typedef  int /*<<< orphan*/  u16 ;
struct zd_chip {int dummy; } ;
struct wiphy {int /*<<< orphan*/  fw_version; } ;
struct TYPE_4__ {TYPE_1__* hw; } ;
struct TYPE_3__ {struct wiphy* wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_REG_FIRMWARE_VER ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_reg_addr (struct zd_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zd_chip_dev (struct zd_chip*) ; 
 TYPE_2__* zd_chip_to_mac (struct zd_chip*) ; 
 int zd_ioread16_locked (struct zd_chip*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int print_fw_version(struct zd_chip *chip)
{
	struct wiphy *wiphy = zd_chip_to_mac(chip)->hw->wiphy;
	int r;
	u16 version;

	r = zd_ioread16_locked(chip, &version,
		fw_reg_addr(chip, FW_REG_FIRMWARE_VER));
	if (r)
		return r;

	dev_info(zd_chip_dev(chip),"firmware version %04hx\n", version);

	snprintf(wiphy->fw_version, sizeof(wiphy->fw_version),
			"%04hx", version);

	return 0;
}