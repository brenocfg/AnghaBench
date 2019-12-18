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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct link_vars {scalar_t__ line_speed; int eee_status; } ;
struct link_params {struct bnx2x* bp; } ;
struct bnx2x_phy {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MDIO_AN_DEVAD ; 
 int /*<<< orphan*/  MDIO_AN_REG_EEE_ADV ; 
 int /*<<< orphan*/  MDIO_AN_REG_LP_EEE_ADV ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 int SHMEM_EEE_100M_ADV ; 
 int SHMEM_EEE_10G_ADV ; 
 int SHMEM_EEE_1G_ADV ; 
 int SHMEM_EEE_ACTIVE_BIT ; 
 int SHMEM_EEE_LP_ADV_STATUS_MASK ; 
 int SHMEM_EEE_LP_ADV_STATUS_SHIFT ; 
 scalar_t__ SPEED_100 ; 
 scalar_t__ SPEED_1000 ; 
 scalar_t__ SPEED_10000 ; 
 int /*<<< orphan*/  bnx2x_cl45_read (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void bnx2x_eee_an_resolve(struct bnx2x_phy *phy,
				  struct link_params *params,
				  struct link_vars *vars)
{
	struct bnx2x *bp = params->bp;
	u16 adv = 0, lp = 0;
	u32 lp_adv = 0;
	u8 neg = 0;

	bnx2x_cl45_read(bp, phy, MDIO_AN_DEVAD, MDIO_AN_REG_EEE_ADV, &adv);
	bnx2x_cl45_read(bp, phy, MDIO_AN_DEVAD, MDIO_AN_REG_LP_EEE_ADV, &lp);

	if (lp & 0x2) {
		lp_adv |= SHMEM_EEE_100M_ADV;
		if (adv & 0x2) {
			if (vars->line_speed == SPEED_100)
				neg = 1;
			DP(NETIF_MSG_LINK, "EEE negotiated - 100M\n");
		}
	}
	if (lp & 0x14) {
		lp_adv |= SHMEM_EEE_1G_ADV;
		if (adv & 0x14) {
			if (vars->line_speed == SPEED_1000)
				neg = 1;
			DP(NETIF_MSG_LINK, "EEE negotiated - 1G\n");
		}
	}
	if (lp & 0x68) {
		lp_adv |= SHMEM_EEE_10G_ADV;
		if (adv & 0x68) {
			if (vars->line_speed == SPEED_10000)
				neg = 1;
			DP(NETIF_MSG_LINK, "EEE negotiated - 10G\n");
		}
	}

	vars->eee_status &= ~SHMEM_EEE_LP_ADV_STATUS_MASK;
	vars->eee_status |= (lp_adv << SHMEM_EEE_LP_ADV_STATUS_SHIFT);

	if (neg) {
		DP(NETIF_MSG_LINK, "EEE is active\n");
		vars->eee_status |= SHMEM_EEE_ACTIVE_BIT;
	}

}