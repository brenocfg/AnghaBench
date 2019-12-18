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
typedef  scalar_t__ u8 ;
struct link_params {int feature_config_flags; struct bnx2x* bp; } ;
struct bnx2x_phy {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int FEATURE_CONFIG_BC_SUPPORTS_SFP_TX_DISABLED ; 
 int /*<<< orphan*/  MDIO_PMA_DEVAD ; 
 int /*<<< orphan*/  MDIO_PMA_REG_TX_DISABLE ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 int /*<<< orphan*/  bnx2x_cl45_write (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void bnx2x_set_disable_pmd_transmit(struct link_params *params,
					   struct bnx2x_phy *phy,
					   u8 pmd_dis)
{
	struct bnx2x *bp = params->bp;
	/* Disable transmitter only for bootcodes which can enable it afterwards
	 * (for D3 link)
	 */
	if (pmd_dis) {
		if (params->feature_config_flags &
		     FEATURE_CONFIG_BC_SUPPORTS_SFP_TX_DISABLED)
			DP(NETIF_MSG_LINK, "Disabling PMD transmitter\n");
		else {
			DP(NETIF_MSG_LINK, "NOT disabling PMD transmitter\n");
			return;
		}
	} else
		DP(NETIF_MSG_LINK, "Enabling PMD transmitter\n");
	bnx2x_cl45_write(bp, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_TX_DISABLE, pmd_dis);
}