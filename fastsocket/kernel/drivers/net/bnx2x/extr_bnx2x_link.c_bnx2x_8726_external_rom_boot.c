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
struct link_params {int /*<<< orphan*/  port; struct bnx2x* bp; } ;
struct bnx2x_phy {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_PMA_DEVAD ; 
 int /*<<< orphan*/  MDIO_PMA_REG_GEN_CTRL ; 
 int MDIO_PMA_REG_GEN_CTRL_ROM_MICRO_RESET ; 
 int MDIO_PMA_REG_GEN_CTRL_ROM_RESET_INTERNAL_MP ; 
 int /*<<< orphan*/  MDIO_PMA_REG_MISC_CTRL1 ; 
 int /*<<< orphan*/  bnx2x_cl45_write (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bnx2x_save_bcm_spirom_ver (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void bnx2x_8726_external_rom_boot(struct bnx2x_phy *phy,
					 struct link_params *params)
{
	struct bnx2x *bp = params->bp;
	/* Need to wait 100ms after reset */
	msleep(100);

	/* Micro controller re-boot */
	bnx2x_cl45_write(bp, phy,
			 MDIO_PMA_DEVAD, MDIO_PMA_REG_GEN_CTRL, 0x018B);

	/* Set soft reset */
	bnx2x_cl45_write(bp, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_GEN_CTRL,
			 MDIO_PMA_REG_GEN_CTRL_ROM_MICRO_RESET);

	bnx2x_cl45_write(bp, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_MISC_CTRL1, 0x0001);

	bnx2x_cl45_write(bp, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_GEN_CTRL,
			 MDIO_PMA_REG_GEN_CTRL_ROM_RESET_INTERNAL_MP);

	/* Wait for 150ms for microcode load */
	msleep(150);

	/* Disable serial boot control, tristates pins SS_N, SCK, MOSI, MISO */
	bnx2x_cl45_write(bp, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_MISC_CTRL1, 0x0000);

	msleep(200);
	bnx2x_save_bcm_spirom_ver(bp, phy, params->port);
}