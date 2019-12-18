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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct bnx2x_phy {scalar_t__ type; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  MDIO_PMA_DEVAD ; 
 int /*<<< orphan*/  MDIO_PMA_REG_GEN_CTRL ; 
 int MDIO_PMA_REG_GEN_CTRL_ROM_MICRO_RESET ; 
 int MDIO_PMA_REG_GEN_CTRL_ROM_RESET_INTERNAL_MP ; 
 int /*<<< orphan*/  MDIO_PMA_REG_M8051_MSGOUT_REG ; 
 int /*<<< orphan*/  MDIO_PMA_REG_MISC_CTRL1 ; 
 int /*<<< orphan*/  MDIO_PMA_REG_ROM_VER1 ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 scalar_t__ PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8073 ; 
 int /*<<< orphan*/  bnx2x_cl45_read (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  bnx2x_cl45_write (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bnx2x_save_bcm_spirom_ver (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int bnx2x_8073_8727_external_rom_boot(struct bnx2x *bp,
					     struct bnx2x_phy *phy,
					     u8 port)
{
	u32 count = 0;
	u16 fw_ver1, fw_msgout;
	int rc = 0;

	/* Boot port from external ROM  */
	/* EDC grst */
	bnx2x_cl45_write(bp, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_GEN_CTRL,
			 0x0001);

	/* Ucode reboot and rst */
	bnx2x_cl45_write(bp, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_GEN_CTRL,
			 0x008c);

	bnx2x_cl45_write(bp, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_MISC_CTRL1, 0x0001);

	/* Reset internal microprocessor */
	bnx2x_cl45_write(bp, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_GEN_CTRL,
			 MDIO_PMA_REG_GEN_CTRL_ROM_MICRO_RESET);

	/* Release srst bit */
	bnx2x_cl45_write(bp, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_GEN_CTRL,
			 MDIO_PMA_REG_GEN_CTRL_ROM_RESET_INTERNAL_MP);

	/* Delay 100ms per the PHY specifications */
	msleep(100);

	/* 8073 sometimes taking longer to download */
	do {
		count++;
		if (count > 300) {
			DP(NETIF_MSG_LINK,
				 "bnx2x_8073_8727_external_rom_boot port %x:"
				 "Download failed. fw version = 0x%x\n",
				 port, fw_ver1);
			rc = -EINVAL;
			break;
		}

		bnx2x_cl45_read(bp, phy,
				MDIO_PMA_DEVAD,
				MDIO_PMA_REG_ROM_VER1, &fw_ver1);
		bnx2x_cl45_read(bp, phy,
				MDIO_PMA_DEVAD,
				MDIO_PMA_REG_M8051_MSGOUT_REG, &fw_msgout);

		usleep_range(1000, 2000);
	} while (fw_ver1 == 0 || fw_ver1 == 0x4321 ||
			((fw_msgout & 0xff) != 0x03 && (phy->type ==
			PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8073)));

	/* Clear ser_boot_ctl bit */
	bnx2x_cl45_write(bp, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_MISC_CTRL1, 0x0000);
	bnx2x_save_bcm_spirom_ver(bp, phy, port);

	DP(NETIF_MSG_LINK,
		 "bnx2x_8073_8727_external_rom_boot port %x:"
		 "Download complete. fw version = 0x%x\n",
		 port, fw_ver1);

	return rc;
}