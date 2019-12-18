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
typedef  size_t u16 ;
struct link_vars {int /*<<< orphan*/  link_attr_sync; } ;
struct link_params {struct bnx2x* bp; } ;
struct bnx2x_reg_set {int member_2; int /*<<< orphan*/  val; int /*<<< orphan*/  reg; int /*<<< orphan*/  devad; int /*<<< orphan*/  member_1; int /*<<< orphan*/  const member_0; } ;
struct bnx2x_phy {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct bnx2x_reg_set*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LINK_ATTR_SYNC_KR2_ENABLE ; 
#define  MDIO_WC_DEVAD 143 
 int /*<<< orphan*/  MDIO_WC_REG_CL49_USERB0_CTRL ; 
#define  MDIO_WC_REG_CL73_BAM_CODE_FIELD 142 
#define  MDIO_WC_REG_CL73_BAM_CTRL1 141 
#define  MDIO_WC_REG_CL73_BAM_CTRL3 140 
#define  MDIO_WC_REG_CL73_USERB0_CTRL 139 
#define  MDIO_WC_REG_CL82_USERB1_RX_CTRL10 138 
#define  MDIO_WC_REG_CL82_USERB1_RX_CTRL11 137 
#define  MDIO_WC_REG_CL82_USERB1_TX_CTRL5 136 
#define  MDIO_WC_REG_CL82_USERB1_TX_CTRL6 135 
#define  MDIO_WC_REG_CL82_USERB1_TX_CTRL7 134 
#define  MDIO_WC_REG_CL82_USERB1_TX_CTRL9 133 
#define  MDIO_WC_REG_ETA_CL73_LD_BAM_CODE 132 
#define  MDIO_WC_REG_ETA_CL73_LD_UD_CODE 131 
#define  MDIO_WC_REG_ETA_CL73_OUI1 130 
#define  MDIO_WC_REG_ETA_CL73_OUI2 129 
#define  MDIO_WC_REG_ETA_CL73_OUI3 128 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 int /*<<< orphan*/  bnx2x_cl45_read_or_write (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bnx2x_cl45_write (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_update_link_attr (struct link_params*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2x_warpcore_enable_AN_KR2(struct bnx2x_phy *phy,
					 struct link_params *params,
					 struct link_vars *vars)
{
	struct bnx2x *bp = params->bp;
	u16 i;
	static struct bnx2x_reg_set reg_set[] = {
		/* Step 1 - Program the TX/RX alignment markers */
		{MDIO_WC_DEVAD, MDIO_WC_REG_CL82_USERB1_TX_CTRL5, 0xa157},
		{MDIO_WC_DEVAD, MDIO_WC_REG_CL82_USERB1_TX_CTRL7, 0xcbe2},
		{MDIO_WC_DEVAD, MDIO_WC_REG_CL82_USERB1_TX_CTRL6, 0x7537},
		{MDIO_WC_DEVAD, MDIO_WC_REG_CL82_USERB1_TX_CTRL9, 0xa157},
		{MDIO_WC_DEVAD, MDIO_WC_REG_CL82_USERB1_RX_CTRL11, 0xcbe2},
		{MDIO_WC_DEVAD, MDIO_WC_REG_CL82_USERB1_RX_CTRL10, 0x7537},
		/* Step 2 - Configure the NP registers */
		{MDIO_WC_DEVAD, MDIO_WC_REG_CL73_USERB0_CTRL, 0x000a},
		{MDIO_WC_DEVAD, MDIO_WC_REG_CL73_BAM_CTRL1, 0x6400},
		{MDIO_WC_DEVAD, MDIO_WC_REG_CL73_BAM_CTRL3, 0x0620},
		{MDIO_WC_DEVAD, MDIO_WC_REG_CL73_BAM_CODE_FIELD, 0x0157},
		{MDIO_WC_DEVAD, MDIO_WC_REG_ETA_CL73_OUI1, 0x6464},
		{MDIO_WC_DEVAD, MDIO_WC_REG_ETA_CL73_OUI2, 0x3150},
		{MDIO_WC_DEVAD, MDIO_WC_REG_ETA_CL73_OUI3, 0x3150},
		{MDIO_WC_DEVAD, MDIO_WC_REG_ETA_CL73_LD_BAM_CODE, 0x0157},
		{MDIO_WC_DEVAD, MDIO_WC_REG_ETA_CL73_LD_UD_CODE, 0x0620}
	};
	DP(NETIF_MSG_LINK, "Enabling 20G-KR2\n");

	bnx2x_cl45_read_or_write(bp, phy, MDIO_WC_DEVAD,
				 MDIO_WC_REG_CL49_USERB0_CTRL, (3<<6));

	for (i = 0; i < ARRAY_SIZE(reg_set); i++)
		bnx2x_cl45_write(bp, phy, reg_set[i].devad, reg_set[i].reg,
				 reg_set[i].val);

	/* Start KR2 work-around timer which handles BCM8073 link-parner */
	vars->link_attr_sync |= LINK_ATTR_SYNC_KR2_ENABLE;
	bnx2x_update_link_attr(params, vars->link_attr_sync);
}