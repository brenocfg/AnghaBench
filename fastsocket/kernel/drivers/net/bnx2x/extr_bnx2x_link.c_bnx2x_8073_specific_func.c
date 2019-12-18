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
typedef  int u32 ;
struct link_params {struct bnx2x* bp; } ;
struct bnx2x_phy {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_PMA_DEVAD ; 
 int /*<<< orphan*/  MDIO_PMA_LASI_CTRL ; 
 int /*<<< orphan*/  MDIO_PMA_LASI_RXCTRL ; 
#define  PHY_INIT 128 
 int /*<<< orphan*/  bnx2x_cl45_write (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bnx2x_8073_specific_func(struct bnx2x_phy *phy,
				     struct link_params *params,
				     u32 action)
{
	struct bnx2x *bp = params->bp;
	switch (action) {
	case PHY_INIT:
		/* Enable LASI */
		bnx2x_cl45_write(bp, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_LASI_RXCTRL, (1<<2));
		bnx2x_cl45_write(bp, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_LASI_CTRL,  0x0004);
		break;
	}
}