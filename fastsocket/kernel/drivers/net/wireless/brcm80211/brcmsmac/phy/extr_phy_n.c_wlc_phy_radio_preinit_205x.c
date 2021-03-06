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
struct brcms_phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RFCC_CHIP0_PU ; 
 int /*<<< orphan*/  RFCC_OE_POR_FORCE ; 
 int /*<<< orphan*/  and_phy_reg (struct brcms_phy*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  or_phy_reg (struct brcms_phy*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wlc_phy_radio_preinit_205x(struct brcms_phy *pi)
{

	and_phy_reg(pi, 0x78, ~RFCC_CHIP0_PU);
	and_phy_reg(pi, 0x78, RFCC_OE_POR_FORCE);

	or_phy_reg(pi, 0x78, ~RFCC_OE_POR_FORCE);
	or_phy_reg(pi, 0x78, RFCC_CHIP0_PU);

}