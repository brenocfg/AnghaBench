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
typedef  int u16 ;
struct link_params {struct bnx2x* bp; } ;
struct bnx2x_phy {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL22_WR_OVER_CL45 (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MDIO_AER_BLOCK_AER_REG ; 
 int /*<<< orphan*/  MDIO_AN_DEVAD ; 
 int /*<<< orphan*/  MDIO_AN_REG_CTRL ; 
 int /*<<< orphan*/  MDIO_PMA_DEVAD ; 
 int /*<<< orphan*/  MDIO_REG_BANK_AER_BLOCK ; 
 int /*<<< orphan*/  MDIO_WC_DEVAD ; 
 int /*<<< orphan*/  MDIO_WC_REG_CL72_USERB0_CL72_MISC1_CONTROL ; 
 int /*<<< orphan*/  MDIO_WC_REG_CL72_USERB0_CL72_TX_FIR_TAP ; 
 int /*<<< orphan*/  MDIO_WC_REG_CL73_USERB0_CTRL ; 
 int /*<<< orphan*/  MDIO_WC_REG_DIGITAL4_MISC3 ; 
 int /*<<< orphan*/  MDIO_WC_REG_PMD_KR_CONTROL ; 
 int /*<<< orphan*/  MDIO_WC_REG_SERDESDIGITAL_MISC1 ; 
 int /*<<< orphan*/  MDIO_WC_REG_XGXSBLK0_XGXSCONTROL ; 
 int /*<<< orphan*/  bnx2x_cl45_read (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  bnx2x_cl45_read_and_write (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bnx2x_cl45_read_or_write (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bnx2x_cl45_write (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bnx2x_set_aer_mmd (struct link_params*,struct bnx2x_phy*) ; 

__attribute__((used)) static void bnx2x_warpcore_set_20G_force_KR2(struct bnx2x_phy *phy,
					     struct link_params *params)
{
	u16 val;
	struct bnx2x *bp = params->bp;
	/* Set global registers, so set AER lane to 0 */
	CL22_WR_OVER_CL45(bp, phy, MDIO_REG_BANK_AER_BLOCK,
			  MDIO_AER_BLOCK_AER_REG, 0);

	/* Disable sequencer */
	bnx2x_cl45_read_and_write(bp, phy, MDIO_WC_DEVAD,
				  MDIO_WC_REG_XGXSBLK0_XGXSCONTROL, ~(1<<13));

	bnx2x_set_aer_mmd(params, phy);

	bnx2x_cl45_read_and_write(bp, phy, MDIO_PMA_DEVAD,
				  MDIO_WC_REG_PMD_KR_CONTROL, ~(1<<1));
	bnx2x_cl45_write(bp, phy, MDIO_AN_DEVAD,
			 MDIO_AN_REG_CTRL, 0);
	/* Turn off CL73 */
	bnx2x_cl45_read(bp, phy, MDIO_WC_DEVAD,
			MDIO_WC_REG_CL73_USERB0_CTRL, &val);
	val &= ~(1<<5);
	val |= (1<<6);
	bnx2x_cl45_write(bp, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_CL73_USERB0_CTRL, val);

	/* Set 20G KR2 force speed */
	bnx2x_cl45_read_or_write(bp, phy, MDIO_WC_DEVAD,
				 MDIO_WC_REG_SERDESDIGITAL_MISC1, 0x1f);

	bnx2x_cl45_read_or_write(bp, phy, MDIO_WC_DEVAD,
				 MDIO_WC_REG_DIGITAL4_MISC3, (1<<7));

	bnx2x_cl45_read(bp, phy, MDIO_WC_DEVAD,
			MDIO_WC_REG_CL72_USERB0_CL72_MISC1_CONTROL, &val);
	val &= ~(3<<14);
	val |= (1<<15);
	bnx2x_cl45_write(bp, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_CL72_USERB0_CL72_MISC1_CONTROL, val);
	bnx2x_cl45_write(bp, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_CL72_USERB0_CL72_TX_FIR_TAP, 0x835A);

	/* Enable sequencer (over lane 0) */
	CL22_WR_OVER_CL45(bp, phy, MDIO_REG_BANK_AER_BLOCK,
			  MDIO_AER_BLOCK_AER_REG, 0);

	bnx2x_cl45_read_or_write(bp, phy, MDIO_WC_DEVAD,
				 MDIO_WC_REG_XGXSBLK0_XGXSCONTROL, (1<<13));

	bnx2x_set_aer_mmd(params, phy);
}