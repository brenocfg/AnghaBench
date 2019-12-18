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
typedef  int /*<<< orphan*/  u16 ;
struct link_params {struct bnx2x* bp; } ;
struct bnx2x_phy {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL22_WR_OVER_CL45 (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MDIO_AER_BLOCK_AER_REG ; 
 int /*<<< orphan*/  MDIO_AN_DEVAD ; 
 int /*<<< orphan*/  MDIO_REG_BANK_AER_BLOCK ; 
 int /*<<< orphan*/  MDIO_WC_REG_IEEE0BLK_MIICNTL ; 
 int /*<<< orphan*/  bnx2x_cl45_write (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bnx2x_get_warpcore_lane (struct bnx2x_phy*,struct link_params*) ; 
 int /*<<< orphan*/  bnx2x_set_aer_mmd (struct link_params*,struct bnx2x_phy*) ; 

__attribute__((used)) static void bnx2x_warpcore_restart_AN_KR(struct bnx2x_phy *phy,
					 struct link_params *params)
{
	/* Restart autoneg on the leading lane only */
	struct bnx2x *bp = params->bp;
	u16 lane = bnx2x_get_warpcore_lane(phy, params);
	CL22_WR_OVER_CL45(bp, phy, MDIO_REG_BANK_AER_BLOCK,
			  MDIO_AER_BLOCK_AER_REG, lane);
	bnx2x_cl45_write(bp, phy, MDIO_AN_DEVAD,
			 MDIO_WC_REG_IEEE0BLK_MIICNTL, 0x1200);

	/* Restore AER */
	bnx2x_set_aer_mmd(params, phy);
}