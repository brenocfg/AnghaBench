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
struct link_params {struct bnx2x* bp; } ;
struct bnx2x_phy {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_PMA_DEVAD ; 
 int /*<<< orphan*/  MDIO_PMA_LASI_CTRL ; 
 int /*<<< orphan*/  bnx2x_cl45_write (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_set_disable_pmd_transmit (struct link_params*,struct bnx2x_phy*,int) ; 
 int /*<<< orphan*/  bnx2x_sfp_set_transmitter (struct link_params*,struct bnx2x_phy*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2x_8727_link_reset(struct bnx2x_phy *phy,
				  struct link_params *params)
{
	struct bnx2x *bp = params->bp;

	/* Enable/Disable PHY transmitter output */
	bnx2x_set_disable_pmd_transmit(params, phy, 1);

	/* Disable Transmitter */
	bnx2x_sfp_set_transmitter(params, phy, 0);
	/* Clear LASI */
	bnx2x_cl45_write(bp, phy, MDIO_PMA_DEVAD, MDIO_PMA_LASI_CTRL, 0);

}